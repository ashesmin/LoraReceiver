CC = g++

receiver_exe : receiver.o utils.o
	g++ -o receiver_exe receiver.o utils.o -lcurl -ljsoncpp

utils.o : utils.cpp
	g++ -c -o utils.o utils.cpp

receiver.o : receiver.cpp
	g++ -c -o receiver.o receiver.cpp 

clean : 
	rm *.o receiver_exe
