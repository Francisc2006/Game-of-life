build:
	gcc gol.c -o gol
run:
	./gol $(ARGS)
clean:
	rm -f gol
