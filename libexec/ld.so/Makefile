#	$OpenBSD: Makefile,v 1.47 2014/02/16 01:16:38 martynas Exp $

SUBDIR=ldconfig ldd
MAN=	ld.so.1

.include <bsd.own.mk>

.if defined(NOPIC)
NOPROG=
.else
PROG=	ld.so

VPATH=${.CURDIR}/../../lib/libc/string

SRCS=	ldasm.S boot.c loader.c resolve.c dlfcn.c dl_printf.c rtld_machine.c
SRCS+=	path.c util.c sod.c strsep.c strtol.c dir.c library_subr.c dl_prebind.c
SRCS+=	dl_realpath.c dl_uname.c dl_dirname.c strlcat.c strlen.c trace.c
.if (${MACHINE_ARCH} == "i386")
SRCS+=	library_mquery.c
.else
SRCS+=	library.c
.endif
SRCS+= tls.c


.include "${.CURDIR}/${MACHINE_CPU}/Makefile.inc"
.PATH:	${.CURDIR}/${MACHINE_CPU}

DEBUG?=	-g
CFLAGS += -Wall -fno-builtin
CFLAGS += -I${.CURDIR} -I${.CURDIR}/${MACHINE_CPU} \
	-Dstrsep=_dl_strsep -Dstrlcat=_dl_strlcat -Dstrlen=_dl_strlen
CDIAGFLAGS=
INSTALL_STRIP=

ELF_LDFLAGS+=--shared -Bsymbolic --no-undefined

candidate=	$(PROG).test
.if ${HOSTCC} == ${CC}
test_prog=	test-$(PROG)
test_cmd= 	'ulimit -c 0; [ "`${.OBJDIR}/$(test_prog) ok`" = ok ]'

$(test_prog):
	printf '#include <stdio.h>\nint main(int argc, char **argv){ printf("%%s\\n", argv[1]); }\n' | \
	$(CC) -x c - -Wl,-dynamic-linker,${.OBJDIR}/$(candidate) -o $@

.endif
$(PROG): $(test_prog)
	$(LD) -x -e _dl_start $(ELF_LDFLAGS) -o $(candidate) $(OBJS) $(LDADD)
	eval $(test_cmd)
	cp $(candidate) $@
.endif

.include <bsd.prog.mk>

boot.o: boot.c
	${COMPILE.c} -fno-stack-protector ${.IMPSRC}
