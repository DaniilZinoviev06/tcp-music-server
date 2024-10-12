all: server client

server:
	g++ Server/server.cpp -o server
client:
	g++ Client/client.cpp -o client -lsfml-audio -lsfml-system
