
all:client.o server.o
	g++ server.cpp -o server
	g++ client.cpp -o client

clean:
	$(RM) server server.o
	$(RM) client client.o
