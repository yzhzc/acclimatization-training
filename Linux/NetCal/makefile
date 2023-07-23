.PHONY : all
all : client server

client : CalClient.cc
	g++ $^ -o $@ -std=c++17
server : CalServer.cc
	g++ $^ -o $@ -std=c++17 -lpthread

.PHONY : clean
clean :
	rm -f client server

