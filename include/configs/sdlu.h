/*
 * (C) Copyright 2001
 * Stuart Hughes <stuarth@lineo.com>
 * This file is based on similar values for other boards found in other
 * U-Boot config files, and some that I found in the mpc8260ads manual.
 *
 * Note: my board is a PILOT rev.
 * Note: the mpc8260ads doesn't come with a proper Ethernet MAC address.
 *
 * (C) Copyright 2003-2004 Arabella Software Ltd.
 * Yuli Barcohen <yuli@arabellasw.com>
 * Added support for SDRAM DIMMs SPD EEPROM, MII, JFFS2.
 * Ported to PQ2FADS-ZU and PQ2FADS-VR boards.
 * Ported to MPC8272ADS board.
 *
 * Copyright (c) 2005 MontaVista Software, Inc.
 * Vitaly Bordug <vbordug@ru.mvista.com>
 * Added support for PCI bridge on MPC8272ADS
 *
 * Copyright (C) Freescale Semiconductor, Inc. 2006-2009.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_H
#define __CONFIG_H

/*
 * High Level Configuration Options
 * (easy to change)
 */


#ifndef CONFIG_SYS_TEXT_BASE
#define CONFIG_SYS_TEXT_BASE	0xFFF00000	/* Standard: boot high */
#endif

#define CONFIG_CPM2		1	/* Has a CPM2 */

/*
 * Figure out if we are booting low via flash HRCW or high via the BCSR.
 */
#if (CONFIG_SYS_TEXT_BASE != 0xFFF00000)		/* Boot low (flash HRCW) */
#   define CONFIG_SYS_LOWBOOT		1
#endif

/* ADS flavours */
//#define CONFIG_SYS_8260ADS		1	/* MPC8260ADS */
//#define CONFIG_SYS_8266ADS		2	/* MPC8266ADS */
//#define CONFIG_SYS_PQ2FADS		3	/* PQ2FADS-ZU or PQ2FADS-VR */
//#define CONFIG_SYS_8272ADS		4	/* MPC8272ADS */

//#ifndef CONFIG_ADSTYPE
//#define CONFIG_ADSTYPE		CONFIG_SYS_8272ADS
//#endif /* CONFIG_ADSTYPE */

//#if CONFIG_ADSTYPE == CONFIG_SYS_8272ADS
//#define CONFIG_MPC8272		1
//#elif CONFIG_ADSTYPE == CONFIG_SYS_PQ2FADS
/*
 * Actually MPC8275, but the code is littered with ifdefs that
 * apply to both, or which use this ifdef to assume board-specific
 * details. :-(
 */
//#define CONFIG_MPC8272		1
//#else
//#define CONFIG_MPC8260		1
//#endif /* CONFIG_ADSTYPE == CONFIG_SYS_8272ADS */

//#define CONFIG_BOARD_EARLY_INIT_F 1	/* Call board_early_init_f	*/
#define CONFIG_RESET_PHY_R	1	/* Call reset_phy()		*/

/* allow serial and ethaddr to be overwritten */
#define CONFIG_ENV_OVERWRITE

/*
 * select serial console configuration
 *
 * if either CONFIG_CONS_ON_SMC or CONFIG_CONS_ON_SCC is selected, then
 * CONFIG_CONS_INDEX must be set to the channel number (1-2 for SMC, 1-4
 * for SCC).
 *
 * if CONFIG_CONS_NONE is defined, then the serial console routines must
 * defined elsewhere (for example, on the cogent platform, there are serial
 * ports on the motherboard which are used for the serial console - see
 * cogent/cma101/serial.[ch]).
 */
#define	CONFIG_CONS_ON_SMC		/* define if console on SMC */
#define CONFIG_CONS_INDEX	1	/* which serial channel for console */

/*
 * select ethernet configuration
 *
 * if either CONFIG_ETHER_ON_SCC or CONFIG_ETHER_ON_FCC is selected, then
 * CONFIG_ETHER_INDEX must be set to the channel number (1-4 for SCC, 1-3
 * for FCC)
 *
 * if CONFIG_ETHER_NONE is defined, then either the ethernet routines must be
 * defined elsewhere (as for the console), or CONFIG_CMD_NET must be unset.
 */

