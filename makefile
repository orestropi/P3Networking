
all:wireview.o
	g++ class.cpp -o class

clean:
	$(RM) class class.o
