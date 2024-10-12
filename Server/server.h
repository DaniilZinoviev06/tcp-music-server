#include "../socket.h"
#include <fstream>

class Server
{
public:
	Server(struct sockaddr_in sock_addr){
		sock_address = sock_addr;
	}

	void mk_socket(){
		socket_d = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_d < 0){
			std::cerr << "Не удалось создать сокет.\n";
		}
		std::cout << "Сокет успешно создан.\n";
	}

	void bind_socket(){
		int b_socket = bind(socket_d, (struct sockaddr*) &sock_address, sizeof(sock_address));
		if (b_socket < 0){
			std::cerr << "Не удалось привязать сокет.\n";
		}
		std::cout << "Сокет успешно привязан.\n";
	}

	void listen_socket(){
		int l_socket = listen(socket_d, 5);
		if (l_socket < 0){
			std::cerr << "Ошибка при прослушивании.\n";
		}
		std::cout << "Сервер начал прослушивать, порт: " << PORT << std::endl;
	}

  // метод для того, чтобы сервер ожид-л подключ-е
	void connection(){
		int sock_size = sizeof(sock_address);
		int conn = accept(socket_d, (struct sockaddr*) &sock_address, (socklen_t *)&sock_size);
		if (conn < 0){
			std::cerr << "Ошибка соединения.\n";
		}
		std::cout << "Соединение установлено.\n" << std::endl;
		send_music(conn);
	}

	// метод для передачи музыки клиенту
	void send_music(int connection){
		std::ifstream mp3_file("sample.mp3", std::ios::binary);
		if(!mp3_file.is_open()){
			std::cerr << "Файл не найден.\n";
		}
		std::cout << "Файл найден. Отправка началась.\n";

		char buffer[1024];
		while (!mp3_file.eof()){
			mp3_file.read(buffer, 1024);
			int bytes_read = mp3_file.gcount();
			send(connection, buffer, bytes_read, 0);
		}

		mp3_file.close();
	}

private:
	int socket_d; // дескриптор сокета
	struct sockaddr_in sock_address;
};