#define CONFIG_ETHER_ON_SCC	
#define CONFIG_ETHER_INDEX	1
#define CONFIG_SYS_CMXSCR_VALUE 0x37000000



#ifdef CONFIG_ETHER_ON_FCC

#define CONFIG_ETHER_INDEX	2	/* which SCC/FCC channel for ethernet */

#if   CONFIG_ETHER_INDEX == 1

# define CONFIG_SYS_PHY_ADDR		0
# define CONFIG_SYS_CMXFCR_VALUE1	(CMXFCR_RF1CS_CLK11 | CMXFCR_TF1CS_CLK10)
# define CONFIG_SYS_CMXFCR_MASK1	(CMXFCR_FC1 | CMXFCR_RF1CS_MSK | CMXFCR_TF1CS_MSK)

#elif CONFIG_ETHER_INDEX == 2

#if CONFIG_ADSTYPE == CONFIG_SYS_8272ADS	/* RxCLK is CLK15, TxCLK is CLK16 */
# define CONFIG_SYS_PHY_ADDR		3
# define CONFIG_SYS_CMXFCR_VALUE2	(CMXFCR_RF2CS_CLK15 | CMXFCR_TF2CS_CLK16)
#else					/* RxCLK is CLK13, TxCLK is CLK14 */
# define CONFIG_SYS_PHY_ADDR		0
# define CONFIG_SYS_CMXFCR_VALUE2	(CMXFCR_RF2CS_CLK13 | CMXFCR_TF2CS_CLK14)
#endif /* CONFIG_ADSTYPE == CONFIG_SYS_8272ADS */

# define CONFIG_SYS_CMXFCR_MASK2	(CMXFCR_FC2 | CMXFCR_RF2CS_MSK | CMXFCR_TF2CS_MSK)

#endif	/* CONFIG_ETHER_INDEX */

#define CONFIG_SYS_CPMFCR_RAMTYPE	0		/* BDs and buffers on 60x bus */
#define CONFIG_SYS_FCC_PSMR		(FCC_PSMR_FDE | FCC_PSMR_LPB)  /* Full duplex */

#define CONFIG_MII			/* MII PHY management		*/
#define CONFIG_BITBANGMII		/* bit-bang MII PHY management	*/
/*
 * GPIO pins used for bit-banged MII communications
 */
#define MDIO_PORT	2		/* Port C */
#define MDIO_DECLARE	volatile ioport_t *iop = ioport_addr ( \
				(immap_t *) CONFIG_SYS_IMMR, MDIO_PORT )
#define MDC_DECLARE	MDIO_DECLARE

#if CONFIG_ADSTYPE == CONFIG_SYS_8272ADS
#define CONFIG_SYS_MDIO_PIN	0x00002000	/* PC18 */
#define CONFIG_SYS_MDC_PIN	0x00001000	/* PC19 */
#else
#define CONFIG_SYS_MDIO_PIN	0x00400000	/* PC9	*/
#define CONFIG_SYS_MDC_PIN	0x00200000	/* PC10 */
#endif /* CONFIG_ADSTYPE == CONFIG_SYS_8272ADS */

#define MDIO_ACTIVE	(iop->pdir |=  CONFIG_SYS_MDIO_PIN)
#define MDIO_TRISTATE	(iop->pdir &= ~CONFIG_SYS_MDIO_PIN)
#define MDIO_READ	((iop->pdat &  CONFIG_SYS_MDIO_PIN) != 0)

#define MDIO(bit)	if(bit) iop->pdat |=  CONFIG_SYS_MDIO_PIN; \
			else	iop->pdat &= ~CONFIG_SYS_MDIO_PIN

#define MDC(bit)	if(bit) iop->pdat |=  CONFIG_SYS_MDC_PIN; \
			else	iop->pdat &= ~CONFIG_SYS_MDC_PIN

#define MIIDELAY	udelay(1)

#endif /* CONFIG_ETHER_ON_FCC */

