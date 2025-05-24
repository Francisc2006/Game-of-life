build:
	gcc gol.c functii_uzuale.c tasks.c f_structuri.c -o gol
run:
	./gol $(ARGS)
clean:
	rm -f gol
