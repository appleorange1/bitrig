# $OpenBSD: Makefile,v 1.2 2014/03/30 19:43:19 schwarze Exp $

REGRESS_TARGETS=TH Dd

.include <bsd.regress.mk>


# --- additions to public targets ---

all ascii: ascii-diff-opt

ascii-clean: ascii-clean-opt

groff: TH.out_ascii_opt Dd.out_ascii_opt

groff-clean: groff-clean-opt


# --- local rules ---

ascii-diff-opt: TH.mandoc_ascii_opt Dd.mandoc_ascii_opt
	${DIFF} ${.CURDIR}/TH.out_ascii_opt TH.mandoc_ascii_opt
	${DIFF} ${.CURDIR}/Dd.out_ascii_opt Dd.mandoc_ascii_opt

TH.mandoc_ascii_opt: TH.in
	${MANDOC} -Tascii -man ${.ALLSRC} > ${.TARGET}

Dd.mandoc_ascii_opt: Dd.in
	${MANDOC} -Tascii -mdoc ${.ALLSRC} > ${.TARGET}

ascii-clean-opt:
	rm -f TH.mandoc_ascii_opt Dd.mandoc_ascii_opt

TH.out_ascii_opt: TH.in
	/usr/local/bin/nroff -c -man -Tascii ${.ALLSRC} > ${.TARGET}

Dd.out_ascii_opt: Dd.in
	/usr/local/bin/nroff -c -mdoc -Tascii ${.ALLSRC} > ${.TARGET}

groff-clean-opt:
	rm -f TH.out_ascii_opt Dd.out_ascii_opt
