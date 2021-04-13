CC = gcc
CFLAGS = -g -Wall -pthread

TARGET = pthreads

all: clean $(TARGET)

$(TARGET): main.c
	$(CC) $(CFLAGS) -O3 -o $(TARGET) main.c
	$(CC) $(CFLAGS) -o $(TARGET)2 main2.c

clean:
	rm -f $(TARGET) *.o