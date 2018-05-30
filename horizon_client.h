#ifndef HORIZON_CLIENT_H
#define HORIZON_CLIENT_H

#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <WinSock2.h>
	#include <WS2tcpip.h>
#else
	#include <sys/socket.h>
#endif

#define BUFFER_SIZE 9192
#define BUFFER_RECEIVE_MIN 2048
#define PORT_NO 6775
#define HOST_IP "128.149.23.134"

typedef struct client_data
{
	WSAData wsa_data;
	SOCKET sock;
	sockaddr_in address;
} client_data;

bool horizon_client_setup(client_data* cd, char* ip, int p);
void horizon_client_receive(client_data* cd, char* msg, char* buffer);
void horizon_client_destroy(client_data* cd);

#endif