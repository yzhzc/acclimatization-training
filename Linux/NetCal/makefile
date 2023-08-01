.PHONY : all
all : client server

client : CalClient.cc
	g++ $^ -o $@ -std=c++17 -ljsoncpp
server : CalServer.cc
	g++ $^ -o $@ -std=c++17 -lpthread -ljsoncpp

.PHONY : clean
clean :
	rm -f client server

