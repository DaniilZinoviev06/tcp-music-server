#include "../socket.h"
#include "server.h"

int main(){
	struct sockaddr_in sock_addr;

	sock_addr.sin_family = AF_INET; // ipv4
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	sock_addr.sin_port = htons(PORT);


	Server server(sock_addr);

	server.mk_socket();
	server.bind_socket();
	server.listen_socket();
	server.connection();
}
