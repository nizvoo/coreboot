/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2010-2017 Advanced Micro Devices, Inc.
 * Copyright (C) 2014 Sage Electronic Engineering, LLC
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __STONEYRIDGE_H__
#define __STONEYRIDGE_H__

#include <arch/io.h>
#include <types.h>
#include <device/pci_ids.h>
#include <device/device.h>
#include <device/pci_def.h>
#include <soc/iomap.h>
#include "chip.h"

/* PSP at D8F0 */
#define PSP_MAILBOX_BAR			PCI_BASE_ADDRESS_4 /* BKDG: "BAR3" */
#define PSP_BAR_ENABLES			0x48
#define  PSP_MAILBOX_BAR_EN		0x10

/* Power management index/data registers */
#define BIOSRAM_INDEX			0xcd4
#define BIOSRAM_DATA			0xcd5
#define PM_INDEX			0xcd6
#define PM_DATA				0xcd7
#define PM2_INDEX			0xcd0
#define PM2_DATA			0xcd1

#define PM_PCI_CTRL			0x08
#define   FORCE_SLPSTATE_RETRY		BIT(25)
#define   FORCE_STPCLK_RETRY		BIT(24)
#define PM_ACPI_MMIO_EN			0x24
#define PM_SERIRQ_CONF			0x54
#define   PM_SERIRQ_NUM_BITS_17		0x0000
#define   PM_SERIRQ_NUM_BITS_18		0x0004
#define   PM_SERIRQ_NUM_BITS_19		0x0008
#define   PM_SERIRQ_NUM_BITS_20		0x000c
#define   PM_SERIRQ_NUM_BITS_21		0x0010
#define   PM_SERIRQ_NUM_BITS_22		0x0014
#define   PM_SERIRQ_NUM_BITS_23		0x0018
#define   PM_SERIRQ_NUM_BITS_24		0x001c
#define   PM_SERIRQ_MODE		BIT(6)
#define   PM_SERIRQ_ENABLE		BIT(7)

#define PM_EVT_BLK			0x60
#define   WAK_STS			BIT(15) /*AcpiPmEvtBlkx00 Pm1Status */
#define   PCIEXPWAK_STS			BIT(14)
#define   RTC_STS			BIT(10)
#define   PWRBTN_STS			BIT(8)
#define   GBL_STS			BIT(5)
#define   BM_STS			BIT(4)
#define   TIMER_STS			BIT(0)
#define   PCIEXPWAK_DIS			BIT(14) /*AcpiPmEvtBlkx02 Pm1Enable */
#define   RTC_EN			BIT(10)
#define   PWRBTN_EN			BIT(8)
#define   GBL_EN			BIT(5)
#define   TIMER_STS			BIT(0)
#define PM1_CNT_BLK			0x62
#define PM_TMR_BLK			0x64
#define PM_CPU_CTRL			0x66
#define PM_GPE0_BLK			0x68
#define PM_ACPI_SMI_CMD			0x6a
#define PM_ACPI_CONF			0x74
#define   PM_ACPI_DECODE_STD		BIT(0)
#define   PM_ACPI_GLOBAL_EN		BIT(1)
#define   PM_ACPI_RTC_EN_EN		BIT(2)
#define   PM_ACPI_TIMER_EN_EN		BIT(4)
#define   PM_ACPI_MASK_ARB_DIS		BIT(6)
#define   PM_ACPI_BIOS_RLS		BIT(7)
#define   PM_ACPI_PWRBTNEN_EN		BIT(8)
#define   PM_ACPI_REDUCED_HW_EN		BIT(9)
#define   PM_ACPI_BLOCK_PCIE_PME	BIT(24)
#define   PM_ACPI_PCIE_WAK_MASK		BIT(25)
#define   PM_ACPI_WAKE_AS_GEVENT	BIT(27)
#define   PM_ACPI_NB_PME_GEVENT		BIT(28)
#define   PM_ACPI_RTC_WAKE_EN		BIT(29)
#define PM_RST_CTRL1			0xbe
#define   SLPTYPE_CONTROL_EN		BIT(5)
#define PM_PMIO_DEBUG			0xd2
#define PM_MANUAL_RESET			0xd3
#define PM_HUD_SD_FLASH_CTRL		0xe7
#define PM_YANG_SD_FLASH_CTRL		0xe8
#define PM_PCIB_CFG			0xea
#define PM_LPC_GATING			0xec
#define   PM_LPC_AB_NO_BYPASS_EN	BIT(2)
#define   PM_LPC_A20_EN			BIT(1)
#define   PM_LPC_ENABLE			BIT(0)

