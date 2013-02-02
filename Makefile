INSTALL = install

CLIENTBIN = vaultaire
SRCBIN = client/bin/$(CLIENTBIN)
DESKTOPFILE = vaultaire.desktop
SRCDESKTOPFILE = client/$(DESKTOPFILE)
ICONFILE = vaultaire.svg
SRCICON = client/icons/hicolor/scalable/apps/$(ICONFILE)

prefix = $(DESTDIR)/usr
BINDIR = $(prefix)/bin
DATADIR = $(prefix)/share
DESKTOPDIR = $(DATADIR)/applications
ICONPATH = $(DATADIR)/icons/hicolor
ICONDIR = $(ICONPATH)/scalable/apps
MANDIR = $(DATADIR)/man/man1

all: $(CLIENTBIN)

# Build client (GUI) application
$(CLIENTBIN):
	cd client && qmake && $(MAKE)

install: $(BINS)
	$(INSTALL) -d -m 755 $(BINDIR)
	$(INSTALL) -m 755 $(SRCBIN) $(BINDIR)
	$(INSTALL) -d -m 755 $(DESKTOPDIR)
	$(INSTALL) -m 644 $(SRCDESKTOPFILE) $(DESKTOPDIR)
	$(INSTALL) -d -m 755 $(ICONDIR)
	$(INSTALL) -m 644 $(SRCICON) $(ICONDIR)

uninstall:
	rm $(BINDIR)/$(CLIENTBIN)
	rm $(DESKTOPDIR)/$(DESKTOPFILE)
	rm $(ICONDIR)/$(ICONFILE)

