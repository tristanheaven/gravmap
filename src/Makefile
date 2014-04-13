CFLAGS ?= -O2
CFLAGS += -std=gnu99 -Wall
SRC = $(wildcard *.c)
HEADERS = $(wildcard *.h)
LIBS = -lm -lpng

gravmap: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o gravmap $(LIBS)

clean:
	rm -f gravmap