/*PCI*/
#if 0
#if CONFIG_ADSTYPE >= CONFIG_SYS_PQ2FADS
//#define CONFIG_PCI
#define CONFIG_PCI_INDIRECT_BRIDGE
#define CONFIG_PCI_PNP
#define CONFIG_PCI_BOOTDELAY 0
#define CONFIG_PCI_SCAN_SHOW
#endif
#endif

#ifndef CONFIG_8260_CLKIN
#define CONFIG_8260_CLKIN	100000000	/* in Hz */
#endif

#define CONFIG_BAUDRATE		115200

#if defined(CONFIG_OF_LIBFDT)
#define OF_TBCLK		(bd->bi_busfreq / 4)
#endif



#define CONFIG_BOOTCOMMAND	"bootm fff80000"	/* autoboot command */
#define CONFIG_BOOTARGS		"root=/dev/mtdblock2"

#if defined(CONFIG_CMD_KGDB)
#undef	CONFIG_KGDB_ON_SMC		/* define if kgdb on SMC */
#define CONFIG_KGDB_ON_SCC		/* define if kgdb on SCC */
#undef	CONFIG_KGDB_NONE		/* define if kgdb on something else */
#define CONFIG_KGDB_INDEX	2	/* which serial channel for kgdb */
#define CONFIG_KGDB_BAUDRATE	115200	/* speed to run kgdb serial port at */
#endif

#define CONFIG_BZIP2	/* include support for bzip2 compressed images */
#undef	CONFIG_WATCHDOG /* disable platform specific watchdog */

/*
 * Miscellaneous configurable options
 */
#if defined(CONFIG_CMD_KGDB)
#define CONFIG_SYS_CBSIZE	1024		/* Console I/O Buffer Size  */
#else
#define CONFIG_SYS_CBSIZE	256			/* Console I/O Buffer Size  */
#endif
#define CONFIG_SYS_PBSIZE (CONFIG_SYS_CBSIZE+sizeof(CONFIG_SYS_PROMPT)+16)	/* Print Buffer Size */
#define CONFIG_SYS_MAXARGS	16			/* max number of command args	*/
#define CONFIG_SYS_BARGSIZE	CONFIG_SYS_CBSIZE	/* Boot Argument Buffer Size	*/

#define CONFIG_SYS_MEMTEST_START	0x00100000	/* memtest works on */
#define CONFIG_SYS_MEMTEST_END		0x00f00000	/* 1 ... 15 MB in DRAM	*/

#define CONFIG_SYS_LOAD_ADDR		0x400000	/* default load address */

#define CONFIG_SYS_BAUDRATE_TABLE	{ 9600, 19200, 38400, 57600, 115200, 230400 }


#define CONFIG_SYS_FLASH_BASE		0xFFE00000
#define CONFIG_SYS_MAX_FLASH_BANKS	1	/* max num of memory banks	*/
#define CONFIG_SYS_MAX_FLASH_SECT	1024	/* max num of sects on one chip */


/*
 * JFFS2 partitions
 *
 * Note: fake mtd_id used, no linux mtd map file
 */
#define MTDIDS_DEFAULT		"nor0=mpc8260ads-0"
#define MTDPARTS_DEFAULT	"mtdparts=mpc8260ads-0:-@1m(jffs2)"
#define CONFIG_SYS_JFFS2_SORT_FRAGMENTS

/* this is stuff came out of the Motorola docs */
#ifndef CONFIG_SYS_LOWBOOT
//#define CONFIG_SYS_DEFAULT_IMMR	0x0F010000
#endif

#define CONFIG_SYS_IMMR		0xF0000000
//#define CONFIG_SYS_BCSR		0xF4500000
//#define CONFIG_SYS_PCI_INT		0xF8200000
#define CONFIG_SYS_SDRAM_BASE		0x00000000
//#define CONFIG_SYS_LSDRAM_BASE		0xFD000000

#define RS232EN_1		0x02000002
#define RS232EN_2		0x01000001
#define FETHIEN1		0x08000008
#define FETH1_RST		0x04000004
#define FETHIEN2		0x10000000
#define FETH2_RST		0x08000000
#define BCSR_PCI_MODE		0x01000000