#define SPIROM_BASE_ADDRESS_REGISTER	0xa0
#define   ROUTE_TPM_2_SPI		BIT(3)
#define   SPI_ABORT_ENABLE		BIT(2)
#define   SPI_ROM_ENABLE		BIT(1)
#define   SPI_ROM_ALT_ENABLE		BIT(0)
#define   SPI_PRESERVE_BITS		(BIT(0) | BIT(1) | BIT(2) | BIT(3))

#define LPC_PCI_CONTROL			0x40
#define   LEGACY_DMA_EN			BIT(2)

#define LPC_IO_PORT_DECODE_ENABLE	0x44
#define   DECODE_ENABLE_PARALLEL_PORT0	BIT(0)
#define   DECODE_ENABLE_PARALLEL_PORT1	BIT(1)
#define   DECODE_ENABLE_PARALLEL_PORT2	BIT(2)
#define   DECODE_ENABLE_PARALLEL_PORT3	BIT(3)
#define   DECODE_ENABLE_PARALLEL_PORT4	BIT(4)
#define   DECODE_ENABLE_PARALLEL_PORT5	BIT(5)
#define   DECODE_ENABLE_SERIAL_PORT0	BIT(6)
#define   DECODE_ENABLE_SERIAL_PORT1	BIT(7)
#define   DECODE_ENABLE_SERIAL_PORT2	BIT(8)
#define   DECODE_ENABLE_SERIAL_PORT3	BIT(9)
#define   DECODE_ENABLE_SERIAL_PORT4	BIT(10)
#define   DECODE_ENABLE_SERIAL_PORT5	BIT(11)
#define   DECODE_ENABLE_SERIAL_PORT6	BIT(12)
#define   DECODE_ENABLE_SERIAL_PORT7	BIT(13)
#define   DECODE_ENABLE_AUDIO_PORT0	BIT(14)
#define   DECODE_ENABLE_AUDIO_PORT1	BIT(15)
#define   DECODE_ENABLE_AUDIO_PORT2	BIT(16)
#define   DECODE_ENABLE_AUDIO_PORT3	BIT(17)
#define   DECODE_ENABLE_MIDI_PORT0	BIT(18)
#define   DECODE_ENABLE_MIDI_PORT1	BIT(19)
#define   DECODE_ENABLE_MIDI_PORT2	BIT(20)
#define   DECODE_ENABLE_MIDI_PORT3	BIT(21)
#define   DECODE_ENABLE_MSS_PORT0	BIT(22)
#define   DECODE_ENABLE_MSS_PORT1	BIT(23)
#define   DECODE_ENABLE_MSS_PORT2	BIT(24)
#define   DECODE_ENABLE_MSS_PORT3	BIT(25)
#define   DECODE_ENABLE_FDC_PORT0	BIT(26)
#define   DECODE_ENABLE_FDC_PORT1	BIT(27)
#define   DECODE_ENABLE_GAME_PORT	BIT(28)
#define   DECODE_ENABLE_KBC_PORT	BIT(29)
#define   DECODE_ENABLE_ACPIUC_PORT	BIT(30)
#define   DECODE_ENABLE_ADLIB_PORT	BIT(31)

