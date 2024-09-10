CC = gcc
BINS = typing clean

all:$(BINS)

typing:
	if [ ! -d build ]; then mkdir build; fi
	$(CC) src/typing.c -o build/typing.exe 

clean:
	rm build/*.o