#define CONFIG_SYS_INIT_RAM_ADDR	CONFIG_SYS_IMMR
#define CONFIG_SYS_INIT_RAM_SIZE	0x2000	/* Size of used area in DPRAM	*/
#define CONFIG_SYS_GBL_DATA_OFFSET	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_OFFSET	CONFIG_SYS_GBL_DATA_OFFSET

#ifdef CONFIG_SYS_LOWBOOT
/* PQ2FADS flash HRCW = 0x0EB4B645 */
#define CONFIG_SYS_HRCW_MASTER (   ( HRCW_BPS11 | HRCW_CIP )			    |\
			    ( HRCW_L2CPC10 | HRCW_DPPC11 | HRCW_ISB100 )    |\
			    ( HRCW_BMS | HRCW_MMR11 | HRCW_LBPC01 | HRCW_APPC10 ) |\
			    ( HRCW_CS10PC01 | HRCW_MODCK_H0101 )	     \
			)
#else
/* PQ2FADS BCSR HRCW = 0x0CB23645 */
#define CONFIG_SYS_HRCW_MASTER (   ( HRCW_BPS11 | HRCW_CIP )			    |\
			    ( HRCW_L2CPC10 | HRCW_DPPC10 | HRCW_ISB010 )    |\
			    ( HRCW_BMS | HRCW_APPC10 )			    |\
			    ( HRCW_MODCK_H0101 )			     \
			)
#endif
/* no slaves */
#define CONFIG_SYS_HRCW_SLAVE1 0
#define CONFIG_SYS_HRCW_SLAVE2 0
#define CONFIG_SYS_HRCW_SLAVE3 0
#define CONFIG_SYS_HRCW_SLAVE4 0
#define CONFIG_SYS_HRCW_SLAVE5 0
#define CONFIG_SYS_HRCW_SLAVE6 0
#define CONFIG_SYS_HRCW_SLAVE7 0

#define CONFIG_SYS_MONITOR_BASE    CONFIG_SYS_TEXT_BASE

#if (CONFIG_SYS_MONITOR_BASE < CONFIG_SYS_FLASH_BASE)
#   define CONFIG_SYS_RAMBOOT
#endif

#define CONFIG_SYS_MONITOR_LEN		(256 << 10)	/* Reserve 256 kB for Monitor	*/
#define CONFIG_SYS_BOOTMAPSZ		(8 << 20)	/* Initial Memory map for Linux */

#ifdef CONFIG_BZIP2
#define CONFIG_SYS_MALLOC_LEN		(4096 << 10)	/* Reserve 4 MB for malloc()	*/
#else
#define CONFIG_SYS_MALLOC_LEN		(128 << 10)	/* Reserve 128 KB for malloc()	*/
#endif /* CONFIG_BZIP2 */

#ifndef CONFIG_SYS_RAMBOOT
#  define CONFIG_ENV_SIZE	0x10000
#  define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - CONFIG_ENV_SIZE)
#else
//#  define CONFIG_ENV_IS_IN_NVRAM	1
//#  define CONFIG_ENV_ADDR		(CONFIG_SYS_MONITOR_BASE - 0x1000)
//#  define CONFIG_ENV_SIZE		0x200
#define CONFIG_ENV_IS_NOWHERE
#define CONFIG_ENV_SIZE		0x2000
#define CONFIG_IPADDR 192.168.1.68
#define CONFIG_ETHADDR 00:11:22:33:44:55
#endif /* CONFIG_SYS_RAMBOOT */



#define CONFIG_SYS_CACHELINE_SIZE	32	/* For MPC8260 CPU */
#if defined(CONFIG_CMD_KGDB)
#  define CONFIG_SYS_CACHELINE_SHIFT	5	/* log base 2 of the above value */
#endif

#define CONFIG_SYS_HID0_INIT		0
#define CONFIG_SYS_HID0_FINAL		(HID0_ICE | HID0_IFEM | HID0_ABE )

#define CONFIG_SYS_HID2		0

#define CONFIG_SYS_SYPCR		0xFFFFFFC3
#define CONFIG_SYS_BCR			0x100C0000
#define CONFIG_SYS_SIUMCR		0x00640000
#define CONFIG_SYS_SCCR		SCCR_DFBRG01
#define CONFIG_SYS_BR0_PRELIM		(CONFIG_SYS_FLASH_BASE | 0x00001801)
//#define CONFIG_SYS_OR0_PRELIM		0xFe000c74
#define CONFIG_SYS_OR0_PRELIM		0xFE000EF4

