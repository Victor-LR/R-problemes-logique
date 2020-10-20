
all:
	g++ -std=c++14 main.cpp -o test.out
	g++ -std=c++14 ecriture.cpp -o ecrit.out
	
clean:
	rm -f *.o main
