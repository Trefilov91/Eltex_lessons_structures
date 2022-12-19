

CC = gcc
BUILD_DIR = build

EXE += phonebook

all: $(BUILD_DIR) $(EXE)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

phonebook: phonebook.c
	$(CC) $< -o $(BUILD_DIR)/$@

clean:
	rm -r $(BUILD_DIR)
