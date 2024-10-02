
final_project: main.o bank_system.o
	g++ -std=c++11 main.o bank_system.o -o final_project

main.o: main.cpp bank_system.hpp acc_class.hpp
	g++ -std=c++11 -Wall -c main.cpp -o main.o

bank_system.o: bank_system.cpp bank_system.hpp acc_class.hpp
	g++ -std=c++11 -Wall -c bank_system.cpp -o bank_system.o

clean:
	rm -f main.o bank_system.o final_project
