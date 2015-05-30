GLOB_FILES = main.c main.h

gauss: $(GLOB_FILES) gauss.h gauss.c
	gcc main.c gauss.c -std=c99 -o gauss -Wall -pedantic -D _USE_GAUSS_

jakobi: $(GLOB_FILES) jakobi.h jakobi.c
	gcc main.c jakobi.c -std=c99 -o jakobi -Wall -pedantic -D _USE_JAKOBI_

gauss-seidl: $(GLOB_FILES) gauss-seidl.h gauss-seidl.c
	gcc main.c gauss-seidl.c -std=c99 -o gauss-seidl -Wall -pedantic -D _USE_GS_

clean:
	rm -f jakobi gauss gauss-seidl

