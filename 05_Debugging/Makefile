CFLAGS = -Wall -Wextra -O0 -g

all: range
range: range.c
clean: 
	rm -rf range  test*_out*

test1:
	gdb --quiet -x script1.gdb ./range 2>/dev/null | grep -Po '@@@\s*\K.*' > test1_out.txt
	cmp test1_out.txt test1_ref.txt