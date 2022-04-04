main.exe: main.o PGMimageProcessor.o ConnectedComponent.o
	g++ main.o PGMimageProcessor.o ConnectedComponent.o -o main.exe -std=c++2a

ConnectedComponent.o: ConnectedComponent.cpp
	g++ -c ConnectedComponent.cpp -o ConnectedComponent.o -std=c++2a

PGMimageProcessor.o: PGMimageProcessor.cpp
	g++ -c PGMimageProcessor.cpp -o PGMimageProcessor.o -std=c++2a

main.o: main.cpp
	g++ -c main.cpp -o main.o -std=c++2a

clean:
	rm *.o main.exe

