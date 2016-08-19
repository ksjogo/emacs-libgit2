EMACSHEADERS = /home/ksjogo/dev/emacs/src
CC      = gcc
LD      = gcc
CFLAGS  = -g -ggdb3 -Wall -fPIC
LDFLAGS = -L libgit2/build -shared
LDLIBS = -lgit2
CMAKEFLAGS =  -DBUILD_SHARED_LIBS=OFF -DTHREADSAFE=ON -DBUILD_CLAR=OFF -DCMAKE_C_FLAGS=-fPIC -DCMAKE_BUILD_TYPE="RelWithDebInfo"
LIBGITHEADERS = libgit2/include
LIBGITFILES = libgit2/build/libgit2.a

ifeq ($(OS),Windows_NT)
TARGET = libgit2-core.dll
LDFLAGS += -Wl,--image-base -Wl,0x10000000
CMAKEFLAGS += -DCMAKE_LEGACY_CYGWIN_WIN32=0
else
TARGET = libgit2-core.so
LDFLAGS += -pthread
LDLIBS += -lz
endif

.ONESHELL:
all: $(TARGET)

# make shared library out of the object file
%.so %.dll: %.o $(LIBGITFILES)
	$(LD) $(LDFLAGS) -o $@ $< $(LDLIBS)

# compile source file to object file
%.o: %.c
	$(CC) $(CFLAGS) -I$(EMACSHEADERS) -I$(LIBGITHEADERS) -c $<

$(LIBGITFILES): libgit2

.PHONY: libgit2
libgit2:
	mkdir -p libgit2/build
	cd libgit2/build
	[ ! -d CMakeFiles ] && cmake $(CMAKEFLAGS) ..
	cmake --build .

clean:
	rm -rf *.so *.dll libgit2/build
