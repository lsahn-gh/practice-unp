include ../Make.defines

LIB_OBJS = inet4.o

all:	${LIB_OBJS}
		ar rv ${LIBPUNP_NAME} $?
		${RANLIB} ${LIBPUNP_NAME}

clean:
		rm -f ${PROGS} ${CLEANFILES}
