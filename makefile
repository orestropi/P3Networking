
all:server.o
	g++ server.cpp -o server

clean:
	$(RM) server server.o
