CFLAGS     = -std=c17 
EFLAG      = -E 
CC         = gcc
LD         = gcc
RM         = rm -rf
 


%.o: %.c  
	$(CC) $(CFLAGS) -o $@ $<

%: %.o 
	$(LD) -o $@ $^

clean: 
	$(RM) *.o

.PHONY: clean

