CC1 = clang
CC2 = gcc
CFLAGS = -g -Wall -Werror
EXECUTABLE1 = wlang
EXECUTABLE2 = wcc
CODE = whitespace.c
all:$(EXECUTABLE1)

$(EXECUTABLE1): $(CODE)
	$(CC1) $(CFLAGS) -o $(EXECUTABLE1) $(CODE)

$(EXECUTABLE2): $(CODE)
	$(CC2) $(CFLAGS) -o $(EXECUTABLE1) $(CODE)

clean:
	rm $(EXECUTABLE)
