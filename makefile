
all:clientServer.o
	g++ clientServer.cpp -o clientServer

alltwo:client.o server.o
	g++ client.cpp -o client	
	g++ server.cpp -o server	
	
clean:
	$(RM) clientServer clientServer.o client client.o server server.o
