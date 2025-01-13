all: f1.o f2.o

# you can set multiple files to do the same thing and use $@ to know which file underwent it
f1.o f2.o:
	echo $@

clean:
	rm -f f1.o
