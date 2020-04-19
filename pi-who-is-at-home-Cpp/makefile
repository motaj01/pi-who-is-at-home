FLAGS  = -Wall -g -pthread
CC     = g++
PROG   = piwhoisathome
OBJS   = main.o authentication.o filecontrol.o util.o global.o networkDevices.o commands.o sendEmail.o

all: ${PROG}

clean:
	rm -rf core* ${OBJS} ${PROG}

${PROG}: ${OBJS}
	${CC} ${FLAGS} ${OBJS} -o $@

%.o : %.c
	${CC} ${FLAGS} -c $< -o $@

#------------------------------------------------------------------------------------
sendEmail.o: sendEmail.cpp sendEmail.h
networkDevices.o: networkDevices.cpp networkDevices.h global.h sendEmail.h
util.o: util.cpp util.h global.h
filecontrol.o: filecontrol.cpp filecontrol.h global.h
global.o: global.cpp global.h
authentication.o: authentication.cpp authentication.h global.h
commands.o: commands.cpp commands.h global.h sendEmail.h
main.o: main.cpp authentication.h filecontrol.h global.h commands.h networkDevices.h

