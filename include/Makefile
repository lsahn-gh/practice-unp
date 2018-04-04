include ../Make.defines

LIB_OBJS = xinet4.o prereq.o xerror.o xio.o

all:	${LIB_OBJS}
		ar rv ${LIBPUNP_PATH} $?
		${RANLIB} ${LIBPUNP_PATH}

clean:
		rm -f ${PROGS} ${CLEANFILES}
