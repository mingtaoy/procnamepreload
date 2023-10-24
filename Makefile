CC ?= cc
DSO = procnamepreload.so
CFLAGS ?= -O2

all: $(DSO)

$(DSO): procnamepreload.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $< $(LDFLAGS)

.PHONY: all clean

clean:
	rm -f procnamepreload.so
