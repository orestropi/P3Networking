
all:server.o client.o
	g++ server.cpp -o server
	g++ client.cpp -o client

clean:
	$(RM) server server.o
