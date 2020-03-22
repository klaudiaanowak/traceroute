CXX=gcc
CFLAGS= -c
CXXFLAGS= -Wall -Wextra
OUTPUT= traceroute
all: traceroute

traceroute: icmp_funcs.o socket_err_handle.o main.o
	$(CXX) $(CXXFLAGS) main.o icmp_funcs.o socket_err_handle.o -o $(OUTPUT)
main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp 
icmp_funcs.o: icmp_funcs.cpp
	$(CXX) $(CFLAGS) icmp_funcs.cpp icmp_funcs.h 
socket_err_handle: socket_err_handle.cpp
	$(CXX) $(CFLAGS) socket_err_handle.cpp socket_err_handle.h

clean:
	rm -rf *.o  *.gch

distclean:
	rm -rf *.o *.gch $(OUTPUT)