enigma: main.o plugboard.o rotor.o reflector.o enigma.o helper.o
	g++ -g -Wall main.o plugboard.o rotor.o reflector.o enigma.o helper.o -o enigma

helper.o: helper.cpp
	g++ -g -Wall -c helper.cpp

enigma.o: enigma.cpp enigma.h plugboard.h rotor.h reflector.h helper.h
	g++ -g -Wall -c enigma.cpp

reflector.o: reflector.cpp reflector.h helper.h
	g++ -g -Wall -c reflector.cpp

rotor.o: rotor.cpp rotor.h helper.h
	g++ -g -Wall -c rotor.cpp

plugboard.o: plugboard.cpp plugboard.h helper.h
	g++ -g -Wall -c plugboard.cpp

main.o: main.cpp enigma.h helper.h
	g++ -g -Wall -c main.cpp

clean:
	rm -f *.o enigma