//#define CONFIG_SYS_BR1_PRELIM		(CONFIG_SYS_FLASH_BASE2 | 0x00001001)
//#define CONFIG_SYS_OR1_PRELIM		0xFC000C54	/*32MB*/

#define	CONFIG_SYS_BR2_PRELIM		(CONFIG_SYS_SDRAM_BASE | 0x00000041)
#define CONFIG_SYS_OR2_PRELIM		0xf8002b00

/*We need to configure chip select to use CPLD PCI IC on MPC8272ADS*/
#if 0
#if CONFIG_ADSTYPE == CONFIG_SYS_8272ADS
#define CONFIG_SYS_BR3_PRELIM	(CONFIG_SYS_PCI_INT | 0x1801)	/* PCI interrupt controller */
#define CONFIG_SYS_OR3_PRELIM	0xFFFF8010
#elif CONFIG_ADSTYPE == CONFIG_SYS_PQ2FADS
#define CONFIG_SYS_BR8_PRELIM	(CONFIG_SYS_PCI_INT | 0x1801)	/* PCI interrupt controller */
#define CONFIG_SYS_OR8_PRELIM	0xFFFF8010
#endif
#endif

#define CONFIG_SYS_RMR			RMR_CSRE
#define CONFIG_SYS_TMCNTSC		(TMCNTSC_SEC|TMCNTSC_ALR|TMCNTSC_TCF|TMCNTSC_TCE)
#define CONFIG_SYS_PISCR		(PISCR_PS|PISCR_PTF|PISCR_PTE)
#define CONFIG_SYS_RCCR		0


#define CONFIG_SYS_OR_TIMING_SDRAM			0xF8002B00
#define CONFIG_SYS_PSDMR		0x832E3662
#define CONFIG_SYS_PSRT			0x13
#define CONFIG_SYS_MPTPR		0x2800


#define CONFIG_SYS_RESET_ADDRESS	(CONFIG_SYS_MONITOR_BASE + EXC_OFF_SYS_RESET)


/* PCI Memory map (if different from default map */
#define CONFIG_SYS_PCI_SLV_MEM_LOCAL	CONFIG_SYS_SDRAM_BASE		/* Local base */
#define CONFIG_SYS_PCI_SLV_MEM_BUS		0x00000000		/* PCI base */
#define CONFIG_SYS_PICMR0_MASK_ATTRIB	(PICMR_MASK_512MB | PICMR_ENABLE | \
				 PICMR_PREFETCH_EN)

/*
 * These are the windows that allow the CPU to access PCI address space.
 * All three PCI master windows, which allow the CPU to access PCI
 * prefetch, non prefetch, and IO space (see below), must all fit within
 * these windows.
 */

/*
 * Master window that allows the CPU to access PCI Memory (prefetch).
 * This window will be setup with the second set of Outbound ATU registers
 * in the bridge.
 */

#define CONFIG_SYS_PCI_MSTR_MEM_LOCAL	0x80000000          /* Local base */
#define CONFIG_SYS_PCI_MSTR_MEM_BUS	0x80000000          /* PCI base   */
#define	CONFIG_SYS_CPU_PCI_MEM_START	PCI_MSTR_MEM_LOCAL
#define CONFIG_SYS_PCI_MSTR_MEM_SIZE	0x20000000          /* 512MB */
#define CONFIG_SYS_POCMR0_MASK_ATTRIB	(POCMR_MASK_512MB | POCMR_ENABLE | POCMR_PREFETCH_EN)

/*
 * Master window that allows the CPU to access PCI Memory (non-prefetch).
 * This window will be setup with the second set of Outbound ATU registers
 * in the bridge.
 */

