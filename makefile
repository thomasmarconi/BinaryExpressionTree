HEADER		= bet.h bet.hpp

proj4_driver: proj4_driver.o
	g++ -g -Wall proj4_driver.o -o proj4.x

proj4_driver.o:
	g++ -g -c -Wall proj4_driver.cpp -std=c++11

clean:
	rm *.o *.x; clear
