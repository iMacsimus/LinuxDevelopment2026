GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
TRASH = *.o *~ o.* *.txt
CFLAGS += -fPIC
LDFLAGS += -fPIC -L.

all:    README prog prog-a prog-so test

prog:   const.o fun.o prog.o
prog-a: prog.o liboutput_static.a
	cc $(LDFLAGS) -o $@ prog.o -loutput_static
prog-so: prog.o liboutput.so
	cc $(LDFLAGS) -o $@ prog.o -loutput -Wl,-rpath,'$$ORIGIN'
liboutput_static.a: fun.o const.o
	ar rcs $@ $^
liboutput.so: fun.o const.o
	cc -shared -o $@ $^
README: prog
	./$< 2> $@
fun.o:  outlib.h

clean:
	rm -f $(TRASH) $(GENERATES)

test-0-args = 
test-1-args = 1
test-3-args = 1 2 3

test-%: prog prog-a prog-so
	./prog $($@-args) > prog-$*.txt 2>&1
	./prog-a $($@-args) > prog-a-$*.txt 2>&1
	./prog-so $($@-args) > prog-so-$*.txt 2>&1
	cmp prog-$*.txt prog-a-$*.txt
	cmp prog-$*.txt prog-so-$*.txt

test: test-0 test-1 test-3