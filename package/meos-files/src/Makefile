%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

all: meos blink

meos: meos.o
	$(CC) $(LDFLAGS) -lm -o $@ $<

blink: blink.o
	$(CC) $(LDFLAGS) -L. -lm -liwinfo -lnl-tiny -ljson-c -o $@ $<

clean:
	rm -f *.o meos blink

