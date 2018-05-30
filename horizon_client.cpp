#include "horizon_client.h"
#include "horizon_data.h"

//winsock lib
#pragma comment(lib, "ws2_32.lib")

bool horizon_client_setup(client_data* cd, char* ip, int p)
{
	// Load winsock
	if (WSAStartup(MAKEWORD(2, 2), &cd->wsa_data) != 0){
		WSACleanup();
		return false;
	}

	// Prepare socket
	cd->sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (cd->sock == -1){
		WSACleanup();
		return false;
	}

	// Prepare connection
	memset(&cd->address, 0, sizeof(cd->address));
	cd->address.sin_family = AF_INET;
	cd->address.sin_port = htons(p);
	inet_pton(AF_INET, ip, &cd->address.sin_addr);

	// Attempt connection
	if (connect(cd->sock, (struct sockaddr*)&cd->address, sizeof(cd->address)) == -1){
		WSACleanup();
		closesocket(cd->sock);
		return false;
	}

	return true;
}

void horizon_client_destroy(client_data* cd)
{
	closesocket(cd->sock);
	WSACleanup();
}

void horizon_client_receive(client_data* cd, char* msg, char* buffer)
{
	while (true)
	{
		int send_rec = send(cd->sock, msg, strlen(msg), 0);
		if (send_rec == SOCKET_ERROR)
			WSACleanup();
		else
		{
			int bytes_rec = recv(cd->sock, buffer, BUFFER_SIZE, 0);
			if (bytes_rec > BUFFER_RECEIVE_MIN){
				buffer[bytes_rec] = 0;
				printf("%s\n", buffer);
				break;
			}
		}
	}
}