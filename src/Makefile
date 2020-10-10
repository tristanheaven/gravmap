CFLAGS ?= -O2 -march=native
CFLAGS += -Wall
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

EMCC = emcc
EMCFLAGS = -O1 --pre-js pre.js \
	-s ALLOW_MEMORY_GROWTH=1 \
	-s DYNAMIC_EXECUTION=0 \
	-s ENVIRONMENT=web \
	-s EXPORTED_FUNCTIONS=[_pngtile,_tilesize,_tilefree] \
	-s EXPORT_NAME=emscripten \
	-s EXTRA_EXPORTED_RUNTIME_METHODS=[cwrap] \
	-s MODULARIZE=1 \
	-s TEXTDECODER=0 \
	-s USE_LIBPNG=1

all: gravmap gravmap.js

gravmap: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o gravmap $(LIBS)

gravmap.js: $(SRC) $(HEADERS) pre.js
	$(EMCC) $(EMCFLAGS) $(SRC) -o gravmap.js

clean:
	rm -f gravmap
	rm -f gravmap.js
	rm -f gravmap.wasm
