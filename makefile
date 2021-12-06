
all:wireview.o
	gcc class.c -o class

clean:
	$(RM) class class.o
