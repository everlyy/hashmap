NAME := hashmap

CC := gcc
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -ggdb -pedantic -std=c2x

BUILD_DIR := .build
SOURCE_DIR := src

OBJECTS := hashmap.o example.o

SOURCES := $(OBJECTS:%.o=%.c)
OBJECTS := $(OBJECTS:%=$(BUILD_DIR)/%)

$(NAME): $(OBJECTS)
	gcc $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	gcc $(CFLAGS) -c -o $@ $^

clean:
	rm -f $(BUILD_DIR)