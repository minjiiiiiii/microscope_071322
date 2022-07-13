#ifndef __CS_DEVICE_IDS__
#define __CS_DEVICE_IDS__

#define	GAGE_VENDOR_ID			0x1197		//	Gage's unique vendor ID number.

#define	GAGE_PCI_BOOT_VENDOR_ID		0x10e8		//	AMCC's unique vendor ID number.

/***********************************************\
*												*
*	The DEVICE ID "_DID_" options can be ORed	*
*	together to identify special features.		*
*												*
\***********************************************/

// PCI device IDs
#define	CS_DEVID_CP500		0x0100u		//	Device ID bits used for CP500 Baseboard.
#define	CS_DEVID_8500		0x0101u		//	Device ID bits used for CS8500.
#define	CS_DEVID_12100		0x0102u		//	Device ID bits used for add-on 12100   board on the CP500 Baseboard.
#define	CS_DEVID_8250		0x0103u		//	Device ID bits used for add-on 8250    board on the CP500 Baseboard.
#define	CS_DEVID_8500_RTAM	0x0104u		//	Device ID bits used for CS8500 with RTAM add-on board.
#define	CS_DEVID_12130		0x0105u		//	Device ID bits used for add-on 12130   board on the CP500 Baseboard.
#define	CS_DEVID_1602		0x0106u		//	Device ID bits used for add-on 1602    board on the CP500 Baseboard.
#define	CS_DEVID_DIM_3200	0x0107u		//	Device ID bits used for add-on DIM3200 board on the CP500 Baseboard.
#define	CS_DEVID_DOM_3200	0x0108u		//	Device ID bits used for add-on DOM3200 board on the CP500 Baseboard.
#define	CS_DEVID_1250		0x0109u		//	Device ID bits used for add-on 1250    board on the CP500 Baseboard.
#define	CS_DEVID_1210		0x010au		//	Device ID bits used for add-on 1210    board on the CP500 Baseboard.
#define	CS_DEVID_14100		0x010bu		//	Device ID bits used for add-on 14100   board on the CP500 Baseboard.
#define	CS_DEVID_82G		0x010cu		//	Device ID bits used for add-on 82G     board on the CP500 Baseboard.
#define	CS_DEVID_85G		0x010du		//	Device ID bits used for add-on 85G(Chopper) board on the CP500 Baseboard.
#define	CS_DEVID_1450		0x010eu		//	Device ID bits used for add-on 14100   board on the CP500 Baseboard.
#define	CS_DEVID_1610		0x010fu		//	Device ID bits used for add-on 1610    board on the CP500 Baseboard.
#define	CS_DEVID_1220		0x0110u		//	Device ID bits used for add-on 1220    board on the CP500 Baseboard.

#define	CS_DEVID_CP500_MAX		0x0110u		//	Maximum Device ID bits used for CP500 class devices.

// Compact PCI device IDs
#define CS_CPCI_DEVID			0x80u
#define	CS_DEVID_1610C		(CS_DEVID_1610 | CS_CPCI_DEVID)
#define	CS_DEVID_DIM_3200C	(CS_DEVID_DIM_3200 | CS_CPCI_DEVID)
#define	CS_DEVID_14100C		(CS_DEVID_14100 | CS_CPCI_DEVID)
#define	CS_DEVID_82GC		(CS_DEVID_82G | CS_CPCI_DEVID)
#define	CS_DEVID_85GC		(CS_DEVID_85G | CS_CPCI_DEVID)

#define	CS_DEVID_CP500_DEVS	0x01ffu		//	Device ID limit for CP500 based hardware.



#define	CS_DEVID_PLX_BASED	0x0200u		//	Device ID bits used for PLX Baseboard.
#define	CS_DEVID_x14200		0x0201u		//	Device ID bits used for add-on 14200 board on the PLX Baseboard.
#define	CS_DEVID_x14105		0x0202u		//	Device ID bits used for add-on 14105 board on the PLX Baseboard.
#define	CS_DEVID_x12400		0x0203u		//	Device ID bits used for add-on 12400 board on the PLX Baseboard.
#define	CS_DEVID_x14200x	0x0204u		//	Device ID bits used for Cs14200 from add-on 12400 board on the PLX Baseboard.
#define	CS_DEVID_SNA142		0x0205u		//	Device ID bits used for SNA-142 (Cs14200 memory less and with eXpert AVG.


#define CS_FAT_DEVID		0x10		//  Combine base board with big FPGA

