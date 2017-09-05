SRC=stress_test.C image.C sink.C source.C PNMreader.C PNMwriter.C filters.C logging.C
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o proj3T

.C.o: $<
	g++  -g -I. -c $<

clean:
	rm *.o proj3T

