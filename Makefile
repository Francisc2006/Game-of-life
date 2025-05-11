build:
	gcc gol.c functii_uzuale.c tasks.c f_stive+liste+arbori.c -o gol
run:
	./gol $(ARGS)
clean:
	rm -f gol
