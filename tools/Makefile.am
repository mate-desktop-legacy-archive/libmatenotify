bin_PROGRAMS = mate-notify-send

common_ldflags = \
	$(top_builddir)/libmatenotify/libmatenotify.la \
	$(PACKAGE_LIBS)

mate_notify_send_SOURCES = notify-send.c
mate_notify_send_LDADD   = $(common_ldflags)

INCLUDES = \
	-I$(top_srcdir) \
	-I$(top_srcdir)/libmatenotify \
	$(PACKAGE_CFLAGS)


-include $(top_srcdir)/git.mk