#define LPC_IO_OR_MEM_DECODE_ENABLE	0x48
#define   LPC_WIDEIO2_ENABLE		BIT(25)
#define   LPC_WIDEIO1_ENABLE		BIT(24)
#define   DECODE_IO_PORT_ENABLE6	BIT(23)
#define   DECODE_IO_PORT_ENABLE5	BIT(22)
#define   DECODE_IO_PORT_ENABLE4	BIT(21)
#define   DECODE_IO_PORT_ENABLE3	BIT(19)
#define   DECODE_IO_PORT_ENABLE2	BIT(18)
#define   DECODE_IO_PORT_ENABLE1	BIT(17)
#define   DECODE_IO_PORT_ENABLE0	BIT(16)
#define   LPC_SYNC_TIMEOUT_COUNT_ENABLE	BIT(7)
#define   LPC_WIDEIO0_ENABLE		BIT(2)
/* Assuming word access to higher word (register 0x4a) */
#define LPC_IO_OR_MEM_DEC_EN_HIGH	0x4a
#define   LPC_WIDEIO2_ENABLE_H		BIT(9)
#define   LPC_WIDEIO1_ENABLE_H		BIT(8)
#define   DECODE_IO_PORT_ENABLE6_H	BIT(7)
#define   DECODE_IO_PORT_ENABLE5_H	BIT(6)
#define   DECODE_IO_PORT_ENABLE4_H	BIT(5)
#define   DECODE_IO_PORT_ENABLE3_H	BIT(3)
#define   DECODE_IO_PORT_ENABLE2_H	BIT(2)
#define   DECODE_IO_PORT_ENABLE1_H	BIT(1)
#define   DECODE_IO_PORT_ENABLE0_H	BIT(0)

/*
 * Register 0x64 is 32-bit, composed by two 16-bit sub-registers.
 * For ease of access, each sub-register is declared separetely.
 */
#define LPC_WIDEIO_GENERIC_PORT		0x64
#define LPC_WIDEIO1_GENERIC_PORT	0x66
#define ROM_ADDRESS_RANGE1_START	0x68
#define ROM_ADDRESS_RANGE1_END		0x6a
#define ROM_ADDRESS_RANGE2_START	0x6c
#define ROM_ADDRESS_RANGE2_END		0x6e

#define LPC_ALT_WIDEIO_RANGE_ENABLE	0x74
#define   LPC_ALT_WIDEIO2_ENABLE	BIT(3)
#define   LPC_ALT_WIDEIO1_ENABLE	BIT(2)
#define   LPC_ALT_WIDEIO0_ENABLE	BIT(0)

#define LPC_MISC_CONTROL_BITS		0x78
#define   LPC_NOHOG			BIT(0)

#define LPC_WIDEIO2_GENERIC_PORT	0x90

/*
 * LPC register 0xb8 is DWORD, here there are definitions for byte
 * access. For example, bits 31-24 are accessed through byte access
 * at register 0xbb ().
 */
#define LPC_ROM_DMA_EC_HOST_CONTROL	0xb8

#define LPC_HOST_CONTROL		0xbb
#define   SPI_FROM_HOST_PREFETCH_EN	BIT(0)

/* SPI Controller */
#define SPI_FIFO_DEPTH			8

#define SPI_CNTRL0			0x00
#define   SPI_BUSY			BIT(31)
#define   SPI_READ_MODE_MASK		(BIT(30) | BIT(29) | BIT(18))
/* Nominal is 16.7MHz on older devices, 33MHz on newer */
#define   SPI_READ_MODE_NOM		0x00000000
#define   SPI_READ_MODE_DUAL112		(          BIT(29)          )
#define   SPI_READ_MODE_QUAD114		(          BIT(29) | BIT(18))
#define   SPI_READ_MODE_DUAL122		(BIT(30)                    )
#define   SPI_READ_MODE_QUAD144		(BIT(30) |           BIT(18))
#define   SPI_READ_MODE_NORMAL66	(BIT(30) | BIT(29)          )
#define   SPI_READ_MODE_FAST		(BIT(30) | BIT(29) | BIT(18))
#define   SPI_FIFO_PTR_CLR		BIT(20)
#define   SPI_ARB_ENABLE		BIT(19)
#define   EXEC_OPCODE			BIT(16)
#define SPI_REG_CNTRL01			0x01
#define SPI_REG_CNTRL02			0x02
#define   SPI_FIFO_PTR_CLR02		(SPI_FIFO_PTR_CLR >> 16)
#define SPI_CNTRL1			0x0c
#define  SPI_FIFO_PTR_MASK		(BIT(8) | BIT(9) | BIT(10))
#define SPI_CNTRL11			0x0d
#define  SPI_FIFO_PTR_MASK11		(SPI_FIFO_PTR_MASK >> 8)

#define SPI100_SPEED_CONFIG		0x22
/* Use SPI_SPEED_16M-SPI_SPEED_66M below for the southbridge */
#define   SPI_CNTRL1_SPEED_MASK		(BIT(15) | BIT(14) | BIT(13) | BIT(12))
#define   SPI_NORM_SPEED_SH		12
#define   SPI_FAST_SPEED_SH		8

