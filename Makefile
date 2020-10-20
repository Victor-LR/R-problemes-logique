
all:
	g++ -std=c++14 ecriture.cpp main.cpp -o test.out

clean:
	rm -f *.o main
