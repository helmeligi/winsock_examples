#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <winsock2.h>

using namespace std;

typedef void (*cb)(char*);

#define MAXPACKETSIZE 4096

class TCPServer
{
public:
	TCPServer(string address,int port,cb c);
	void receive();
	string getMessage();
	void Send(string msg);
	void detach();
	void clean();
	void connect();
	bool isConnected();
	~TCPServer();
private:
	static void * rx_runnable(void * argv);
	WSADATA m_wsa;
	SOCKET m_sockfd, m_clientsockfd;
	struct sockaddr_in m_serverAddress;
	struct sockaddr_in m_clientAddress;
	pthread_t m_serverThread;
	char m_msg[ MAXPACKETSIZE];
	string m_message;
	cb m_callback;
	bool m_connect;
};
