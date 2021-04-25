all: class.c
	gcc class.c -o class.out

clean:
	rm -rf *.out