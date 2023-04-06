bsl: main.o integer_math.o poly_math.o elliptic_math.o algorithms.o
	gcc -Os -Wall -o bsl main.o integer_math.o poly_math.o elliptic_math.o algorithms.o

integer_math.o: integer_math.h binary_field.h integer_math.c
	gcc -Os -Wall -c integer_math.c

poly_math.o: integer_math.h binary_field.h poly_math.h poly_math.c
	gcc -Os -Wall -c poly_math.c

elliptic_math.o: integer_math.h binary_field.h elliptic_math.h elliptic_math.c
	gcc -Os -Wall -c elliptic_math.c

algorithms.o: integer_math.h binary_field.h elliptic_math.h algorithms.h algorithms.c
	gcc -Os -Wall -c algorithms.c

clean: 
	rm bsl *.o