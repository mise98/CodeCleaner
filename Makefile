CC=gcc  #compiler
TARGET=main #target file name
 
all:	main.o
	$(CC) main.c -o $(TARGET)
 
clean:
	rm *.o $(TARGET)