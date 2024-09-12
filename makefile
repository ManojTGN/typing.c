CC = gcc
BINS = typing clean

all:$(BINS)

build:
	if [ ! -d build ]; then mkdir build; fi

screen:
	$(CC) -c src/screen.c -o build/screen.o

typing: build screen
	$(CC) build/screen.o src/typing.c -o build/typing.exe

clean:
	rm build/*.o
