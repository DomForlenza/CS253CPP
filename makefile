all: PA

pa.o: pa.cpp pa.h
	g++ -Wall -g -std=c++11 -I. -c pa.cpp -lX11

Main.o: Main.cpp
	g++ -Wall -g -std=c++11 -I. -c Main.cpp -lX11

PoseDisplay.o: PoseDisplay.cpp PoseDisplay.h Point3D.h
	g++ -Wall -g -std=c++11 -I. -c PoseDisplay.cpp -lX11

EuclideanL2.o: EuclideanL2.cpp EuclideanL2.h
	g++ -Wall -g -std=c++11 -I. -c EuclideanL2.cpp -lX11

PA: pa.o Main.o PoseDisplay.o EuclideanL2.o
	g++ -Wall -g  -std=c++11 -I. pa.o Main.o PoseDisplay.o EuclideanL2.o -lX11 -o PA

clean:
	rm *.o PA

package:
	tar -cvf Dominick_Forlenza_PA.tar *.cpp *.h makefile 
