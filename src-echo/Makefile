include ../Make.defines

PROGS =	echocliv1 poll-echocliv1 \
		echoservv1 poll-echoservv1 \
		tcp-fork-echocliv1 tcp-fork-echoserv1

all:	${PROGS}

echocliv1:	echocliv1.o
		${CC} ${CFLAGS} -o $@ echocliv1.o ${LIBS}

echoservv1:	echoservv1.o
		${CC} ${CFLAGS} -o $@ echoservv1.o ${LIBS}

poll-echocliv1: poll-echocliv1.o
		${CC} ${CFLAGS} -o $@ poll-echocliv1.o ${LIBS}

poll-echoservv1: poll-echoservv1.o
		${CC} ${CFLAGS} -o $@ poll-echoservv1.o ${LIBS}

tcp-fork-echocliv1: tcp-fork-echocliv1.o
		${CC} ${CFLAGS} -o $@ tcp-fork-echocliv1.o ${LIBS}

tcp-fork-echoserv1: tcp-fork-echoserv1.o
		${CC} ${CFLAGS} -o $@ tcp-fork-echoserv1.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}

