CFLAGS = -Wall -Wextra -O0 -g

all: range
range: range.c
clean: 
	rm -rf range  test*_out*

test1: range
	gdb --quiet -x script1.gdb ./range 2>/dev/null | grep -Po '@@@\s*\K.*' > test1_out.txt
	cmp test1_out.txt test1_ref.txt

test2: range
	gdb --quiet -x script2.gdb ./range 2>/dev/null | grep -Po '@@@\s*\K.*' > test2_out.txt
	cmp test2_out.txt test2_ref.txt

test: test1 test2