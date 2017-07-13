/* drivers/leds/leds-x210.c
 *
 *
 *
 * S5PV210 - LEDs GPIO driver
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/leds.h>
#include <linux/gpio.h>
#include <linux/slab.h>

#include <mach/hardware.h>
#include <mach/regs-gpio.h>
#include <mach/leds-gpio.h>

/* our context */

struct x210_gpio_led {
	struct led_classdev		 cdev;
	struct x210_led_platdata	*pdata;
};

static inline struct x210_gpio_led *pdev_to_gpio(struct platform_device *dev)
{
	return platform_get_drvdata(dev);
}

static inline struct x210_gpio_led *to_gpio(struct led_classdev *led_cdev)
{
	return container_of(led_cdev, struct x210_gpio_led, cdev);
}

static void x210_led_set(struct led_classdev *led_cdev,
			    enum led_brightness value)
{
	struct x210_gpio_led *led = to_gpio(led_cdev);
	struct x210_led_platdata *pd = led->pdata;

	/* there will be a short delay between setting the output and
	 * going from output to input when using tristate. */

	gpio_request(pd->gpio, "temporary");

	if (pd->flags & X210_LEDF_TRISTATE)
		s3c_gpio_cfgpin(pd->gpio,
			value ? S3C_GPIO_OUTPUT : S3C_GPIO_INPUT);
	if(value)
		s3c_gpio_setpull(pd->gpio, S3C_GPIO_PULL_UP);
	
	gpio_set_value(pd->gpio, (value ? 1 : 0) ^
			    (pd->flags & X210_LEDF_ACTLOW));
	
	gpio_free(pd->gpio);


}

static int x210_leds_remove(struct platform_device *dev)
{
	struct x210_gpio_led *led = pdev_to_gpio(dev);

	led_classdev_unregister(&led->cdev);
	kfree(led);

	return 0;
}

static int x210_leds_probe(struct platform_device *dev)
{
	struct x210_led_platdata *pdata = dev->dev.platform_data;
	struct x210_gpio_led *led;
	int ret;

	led = kzalloc(sizeof(struct x210_gpio_led), GFP_KERNEL);
	if (led == NULL) {
		dev_err(&dev->dev, "No memory for device\n");
		return -ENOMEM;
	}

	platform_set_drvdata(dev, led);

	led->cdev.brightness_set = x210_led_set;
	led->cdev.default_trigger = pdata->def_trigger;
	led->cdev.name = pdata->name;
	led->cdev.flags |= LED_CORE_SUSPENDRESUME;

	led->pdata = pdata;

	/* no point in having a pull-up if we are always driving */

	gpio_request(pdata->gpio, "temporary");
	if (pdata->flags & X210_LEDF_TRISTATE) {
		s3c_gpio_cfgpin(pdata->gpio, S3C_GPIO_INPUT);
		gpio_set_value(pdata->gpio, 0);
	} else {
		s3c_gpio_setpull(pdata->gpio, S3C_GPIO_PULL_UP);
		s3c_gpio_cfgpin(pdata->gpio, S3C_GPIO_OUTPUT);
		gpio_set_value(pdata->gpio, 0);
	}
	gpio_free(pdata->gpio);

	
	/* register our new led device */

	ret = led_classdev_register(NULL, &led->cdev);
	if (ret < 0) {
		dev_err(&dev->dev, "led_classdev_register failed\n");
		kfree(led);
		return ret;
	}

	return 0;
}

static struct platform_driver x210_leds_driver = {
	.probe		= x210_leds_probe,
	.remove		= x210_leds_remove,
	.driver		= {
		.name		= "x210_leds",
		.owner		= THIS_MODULE,
	},
};

static int __init x210_leds_init(void)
{
	return platform_driver_register(&x210_leds_driver);
}

static void __exit x210_leds_exit(void)
{
	platform_driver_unregister(&x210_leds_driver);
}

module_init(s3c24xx_led_init);
module_exit(s3c24xx_led_exit);

MODULE_AUTHOR("liulianjun <liulianjun102@outlook.com>");
MODULE_DESCRIPTION("x210 LED driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:s5pv210_led");

