TARGET = bin/final
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/*.c, obj/%.o, $(SRC))

default: $(TARGET)

clean:
	rm -f obj/*.o
	rm -f bin/*

$(TARGET): $(OBJ)
	gcc -o $@ $? -I./inc
