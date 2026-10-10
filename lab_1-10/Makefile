CC = cc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic
LDLIBS = -lm

LABS = $(basename $(wildcard lab*.c))

all: $(LABS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LDLIBS)

clean:
	rm -f $(LABS)

.PHONY: all clean
