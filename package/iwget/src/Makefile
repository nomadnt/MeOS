%.o: %.c
	$(CC) $(CFLAGS) -std=gnu99 -fstrict-aliasing -Iinclude -DUSE_NL80211 $(FPIC) -c -o $@ $<

all: iwget

iwget: format.o radio.o main.o
	$(CC) $(LDFLAGS) -L. -liwinfo -lnl-tiny -o iwget format.o radio.o main.o

clean:
	rm -f *.o iwget

