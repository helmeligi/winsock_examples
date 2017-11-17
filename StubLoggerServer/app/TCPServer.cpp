#include "TCPServer.h" 

TCPServer::TCPServer(string address, int port,cb c) :
		m_clientsockfd(0),m_callback(c)
{
	m_connect = false;
	if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0) {
		fprintf(stderr, "Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockfd == INVALID_SOCKET) {
		fprintf(stderr, "Could not create socket : %d",
				WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	memset(&m_serverAddress, 0, sizeof(m_serverAddress));
	m_serverAddress.sin_addr.s_addr = inet_addr(address.c_str());
	m_serverAddress.sin_family = AF_INET;
	m_serverAddress.sin_port = htons(port);
	int result = bind(m_sockfd, (struct sockaddr *)&m_serverAddress,
			sizeof(m_serverAddress));
	if (result == SOCKET_ERROR) {
		fprintf(stderr, "Bind failed with error code : %d",
				WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	cout << "Listening ...." << endl;

	listen(m_sockfd, 5);
}

//Blocking Till Connection
void TCPServer::connect(){

	char * str;
	int sosize = sizeof(m_clientAddress);
	m_clientsockfd = accept(m_sockfd,
			(struct sockaddr*)&m_clientAddress,
			&sosize);

	cout << "Client Connected" << endl;

	str = inet_ntoa(m_clientAddress.sin_addr);
	printf(
			"New connection , socket fd is %d , ip is : %s , port : %d \n",
			m_clientsockfd, str,
			m_clientAddress.sin_port);
	m_connect = true;
}

//Blocking Call
void TCPServer::receive()
{
	int valread;
	char msg[MAXPACKETSIZE];


	while (1)
	{
		valread = recv(m_clientsockfd, msg, MAXPACKETSIZE, 0);
		if (valread == 0) {
			//Somebody disconnected , get his details and print
			fprintf(stderr, "Host disconnected!");
			close(m_clientsockfd);
			break;
		} else if (valread == SOCKET_ERROR) {
			int error_code = WSAGetLastError();
			if (error_code == WSAECONNRESET) {

				//Somebody disconnected , get his details and print
				fprintf(stderr, "Host disconnected!");

				//Close the socket and mark as 0 in list for reuse
				closesocket(m_clientsockfd);
				break;
			}
		} else {
			//msg[valread] = '\n';
			m_message = string(msg);
			//cout << msg;
			if(m_callback != NULL)
				m_callback(msg);
		}
	}
}

string
TCPServer::getMessage()
{
	return m_message;
}

void TCPServer::Send(string msg)
{
	int result = send(m_clientsockfd, msg.c_str(), msg.length(), 0);
	if(result == SOCKET_ERROR){
		fprintf (stderr,"send() failed with error code %d\n", WSAGetLastError ());
		exit(1);
	}
}

void TCPServer::clean()
{
	m_message = "";
	memset(m_msg, 0, MAXPACKETSIZE);
}

void TCPServer::detach()
{
	close(m_sockfd);
	close(m_clientsockfd);
	WSACleanup();
}

TCPServer::~TCPServer()
{
	closesocket(m_sockfd);
	close(m_clientsockfd);
	WSACleanup();
}

bool TCPServer::isConnected(){
	return 	m_connect;
}
