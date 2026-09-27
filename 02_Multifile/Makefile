GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so README
TRASH = *.o *~ o.*
CFLAGS += -fPIC
LDFLAGS += -fPIC -L.

all:    README prog prog-a prog-so

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
	rm -f $(TRASH)
distclean:      clean
	rm -rf $(GENERATES)