# Created by: Gustau Perez <gustau.perez@gmail.com>
# $FreeBSD$

PORTNAME=	california
PORTVERSION=	0.4.0
PORTREVISION=	1
CATEGORIES=	deskutils gnome
MASTER_SITES=	GNOME
DIST_SUBDIR=	gnome3

MAINTAINER=	gnome@FreeBSD.org
COMMENT=	Calendar client for GNOME 3

DEPRECATED=	Orphaned upstream, replaced by gnome-calendar
EXPIRATION_DATE=2017-07-02

BUILD_DEPENDS=	itstool:textproc/itstool \
		xdg-open:devel/xdg-utils
LIB_DEPENDS=	libwebkitgtk-3.0.so:www/webkit-gtk3 \
		libicui18n.so:devel/icu \
		libsoup-2.4.so:devel/libsoup \
		libgee-0.8.so:devel/libgee \
		libgdata.so:devel/libgdata \
		libical.so:devel/libical \
		libsecret-1.so:security/libsecret \
		libjson-glib-1.0.so:devel/json-glib \
		libgoa-1.0.so:net/gnome-online-accounts
RUN_DEPENDS=	xdg-open:devel/xdg-utils

USES=		desktop-file-utils gettext gmake libtool pathfix \
		pkgconfig tar:xz
USE_GNOME=	cairo evolutiondataserver3 glib20 gnomedocutils gnomeprefix \
		gtk30 intlhack introspection
USE_LDCONFIG=	yes
GNU_CONFIGURE=	yes
INSTALLS_ICONS=	yes
CONFIGURE_ARGS=	--disable-unity --disable-fatal
CPPFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
INSTALL_TARGET=	install-strip
GLIB_SCHEMAS=	org.yorba.california.gschema.xml

post-patch:
		@${REINPLACE_CMD} -e 's|californiadocdir = $${prefix}|californiadocdir = $${prefix}/share|g' \
			${WRKSRC}/Makefile.in

.include <bsd.port.mk>
