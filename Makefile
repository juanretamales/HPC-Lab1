HEADERS =

default: simdsort

simdsort: simdsort.c $(HEADERS)
		gcc -c simdsort.c -o simdsort.o
		./simdsort.o -i 16inum.raw -o output.raw -N 16

clean:
	rm -f simdsort.o
	rm -f output.raw
