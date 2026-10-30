CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -O2
SRC     := src/main.c src/tokenizer.c src/parser.c src/evaluator.c
INCLUDE := -Iinclude

ifeq ($(OS),Windows_NT)
    BIN   := calculator.exe
    RM    := del /Q
    RMERR := 2>NUL
else
    BIN   := calculator
    RM    := rm -f
    RMERR :=
endif

.PHONY: all clean run

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $(SRC)

run: $(BIN)
	-./$(BIN)

clean:
	-$(RM) $(BIN) $(RMERR)