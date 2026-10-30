CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -O2
SRC    := src/main.c

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
	$(CC) $(CFLAGS) -o $@ $<

run: $(BIN)
	./$(BIN)

clean:
	-$(RM) $(BIN) $(RMERR)