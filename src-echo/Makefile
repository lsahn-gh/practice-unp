include ../Make.defines

PROGS =	echocliv1 echoservv1

all:	${PROGS}

echocliv1:	echocliv1.o
		${CC} ${CFLAGS} -o $@ echocliv1.o ${LIBS}

echoservv1:	echoservv1.o
		${CC} ${CFLAGS} -o $@ echoservv1.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}

