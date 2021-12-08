
all:clientServer.o
	g++ clientServer.cpp -o clientServer

clean:
	$(RM) clientServer clientServer.o
