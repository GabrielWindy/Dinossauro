CC = clang
CFLAGS = -O2 -lraylib -lm -Wall
SRCS = ./src/main.c
OUTPUT = ./dino

build:
	make ./dino
	./dino
./dino: $(SRCS)
	$(CC) $(SRCS) $(CFLAGS) -o $(OUTPUT)

clean:
	rm ./dino

.PHONY: clean build
