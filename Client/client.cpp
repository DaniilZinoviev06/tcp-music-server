#include "../socket.h"
#include "client.h"

int main(){
	struct sockaddr_in sock_addr;

	sock_addr.sin_family = AF_INET; // ipv4
	sock_addr.sin_addr.s_addr = INADDR_ANY;
	sock_addr.sin_port = htons(PORT);

	Client client(sock_addr);

	client.mk_socket();
  client.connection();
}