#define CONFIG_SYS_PCI_MSTR_MEMIO_LOCAL    0xA0000000          /* Local base */
#define CONFIG_SYS_PCI_MSTR_MEMIO_BUS      0xA0000000          /* PCI base   */
#define CONFIG_SYS_CPU_PCI_MEMIO_START     PCI_MSTR_MEMIO_LOCAL
#define CONFIG_SYS_PCI_MSTR_MEMIO_SIZE     0x20000000          /* 512MB */
#define CONFIG_SYS_POCMR1_MASK_ATTRIB      (POCMR_MASK_512MB | POCMR_ENABLE)

/*
 * Master window that allows the CPU to access PCI IO space.
 * This window will be setup with the first set of Outbound ATU registers
 * in the bridge.
 */

#define CONFIG_SYS_PCI_MSTR_IO_LOCAL       0xF6000000          /* Local base */
#define CONFIG_SYS_PCI_MSTR_IO_BUS         0x00000000          /* PCI base   */
#define CONFIG_SYS_CPU_PCI_IO_START        PCI_MSTR_IO_LOCAL
#define CONFIG_SYS_PCI_MSTR_IO_SIZE        0x02000000          /* 64MB */
#define CONFIG_SYS_POCMR2_MASK_ATTRIB      (POCMR_MASK_32MB | POCMR_ENABLE | POCMR_PCI_IO)


/* PCIBR0 - for PCI IO*/
#define CONFIG_SYS_PCI_MSTR0_LOCAL		CONFIG_SYS_PCI_MSTR_IO_LOCAL		/* Local base */
#define CONFIG_SYS_PCIMSK0_MASK		~(CONFIG_SYS_PCI_MSTR_IO_SIZE - 1U)	/* Size of window */
/* PCIBR1 - prefetch and non-prefetch regions joined together */
#define CONFIG_SYS_PCI_MSTR1_LOCAL		CONFIG_SYS_PCI_MSTR_MEM_LOCAL
#define CONFIG_SYS_PCIMSK1_MASK		~(CONFIG_SYS_PCI_MSTR_MEM_SIZE + CONFIG_SYS_PCI_MSTR_MEMIO_SIZE - 1U)



#define CONFIG_HAS_ETH0

#define CONFIG_HAS_ETH1

#define CONFIG_NETDEV eth0
#define CONFIG_LOADADDR 500000 /* default location for tftp and bootm */

#define CONFIG_EXTRA_ENV_SETTINGS \
	"netdev=" __stringify(CONFIG_NETDEV) "\0"			\
	"tftpflash=tftpboot $loadaddr $uboot; "				\
		"protect off " __stringify(CONFIG_SYS_TEXT_BASE)	\
			" +$filesize; "	\
		"erase " __stringify(CONFIG_SYS_TEXT_BASE) " +$filesize; " \
		"cp.b $loadaddr " __stringify(CONFIG_SYS_TEXT_BASE)	\
			" $filesize; "	\
		"protect on " __stringify(CONFIG_SYS_TEXT_BASE)		\
			" +$filesize; "	\
		"cmp.b $loadaddr " __stringify(CONFIG_SYS_TEXT_BASE)	\
			" $filesize\0"	\
	"fdtaddr=400000\0"						\
	"console=ttyCPM0\0"						\
	"setbootargs=setenv bootargs "					\
		"root=$rootdev rw console=$console,$baudrate $othbootargs\0" \
	"setipargs=setenv bootargs nfsroot=$serverip:$rootpath "	 \
		"ip=$ipaddr:$serverip:$gatewayip:$netmask:$hostname:$netdev:off " \
		"root=$rootdev rw console=$console,$baudrate $othbootargs\0"

#define CONFIG_NFSBOOTCOMMAND						\
	"setenv rootdev /dev/nfs;"					\
	"run setipargs;"						\
	"tftp $loadaddr $bootfile;"					\
	"tftp $fdtaddr $fdtfile;"					\
	"bootm $loadaddr - $fdtaddr"

#define CONFIG_RAMBOOTCOMMAND						\
	"setenv rootdev /dev/ram;"					\
	"run setbootargs;"						\
	"tftp $ramdiskaddr $ramdiskfile;"				\
	"tftp $loadaddr $bootfile;"					\
	"tftp $fdtaddr $fdtfile;"					\
	"bootm $loadaddr $ramdiskaddr $fdtaddr"

#endif /* __CONFIG_H */
