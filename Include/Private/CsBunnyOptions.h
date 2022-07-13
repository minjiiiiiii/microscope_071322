
#ifndef __CsBunnyOptions_h__
#define __CsBunnyOptions_h__


#define BUNNY_TRIGGER_RES			32

// "Base board" options
#define	BUNNY_BASEOPTION_ECO10		0x1


// "Addon" options
#define BUNNY_OPT_DUAL_CHANNEL		0x1
#define	BUNNY_OPT_HIGH_BW			0x2
#define	BUNNY_OPT_FULL_BW			0x4
#define	BUNNY_OPT_OSC500M			0x8
#define	BUNNY_OPT_OSC1G				0x10
#define	BUNNY_OPT_OSC1500M			0x20
#define	BUNNY_OPT_OSC2G				0x40
#define	BUNNY_OPT_xx20_ADC			0x80
#define BUNNY_OPT_TRIGOUT			0x100
#define BUNNY_OPT_CLKOUT			0x200
#define BUNNY_OPT_SR_1G             0x400
#define	BUNNY_OPT_4G_ADC			0x800




// Base board options that require Special Firmware
#define	BUNNY_BBHW_OPT_FWREQUIRED_MASK		0

// Addon board options that require Special Firmware
#define	BUNNY_AOHW_OPT_FWREQUIRED_MASK		0



#endif
