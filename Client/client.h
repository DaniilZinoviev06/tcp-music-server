#include "../socket.h"
#include <SFML/Audio.hpp>
#include <cstring>

class Client {
public:
  Client(struct sockaddr_in sock_addr){
  	sock_address = sock_addr;
  }

  void mk_socket(){
		socket_d = socket(AF_INET, SOCK_STREAM, 0);
		if (socket_d < 0){
			std::cerr << "Клиент: Не удалось создать сокет.\n";
		}
		std::cout << "Клиент: Сокет успешно создан.\n";
	}

  void connection(){
    int conn = connect(socket_d, (struct sockaddr*)&sock_address, sizeof(sock_address));
    if (conn < 0){
      std::cerr << "Клиент: Ошибка соединения.\n";
    }
    std::cout << "Клиент: Соединение установлено." << std::endl;
    receive_music();
  }

  // метод для приема файла
  void receive_music(){
    std::ofstream file("received_music.mp3", std::ios::binary);
    if (!file.is_open()) {
       std::cerr << "Ошибка открытия файла.\n" << std::endl;
    }

    char buffer[1024];
    int bytes_received;
    while ((bytes_received = recv(socket_d, buffer, 1024, 0)) > 0) {
       file.write(buffer, bytes_received);
    }

    std::cout << "Файл успешно получен и сохранен\n" << std::endl;

    file.close();

    sf::Music music;
    if (!music.openFromFile("received_music.mp3")) {
        std::cerr << "Ошибка открытия музыкального файла.\n";
        return;
    }

    std::cout << "Начало воспроизведения музыки.\n";
    music.play();

    while (music.getStatus() == sf::Music::Playing) {
        sf::sleep(sf::milliseconds(100));
    }
  }

private:
  int socket_d; // дескриптор сокета
  struct sockaddr_in sock_address;
};
