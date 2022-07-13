
include $(top_srcdir)/common_middle.mk

AM_CPPFLAGS += \
	-I$(srcdir)/../C_Common

lib_LTLIBRARIES = libCsAppSupport.la

libCsAppSupport_la_SOURCES = \
	../C_Common/CsSdkMisc.c \
	ConfigSystem.c \
	CsAppSupport.c \
	SaveFile.c \
	../../Include/Public/CsPrototypes.h \
	../C_Common/CsTchar.h \
	../C_Common/CsSdkMisc.h

libCsAppSupport_la_LIBADD = \
	../../Middle/CsSsm/libCsSsm.la

