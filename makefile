CC = gcc
BINS = typing clean

all:$(BINS)

build:
	if [ ! -d build ]; then mkdir build; fi

text:
	$(CC) -c src/text.c -o build/text.o

screen:
	$(CC) -c src/screen.c -o build/screen.o

typing: build text screen 
	$(CC) src/typing.c build/text.o build/screen.o -o build/typing.exe

clean:
	rm build/*.o
