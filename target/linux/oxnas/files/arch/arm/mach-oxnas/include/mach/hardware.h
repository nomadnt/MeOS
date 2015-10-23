/*
 * arch/arm/mach-0x820/include/mach/hardware.h
 *
 * Copyright (C) 2009 Oxford Semiconductor Ltd
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef __ASM_ARCH_HARDWARE_H
#define __ASM_ARCH_HARDWARE_H

#include <linux/io.h>
#include <mach/iomap.h>

/*
 * Location of flags and vectors in SRAM for controlling the booting of the
 * secondary ARM11 processors.
 */

#define OXNAS_SCU_BASE_VA		OXNAS_PERCPU_BASE_VA
#define OXNAS_GICN_BASE_VA(n)		(OXNAS_PERCPU_BASE_VA + 0x200 + n*0x100)

#define HOLDINGPEN_CPU			IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xc8)
#define HOLDINGPEN_LOCATION		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xc4)

/**
 * System block reset and clock control
 */
#define SYS_CTRL_PCI_STAT		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x20)
#define SYSCTRL_CLK_STAT		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x24)
#define SYS_CTRL_CLK_SET_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x2C)
#define SYS_CTRL_CLK_CLR_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x30)
#define SYS_CTRL_RST_SET_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x34)
#define SYS_CTRL_RST_CLR_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x38)

#define SYS_CTRL_PLLSYS_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x48)
#define SYS_CTRL_CLK_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x64)
#define SYS_CTRL_PLLSYS_KEY_CTRL	IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x6C)
#define SYS_CTRL_GMAC_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x78)
#define SYS_CTRL_GMAC_DELAY_CTRL	IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x100)

/* Scratch registers */
#define SYS_CTRL_SCRATCHWORD0		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xc4)
#define SYS_CTRL_SCRATCHWORD1		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xc8)
#define SYS_CTRL_SCRATCHWORD2		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xcc)
#define SYS_CTRL_SCRATCHWORD3		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xd0)

#define SYS_CTRL_PLLA_CTRL0		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x1F0)
#define SYS_CTRL_PLLA_CTRL1		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x1F4)
#define SYS_CTRL_PLLA_CTRL2		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x1F8)
#define SYS_CTRL_PLLA_CTRL3		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x1FC)

#define SYS_CTRL_USBHSMPH_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x40)
#define SYS_CTRL_USBHSMPH_STAT		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x44)
#define SYS_CTRL_REF300_DIV		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xF8)
#define SYS_CTRL_USBHSPHY_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x84)
#define SYS_CTRL_USB_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x90)

/* pcie */
#define SYS_CTRL_HCSL_CTRL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x114)

/* System control multi-function pin function selection */
#define SYS_CTRL_SECONDARY_SEL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x14)
#define SYS_CTRL_TERTIARY_SEL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x8c)
#define SYS_CTRL_QUATERNARY_SEL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x94)
#define SYS_CTRL_DEBUG_SEL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0x9c)
#define SYS_CTRL_ALTERNATIVE_SEL	IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xa4)
#define SYS_CTRL_PULLUP_SEL		IOMEM(OXNAS_SYSCRTL_BASE_VA + 0xac)

/* Secure control multi-function pin function selection */
#define SEC_CTRL_SECONDARY_SEL		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x14)
#define SEC_CTRL_TERTIARY_SEL		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x8c)
#define SEC_CTRL_QUATERNARY_SEL		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x94)
#define SEC_CTRL_DEBUG_SEL		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x9c)
#define SEC_CTRL_ALTERNATIVE_SEL	IOMEM(OXNAS_SECCRTL_BASE_VA + 0xa4)
#define SEC_CTRL_PULLUP_SEL		IOMEM(OXNAS_SECCRTL_BASE_VA + 0xac)

#define SEC_CTRL_COPRO_CTRL		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x68)
#define SEC_CTRL_SECURE_CTRL		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x98)
#define SEC_CTRL_LEON_DEBUG		IOMEM(OXNAS_SECCRTL_BASE_VA + 0xF0)
#define SEC_CTRL_PLLB_DIV_CTRL		IOMEM(OXNAS_SECCRTL_BASE_VA + 0xF8)
#define SEC_CTRL_PLLB_CTRL0		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x1F0)
#define SEC_CTRL_PLLB_CTRL1		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x1F4)
#define SEC_CTRL_PLLB_CTRL8		IOMEM(OXNAS_SECCRTL_BASE_VA + 0x1F4)

