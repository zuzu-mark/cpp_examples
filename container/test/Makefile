all:
	cd build && make
	#g++ main.cpp -I../include -I../src -lpthread -lboost_system -lboost_thread
	#g++ main.cpp -I../include -I../src -lpthread -Wl,-Bstatic -lboost_system -Wl,-Bdynamic

d:
	valgrind --tool=helgrind ./build/main
t:
	valgrind ./build/main

