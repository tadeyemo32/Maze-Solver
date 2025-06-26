# ---------------- CONFIG ----------------
CC := gcc
CFLAGS := -Wall -Wextra -std=c17 -Iinclude

SRCDIR := src
INCDIR := include
BINDIR := bin
TARGET := $(BINDIR)/main

SRC := $(wildcard $(SRCDIR)/*.c)
OBJ := $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.o)

# ---------------- RULES ----------------
all: $(TARGET)

$(TARGET): $(OBJ) | $(BINDIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BINDIR)/%.o: $(SRCDIR)/%.c | $(BINDIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(BINDIR)/*.o
	rm -f $(TARGET)

$(BINDIR):
	mkdir -p $(BINDIR)

.PHONY: all clean run