#define RPSA_IRQ_SOFT			IOMEM(OXNAS_RPSA_BASE_VA + 0x10)
#define RPSA_FIQ_ENABLE			IOMEM(OXNAS_RPSA_BASE_VA + 0x108)
#define RPSA_FIQ_DISABLE		IOMEM(OXNAS_RPSA_BASE_VA + 0x10C)
#define RPSA_FIQ_IRQ_TO_FIQ		IOMEM(OXNAS_RPSA_BASE_VA + 0x1FC)

#define RPSC_IRQ_SOFT			IOMEM(OXNAS_RPSC_BASE_VA + 0x10)
#define RPSC_FIQ_ENABLE			IOMEM(OXNAS_RPSC_BASE_VA + 0x108)
#define RPSC_FIQ_DISABLE		IOMEM(OXNAS_RPSC_BASE_VA + 0x10C)
#define RPSC_FIQ_IRQ_TO_FIQ		IOMEM(OXNAS_RPSC_BASE_VA + 0x1FC)

#define RPSA_TIMER2_VAL			IOMEM(OXNAS_RPSA_BASE_VA + 0x224)

#define REF300_DIV_INT_SHIFT		8
#define REF300_DIV_FRAC_SHIFT		0
#define REF300_DIV_INT(val)		((val) << REF300_DIV_INT_SHIFT)
#define REF300_DIV_FRAC(val)		((val) << REF300_DIV_FRAC_SHIFT)

#define USBHSPHY_SUSPENDM_MANUAL_ENABLE		16
#define USBHSPHY_SUSPENDM_MANUAL_STATE		15
#define USBHSPHY_ATE_ESET			14
#define USBHSPHY_TEST_DIN			6
#define USBHSPHY_TEST_ADD			2
#define USBHSPHY_TEST_DOUT_SEL			1
#define USBHSPHY_TEST_CLK			0

#define USB_CTRL_USBAPHY_CKSEL_SHIFT	5
#define USB_CLK_XTAL0_XTAL1		(0 << USB_CTRL_USBAPHY_CKSEL_SHIFT)
#define USB_CLK_XTAL0			(1 << USB_CTRL_USBAPHY_CKSEL_SHIFT)
#define USB_CLK_INTERNAL		(2 << USB_CTRL_USBAPHY_CKSEL_SHIFT)

#define USBAMUX_DEVICE			BIT(4)

#define USBPHY_REFCLKDIV_SHIFT		2
#define USB_PHY_REF_12MHZ		(0 << USBPHY_REFCLKDIV_SHIFT)
#define USB_PHY_REF_24MHZ		(1 << USBPHY_REFCLKDIV_SHIFT)
#define USB_PHY_REF_48MHZ		(2 << USBPHY_REFCLKDIV_SHIFT)

#define USB_CTRL_USB_CKO_SEL_BIT	0

#define USB_INT_CLK_XTAL		0
#define USB_INT_CLK_REF300		2
#define USB_INT_CLK_PLLB		3

#define SYS_CTRL_GMAC_CKEN_RX_IN	14
#define SYS_CTRL_GMAC_CKEN_RXN_OUT	13
#define SYS_CTRL_GMAC_CKEN_RX_OUT	12
#define SYS_CTRL_GMAC_CKEN_TX_IN	10
#define SYS_CTRL_GMAC_CKEN_TXN_OUT	9
#define SYS_CTRL_GMAC_CKEN_TX_OUT	8
#define SYS_CTRL_GMAC_RX_SOURCE		7
#define SYS_CTRL_GMAC_TX_SOURCE		6
#define SYS_CTRL_GMAC_LOW_TX_SOURCE	4
#define SYS_CTRL_GMAC_AUTO_TX_SOURCE	3
#define SYS_CTRL_GMAC_RGMII		2
#define SYS_CTRL_GMAC_SIMPLE_MUX	1
#define SYS_CTRL_GMAC_CKEN_GTX		0
#define SYS_CTRL_GMAC_TX_VARDELAY_SHIFT		0
#define SYS_CTRL_GMAC_TXN_VARDELAY_SHIFT	8
#define SYS_CTRL_GMAC_RX_VARDELAY_SHIFT		16
#define SYS_CTRL_GMAC_RXN_VARDELAY_SHIFT	24
#define SYS_CTRL_GMAC_TX_VARDELAY(d)	((d)<<SYS_CTRL_GMAC_TX_VARDELAY_SHIFT)
#define SYS_CTRL_GMAC_TXN_VARDELAY(d)	((d)<<SYS_CTRL_GMAC_TXN_VARDELAY_SHIFT)
#define SYS_CTRL_GMAC_RX_VARDELAY(d)	((d)<<SYS_CTRL_GMAC_RX_VARDELAY_SHIFT)
#define SYS_CTRL_GMAC_RXN_VARDELAY(d)	((d)<<SYS_CTRL_GMAC_RXN_VARDELAY_SHIFT)

