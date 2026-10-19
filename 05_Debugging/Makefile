CFLAGS = -Wall -Wextra -O0 -g

all: range
range: range.c
clean: 
	rm -rf range

test1:
	gdb --quiet -x script1.gdb ./range 2>/dev/null | grep "@@@"