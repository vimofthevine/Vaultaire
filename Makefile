INSTALL = install

CLIENTBIN = client/bin/vaultaire
DESKTOPFILE = client/vaultaire.desktop
ICONFILE = client/icons/hicolor/scalable/apps/vaultaire.svg

prefix = $(DESKDIR)/usr
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
	$(INSTALL) -m 755 $(CLIENTBIN) $(BINDIR)
	$(INSTALL) -d -m 755 $(DESKTOPDIR)
	$(INSTALL) -m 644 $(DESKTOPFILE) $(DESKTOPDIR)
	$(INSTALL) -d -m 755 $(ICONDIR)
	$(INSTALL) -m 644 $(ICONFILE) $(ICONDIR)

uninstall:
	rm $(BINDIR)/$(CLIENTBIN)
	rm $(DESKTOPDIR)/$(DESKTOPFILE)
	rm $(ICONDIR)/$(ICONFILE)

