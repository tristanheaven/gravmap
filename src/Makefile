CFLAGS ?= -O2 -march=native
CFLAGS += -std=gnu99 -Wall
SRC = $(wildcard *.c)
HEADERS = $(wildcard *.h)
LIBS = -lm
STATIC = 0

ifeq ($(STATIC), 1)
	CFLAGS += -static $(shell pkg-config --static --cflags libpng)
	LIBS += $(shell pkg-config --static --libs libpng)
else
	CFLAGS += $(shell pkg-config --cflags libpng)
	LIBS += $(shell pkg-config --libs libpng)
endif

gravmap: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o gravmap $(LIBS)

clean:
	rm -f gravmap
