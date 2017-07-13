/* linux/arch/arm/mach-s5pv210/dev-audio.c
 *
 * Copyright (c) 2010 Samsung Electronics Co. Ltd
 *	Jaswinder Singh <jassi.brar@samsung.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/platform_device.h>
#include <linux/dma-mapping.h>

#include <plat/gpio-cfg.h>
#include <plat/audio.h>

#include <mach/gpio.h>
#include <mach/map.h>
#include <mach/dma.h>
#include <mach/irqs.h>

static int s5pv210_cfg_i2s(struct platform_device *pdev)
{
	/* configure GPIO for i2s port */
	switch (pdev->id) {
	case 1:
		s3c_gpio_cfgpin(S5PV210_GPC0(0), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPC0(1), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPC0(2), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPC0(3), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPC0(4), S3C_GPIO_SFN(2));
		break;

	case 2:
		s3c_gpio_cfgpin(S5PV210_GPC1(0), S3C_GPIO_SFN(4));
		s3c_gpio_cfgpin(S5PV210_GPC1(1), S3C_GPIO_SFN(4));
		s3c_gpio_cfgpin(S5PV210_GPC1(2), S3C_GPIO_SFN(4));
		s3c_gpio_cfgpin(S5PV210_GPC1(3), S3C_GPIO_SFN(4));
		s3c_gpio_cfgpin(S5PV210_GPC1(4), S3C_GPIO_SFN(4));
		break;

	case 0:
		s3c_gpio_cfgpin(S5PV210_GPI(0), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPI(1), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPI(2), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPI(3), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPI(4), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPI(5), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPI(6), S3C_GPIO_SFN(2));
		break;

	default:
		printk(KERN_ERR "Invalid Device %d\n", pdev->id);
		return -EINVAL;
	}

	return 0;
}

static struct s3c_audio_pdata s3c_i2s_pdata = {
	.cfg_gpio = s5pv210_cfg_i2s,
};