#define PLLB_BYPASS			1
#define PLLB_ENSAT			3
#define PLLB_OUTDIV			4
#define PLLB_REFDIV			8
#define PLLB_DIV_INT_SHIFT		8
#define PLLB_DIV_FRAC_SHIFT		0
#define PLLB_DIV_INT(val)		((val) << PLLB_DIV_INT_SHIFT)
#define PLLB_DIV_FRAC(val)		((val) << PLLB_DIV_FRAC_SHIFT)

#define SYS_CTRL_CKCTRL_PCI_DIV_BIT	0
#define SYS_CTRL_CKCTRL_SLOW_BIT	8

#define SYS_CTRL_UART2_DEQ_EN		0
#define SYS_CTRL_UART3_DEQ_EN		1
#define SYS_CTRL_UART3_IQ_EN		2
#define SYS_CTRL_UART4_IQ_EN		3
#define SYS_CTRL_UART4_NOT_PCI_MODE	4

#define SYS_CTRL_PCI_CTRL1_PCI_STATIC_RQ_BIT	11

#define PLLA_REFDIV_MASK		0x3F
#define PLLA_REFDIV_SHIFT		8
#define PLLA_OUTDIV_MASK		0x7
#define PLLA_OUTDIV_SHIFT		4

/* bit numbers of clock control register */
#define SYS_CTRL_CLK_COPRO		0
#define SYS_CTRL_CLK_DMA		1
#define SYS_CTRL_CLK_CIPHER		2
#define SYS_CTRL_CLK_SD			3
#define SYS_CTRL_CLK_SATA		4
#define SYS_CTRL_CLK_I2S		5
#define SYS_CTRL_CLK_USBHS		6
#define SYS_CTRL_CLK_MACA		7
#define SYS_CTRL_CLK_MAC		SYS_CTRL_CLK_MACA
#define SYS_CTRL_CLK_PCIEA		8
#define SYS_CTRL_CLK_STATIC		9
#define SYS_CTRL_CLK_MACB		10
#define SYS_CTRL_CLK_PCIEB		11
#define SYS_CTRL_CLK_REF600		12
#define SYS_CTRL_CLK_USBDEV		13
#define SYS_CTRL_CLK_DDR		14
#define SYS_CTRL_CLK_DDRPHY		15
#define SYS_CTRL_CLK_DDRCK		16


/* bit numbers of reset control register */
#define SYS_CTRL_RST_SCU		0
#define SYS_CTRL_RST_COPRO		1
#define SYS_CTRL_RST_ARM0		2
#define SYS_CTRL_RST_ARM1		3
#define SYS_CTRL_RST_USBHS		4
#define SYS_CTRL_RST_USBHSPHYA		5
#define SYS_CTRL_RST_MACA		6
#define SYS_CTRL_RST_MAC		SYS_CTRL_RST_MACA
#define SYS_CTRL_RST_PCIEA		7
#define SYS_CTRL_RST_SGDMA		8
#define SYS_CTRL_RST_CIPHER		9
#define SYS_CTRL_RST_DDR		10
#define SYS_CTRL_RST_SATA		11
#define SYS_CTRL_RST_SATA_LINK		12
#define SYS_CTRL_RST_SATA_PHY		13
#define SYS_CTRL_RST_PCIEPHY		14
#define SYS_CTRL_RST_STATIC		15
#define SYS_CTRL_RST_GPIO		16
#define SYS_CTRL_RST_UART1		17
#define SYS_CTRL_RST_UART2		18
#define SYS_CTRL_RST_MISC		19
#define SYS_CTRL_RST_I2S		20
#define SYS_CTRL_RST_SD			21
#define SYS_CTRL_RST_MACB		22
#define SYS_CTRL_RST_PCIEB		23
#define SYS_CTRL_RST_VIDEO		24
#define SYS_CTRL_RST_DDR_PHY		25
#define SYS_CTRL_RST_USBHSPHYB		26
#define SYS_CTRL_RST_USBDEV		27
#define SYS_CTRL_RST_ARMDBG		29
#define SYS_CTRL_RST_PLLA		30
#define SYS_CTRL_RST_PLLB		31

#endif