#define	CS_DEVID_x12400_FAT	(CS_DEVID_x12400 | CS_FAT_DEVID)
#define	CS_DEVID_ST12AVG	(0x205 | CS_FAT_DEVID)	//	Sensortran ST12AVG card



#define	CS_DEVID_SPIDER		0x0401u		//	Generic Device ID used for Spider boards
#define	CS_DEVID_SPIDER_v12	0x0402u		//	Generic Device ID used for Spider boards v12
#define	CS_DEVID_SPIDER_LP	0x0403u		//	Generic Device ID used for Spider low power boards
#define	CS_DEVID_ZAP        0x0404u		//	Generic Device ID used for Spider based ZAP boards

#define CS_DEVID_STAVG_SPIDER	0x20
#define CS_DEVID_ST81AVG	(CS_DEVID_SPIDER_v12 | CS_DEVID_STAVG_SPIDER)
#define CS_DEVID_STLP81		(CS_DEVID_SPIDER_LP | CS_DEVID_STAVG_SPIDER)

#define CS_DEVID_SPLENDA	0x480u		//  Device ID used for Splenda boards

#define	CS_DEVID_RABBIT		0x0501u		//	Device ID used for Rabit boards

#define	CS_DEVID_HUSS			    0x0601u		//	Device ID used for Hustler boards
#define	CS_DEVID_PLAY			    0x0602u		//	Device ID used for Playboy boards
#define	CS_DEVID_PITCHER_MEM	    0x0603u		//	Device ID used for Pichter with Memeory boards
#define	CS_DEVID_PITCHER		    0x0604u		//	Device ID used for Pichter w/o Memeory boards

#define	CS_DEVID_FASTBALL	        0x0605u		//	Device ID used for Fastball with Memeory boards
#define	CS_DEVID_FASTBALL_NOMEM	    0x0606u		//	Device ID used for Fastball w/o Memeory boards
#define	CS_DEVID_FASTBALL_4G	    0x0607u		//	Device ID used for Fastball 4 GS/s with Memeory boards
#define	CS_DEVID_FASTBALL_4G_NOMEM  0x0608u		//	Device ID used for Fastball 4 GS/s w/o Memeory boards
#define	CS_DEVID_FASTBALL_3G	    0x0609u		//	Device ID used for Fastball 3 GS/s with Memeory boards
#define	CS_DEVID_FASTBALL_3G_NOMEM  0x060au		//	Device ID used for Fastball 4 GS/s w/o Memeory boards

#define	CS_DEVID_JOHNDEERE	0x0701u		//	Device ID used for JohnDeer boards
#define	CS_DEVID_BRAINIAC	0x0702u		//	Device ID used for Braniac boards

#define CS_DEVID_CS121G11U	0x0801u		//	Device ID used for USB 112 device
#define CS_DEVID_CS148001U	0x0802u		//	Device ID used for USB 114 device
#define CS_DEVID_CS144002U	0x0803u		//	Device ID used for USB 214 device
#define CS_DEVID_CS0864G1U	0x0804u		//	Device ID used for USB 108 device

#define	CS_DEVID_SPIDER_PCIE	0x0450u		//	Generic Device ID used for Spider PciE
#define	CS_DEVID_ZAP_PCIE		0x0451u		//	Generic Device ID used for Zap PciE
#define	CS_DEVID_SPLENDA_PCIE	0x0490u		//	Generic Device ID used for Splenda PciE
#define	CS_DEVID_OSCAR_PCIE		0x0491u		//	Generic Device ID used for Oscar PciE
#define	CS_DEVID_COBRA_PCIE		0x0550u		//	Generic Device ID used for Cobra PciE
#define	CS_DEVID_COBRA_MAX_PCIE	0x0650u		//	Generic Device ID used for Cobra Max PciE

#define	CS_DEVID_DECADE12		0x0A00u		//	Generic Device ID used for Decade 12
#define	CS_DEVID_HEXAGON		0x0B00u		//	Generic Device ID used for Hexagon PCIe	(A5 FPGA)
#define	CS_DEVID_HEXAGON_PXI	0x0B01u		//	Generic Device ID used for Hexagon PXI (A5 FPGA)
#define	CS_DEVID_HEXAGON_A3		0x0B02u		//	Generic Device ID used for Hexagon PCIe (A3 FPGA)
#define	CS_DEVID_HEXAGON_A3_PXI	0x0B03u		//	Generic Device ID used for Hexagon PXI (A3 FPGA)

#endif