#define SPI_EXT_INDEX			0x1e
#define SPI_EXT_DATA			0x1f
#define   SPI_DDR_CMD			0x0
#define   SPI_QDR_CMD			0x1
#define   SPI_DPR_CMD			0x2
#define   SPI_QPR_CMD			0x3
#define   SPI_MODE_BYTE			0x4
#define   SPI_TX_BYTE_COUNT		0x5
#define   SPI_RX_BYTE_COUNT		0x6
#define   SPI_SPI_DATA_FIFO_PTR		0x7

#define SPI100_ENABLE			0x20
#define   SPI_USE_SPI100		BIT(0)

#define SPI100_SPEED_CONFIG		0x22
#define   SPI_SPEED_66M			(0x0)
#define   SPI_SPEED_33M			(                  BIT(0))
#define   SPI_SPEED_22M			(         BIT(1)         )
#define   SPI_SPEED_16M			(         BIT(1) | BIT(0))
#define   SPI_SPEED_100M		(BIT(2)                  )
#define   SPI_SPEED_800K		(BIT(2) |          BIT(0))
#define   SPI_NORM_SPEED_NEW_SH		12
#define   SPI_FAST_SPEED_NEW_SH		8
#define   SPI_ALT_SPEED_NEW_SH		4
#define   SPI_TPM_SPEED_NEW_SH		0

#define SPI100_HOST_PREF_CONFIG		0x2c
#define   SPI_RD4DW_EN_HOST		BIT(15)

#define FCH_MISC_REG40_OSCOUT1_EN	BIT(2)

/* IO 0xcf9 - Reset control port*/
#define   FULL_RST			BIT(3)
#define   RST_CMD			BIT(2)
#define   SYS_RST			BIT(1)

/* PMx10 - Power Reset Config */
#define PWR_RESET_CFG			0x10
#define   TOGGLE_ALL_PWR_GOOD		BIT(1)

static inline int sb_sata_enable(void)
{
	/* True if IDE or AHCI. */
	return (CONFIG_STONEYRIDGE_SATA_MODE == 0) ||
					(CONFIG_STONEYRIDGE_SATA_MODE == 2);
}

static inline int sb_ide_enable(void)
{
	/* True if IDE or LEGACY IDE. */
	return (CONFIG_STONEYRIDGE_SATA_MODE == 0) ||
					(CONFIG_STONEYRIDGE_SATA_MODE == 3);
}

void sb_enable_rom(void);
void configure_stoneyridge_uart(void);
void sb_clk_output_48Mhz(void);
void sb_disable_4dw_burst(void);
void sb_enable(device_t dev);
void southbridge_final(void *chip_info);
void southbridge_init(void *chip_info);
void sb_lpc_port80(void);
void sb_lpc_decode(void);
void sb_pci_port80(void);
void sb_read_mode(u32 mode);
void sb_set_spi100(u16 norm, u16 fast, u16 alt, u16 tpm);
void sb_set_readspeed(u16 norm, u16 fast);
void sb_tpm_decode_spi(void);
void lpc_wideio_512_window(uint16_t base);
void lpc_wideio_16_window(uint16_t base);
u8 pm_read8(u8 reg);
u16 pm_read16(u8 reg);
u32 pm_read32(u8 reg);
void pm_write8(u8 reg, u8 value);
void pm_write16(u8 reg, u16 value);
void pm_write32(u8 reg, u32 value);
uint8_t smi_read8(uint8_t offset);
uint16_t smi_read16(uint8_t offset);
uint32_t smi_read32(uint8_t offset);
void smi_write8(uint8_t offset, uint8_t value);
void smi_write16(uint8_t offset, uint16_t value);
void smi_write32(uint8_t offset, uint32_t value);
uint16_t pm_acpi_pm_cnt_blk(void);
uint16_t pm_acpi_pm_evt_blk(void);
int s3_load_nvram_early(int size, u32 *old_dword, int nvram_pos);
int s3_save_nvram_early(u32 dword, int size, int  nvram_pos);
void bootblock_fch_early_init(void);

#endif /* __STONEYRIDGE_H__ */
