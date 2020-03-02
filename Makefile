PROGRAMS :=  hw1_ww838\

CODES :=  hw1_ww838.c \

CFLAGS := -std=c11 -O0 -ggdb 

.PHONY : clean

.PHONY : all

clean :
	rm -f $(PROGRAMS)
all :
	make hw1

hw1 : hw1_ww838.c
	$(CC) $(CFLAGS) hw1_ww838.c -o hw1_ww838