static struct resource s5pv210_iis0_resource[] = {
	[0] = {
		.start = S5PV210_PA_IIS0,
		.end   = S5PV210_PA_IIS0 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_I2S0_TX,
		.end   = DMACH_I2S0_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_I2S0_RX,
		.end   = DMACH_I2S0_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv210_device_iis0 = {
	.name		  = "s3c64xx-iis",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(s5pv210_iis0_resource),
	.resource	  = s5pv210_iis0_resource,
	.dev = {
		.platform_data = &s3c_i2s_pdata,
	},
};

static struct resource s5pv210_iis1_resource[] = {
	[0] = {
		.start = S5PV210_PA_IIS1,
		.end   = S5PV210_PA_IIS1 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_I2S1_TX,
		.end   = DMACH_I2S1_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_I2S1_RX,
		.end   = DMACH_I2S1_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv210_device_iis1 = {
	.name		  = "s3c64xx-iis",
	.id		  = 1,
	.num_resources	  = ARRAY_SIZE(s5pv210_iis1_resource),
	.resource	  = s5pv210_iis1_resource,
	.dev = {
		.platform_data = &s3c_i2s_pdata,
	},
};

static struct resource s5pv210_iis2_resource[] = {
	[0] = {
		.start = S5PV210_PA_IIS2,
		.end   = S5PV210_PA_IIS2 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_I2S2_TX,
		.end   = DMACH_I2S2_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_I2S2_RX,
		.end   = DMACH_I2S2_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv210_device_iis2 = {
	.name		  = "s3c64xx-iis",
	.id		  = 2,
	.num_resources	  = ARRAY_SIZE(s5pv210_iis2_resource),
	.resource	  = s5pv210_iis2_resource,
	.dev = {
		.platform_data = &s3c_i2s_pdata,
	},
};

/* PCM Controller platform_devices */

static int s5pv210_pcm_cfg_gpio(struct platform_device *pdev)
{
	switch (pdev->id) {
	case 0:
		s3c_gpio_cfgpin(S5PV210_GPI(0), S3C_GPIO_SFN(3));
		s3c_gpio_cfgpin(S5PV210_GPI(1), S3C_GPIO_SFN(3));
		s3c_gpio_cfgpin(S5PV210_GPI(2), S3C_GPIO_SFN(3));
		s3c_gpio_cfgpin(S5PV210_GPI(3), S3C_GPIO_SFN(3));
		s3c_gpio_cfgpin(S5PV210_GPI(4), S3C_GPIO_SFN(3));
		break;
	case 1:
		s3c_gpio_cfgpin(S5PV210_GPC0(0), S3C_GPIO_SFN(3));
		s3c_gpio_cfgpin(S5PV210_GPC0(1), S3C_GPIO_SFN(3));
		s3c_gpio_cfgpin(S5PV210_GPC0(2), S3C_GPIO_SFN(3));
		s3c_gpio_cfgpin(S5PV210_GPC0(3), S3C_GPIO_SFN(3));
		s3c_gpio_cfgpin(S5PV210_GPC0(4), S3C_GPIO_SFN(3));
		break;
	case 2:
		s3c_gpio_cfgpin(S5PV210_GPC1(0), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPC1(1), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPC1(2), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPC1(3), S3C_GPIO_SFN(2));
		s3c_gpio_cfgpin(S5PV210_GPC1(4), S3C_GPIO_SFN(2));
		break;
	default:
		printk(KERN_DEBUG "Invalid PCM Controller number!");
		return -EINVAL;
	}

	return 0;
}

static struct s3c_audio_pdata s3c_pcm_pdata = {
	.cfg_gpio = s5pv210_pcm_cfg_gpio,
};

static struct resource s5pv210_pcm0_resource[] = {
	[0] = {
		.start = S5PV210_PA_PCM0,
		.end   = S5PV210_PA_PCM0 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_PCM0_TX,
		.end   = DMACH_PCM0_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_PCM0_RX,
		.end   = DMACH_PCM0_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv210_device_pcm0 = {
	.name		  = "samsung-pcm",
	.id		  = 0,
	.num_resources	  = ARRAY_SIZE(s5pv210_pcm0_resource),
	.resource	  = s5pv210_pcm0_resource,
	.dev = {
		.platform_data = &s3c_pcm_pdata,
	},
};

static struct resource s5pv210_pcm1_resource[] = {
	[0] = {
		.start = S5PV210_PA_PCM1,
		.end   = S5PV210_PA_PCM1 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_PCM1_TX,
		.end   = DMACH_PCM1_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_PCM1_RX,
		.end   = DMACH_PCM1_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv210_device_pcm1 = {
	.name		  = "samsung-pcm",
	.id		  = 1,
	.num_resources	  = ARRAY_SIZE(s5pv210_pcm1_resource),
	.resource	  = s5pv210_pcm1_resource,
	.dev = {
		.platform_data = &s3c_pcm_pdata,
	},
};

static struct resource s5pv210_pcm2_resource[] = {
	[0] = {
		.start = S5PV210_PA_PCM2,
		.end   = S5PV210_PA_PCM2 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_PCM2_TX,
		.end   = DMACH_PCM2_TX,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_PCM2_RX,
		.end   = DMACH_PCM2_RX,
		.flags = IORESOURCE_DMA,
	},
};

struct platform_device s5pv210_device_pcm2 = {
	.name		  = "samsung-pcm",
	.id		  = 2,
	.num_resources	  = ARRAY_SIZE(s5pv210_pcm2_resource),
	.resource	  = s5pv210_pcm2_resource,
	.dev = {
		.platform_data = &s3c_pcm_pdata,
	},
};

/* AC97 Controller platform devices */

static int s5pv210_ac97_cfg_gpio(struct platform_device *pdev)
{
	s3c_gpio_cfgpin(S5PV210_GPC0(0), S3C_GPIO_SFN(4));
	s3c_gpio_cfgpin(S5PV210_GPC0(1), S3C_GPIO_SFN(4));
	s3c_gpio_cfgpin(S5PV210_GPC0(2), S3C_GPIO_SFN(4));
	s3c_gpio_cfgpin(S5PV210_GPC0(3), S3C_GPIO_SFN(4));
	s3c_gpio_cfgpin(S5PV210_GPC0(4), S3C_GPIO_SFN(4));

	return 0;
}

static struct resource s5pv210_ac97_resource[] = {
	[0] = {
		.start = S5PV210_PA_AC97,
		.end   = S5PV210_PA_AC97 + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_AC97_PCMOUT,
		.end   = DMACH_AC97_PCMOUT,
		.flags = IORESOURCE_DMA,
	},
	[2] = {
		.start = DMACH_AC97_PCMIN,
		.end   = DMACH_AC97_PCMIN,
		.flags = IORESOURCE_DMA,
	},
	[3] = {
		.start = DMACH_AC97_MICIN,
		.end   = DMACH_AC97_MICIN,
		.flags = IORESOURCE_DMA,
	},
	[4] = {
		.start = IRQ_AC97,
		.end   = IRQ_AC97,
		.flags = IORESOURCE_IRQ,
	},
};

static struct s3c_audio_pdata s3c_ac97_pdata = {
	.cfg_gpio = s5pv210_ac97_cfg_gpio,
};

static u64 s5pv210_ac97_dmamask = DMA_BIT_MASK(32);

struct platform_device s5pv210_device_ac97 = {
	.name		  = "s3c-ac97",
	.id		  = -1,
	.num_resources	  = ARRAY_SIZE(s5pv210_ac97_resource),
	.resource	  = s5pv210_ac97_resource,
	.dev = {
		.platform_data = &s3c_ac97_pdata,
		.dma_mask = &s5pv210_ac97_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
};

static int s5pv210_spdif_cfg_gpio(struct platform_device *pdev)
{
	s3c_gpio_cfgpin(S5PV210_GPC1(0), (0x3)<<0);
	s3c_gpio_cfgpin(S5PV210_GPC1(1), (0x3)<<4);

	return 0;
}

static struct resource s5pv210_spdif_resource[] = {
	[0] = {
		.start = S5PV210_PA_SPDIF,
		.end   = S5PV210_PA_SPDIF + 0x100 - 1,
		.flags = IORESOURCE_MEM,
	},
	[1] = {
		.start = DMACH_SPDIF,
		.end   = DMACH_SPDIF,
		.flags = IORESOURCE_DMA,
	},
};

static struct s3c_audio_pdata s5pv210_spdif_pdata = {
	.cfg_gpio = s5pv210_spdif_cfg_gpio,
};

static u64 s5pv210_spdif_dmamask = DMA_BIT_MASK(32);

struct platform_device s5pv210_device_spdif = {
	.name		= "samsung-spdif",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(s5pv210_spdif_resource),
	.resource	= s5pv210_spdif_resource,
	.dev = {
		.platform_data = &s5pv210_spdif_pdata,
		.dma_mask = &s5pv210_spdif_dmamask,
		.coherent_dma_mask = DMA_BIT_MASK(32),
	},
};
