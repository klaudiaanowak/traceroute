CXX=gcc 
CFLAGS= -c
CXXFLAGS= -std=c++11 -Wall -Wextra 
OUTPUT= traceroute
all: traceroute

traceroute: icmp_funcs.o socket_err_handle.o traceroute.o main.o
	$(CXX) $(CXXFLAGS) main.o traceroute.o icmp_funcs.o socket_err_handle.o -o $(OUTPUT)
main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp 
traceroute.o: traceroute.cpp 
	$(CXX) $(CFLAGS) traceroute.cpp traceroute.h
icmp_funcs.o: icmp_funcs.cpp
	$(CXX) $(CFLAGS) icmp_funcs.cpp icmp_funcs.h 
socket_err_handle: socket_err_handle.cpp
	$(CXX) $(CFLAGS) socket_err_handle.cpp socket_err_handle.h

clean:
	rm -rf *.o  *.gch

distclean:
	rm -rf *.o *.gch $(OUTPUT)