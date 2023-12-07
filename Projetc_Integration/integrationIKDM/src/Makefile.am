## Process this file with automake to produce Makefile.in

INCLUDES = \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	@PACKAGE_CFLAGS@

bin_PROGRAMS = integrationikdm

integrationikdm_SOURCES = \
	main.c \
	support.c support.h \
	interface.c interface.h \
	callbacks.c callbacks.h \
	auth.c auth.h \
	rdv.c rdv.h \
	ets.c ets.h \
	user.c user.h

integrationikdm_LDADD = @PACKAGE_LIBS@ $(INTLLIBS)

