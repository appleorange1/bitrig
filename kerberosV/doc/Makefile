# $OpenBSD: Makefile,v 1.13 2013/07/09 14:33:43 ajacoutot Exp $

KINFOSRC =	${.CURDIR}/../src/doc
KINFODIR =	${DESTDIR}${SHAREDIR}/info

MAKEINFO =	/usr/bin/makeinfo
INSTALL-INFO =	/usr/bin/install-info

INFO =	heimdal.info

SRCS =	heimdal.texi intro.texi whatis.texi install.texi setup.texi apps.texi \
	misc.texi kerberos4.texi win2k.texi programming.texi migration.texi \
	ack.texi copyright.texi vars.texi

all: ${INFO}

heimdal.info: ${SRCS}
.for t in ${SRCS}
	sed -f ${.CURDIR}/../varsub ${KINFOSRC}/${t} > ${.OBJDIR}/${t}.tmp && \
		mv ${.OBJDIR}/${t}.tmp ${.OBJDIR}/${t}
.endfor
	${MAKEINFO} --no-split -I${KINFOSRC} -o ${.TARGET} ${.OBJDIR}/heimdal.texi

install: ${INFO}
	${INSTALL} ${INSTALL_COPY} -m ${DOCMODE} -o ${DOCOWN} -g ${DOCGRP} ${.OBJDIR}/${INFO} ${KINFODIR}
	$(INSTALL-INFO) ${.OBJDIR}/${INFO} ${KINFODIR}/dir

clean:
	rm -f ${INFO} ${SRCS}

cleandir: clean

.PATH:	${KINFOSRC}

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
