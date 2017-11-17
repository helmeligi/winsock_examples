#include "TCPClient.h"


TCPClient::TCPClient(string address , int port)
{
	if (WSAStartup(MAKEWORD(2, 2), &m_wsa) != 0) {
		fprintf(stderr, "Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET) {
		fprintf(stderr, "Could not create socket : %d",
				WSAGetLastError());
		exit(EXIT_FAILURE);
	}

	memset(&m_server, 0, sizeof(m_server));
	m_server.sin_addr.s_addr = inet_addr(address.c_str());
	m_server.sin_family = AF_INET;
	m_server.sin_port = htons(port);


  	if (connect(m_sock , (struct sockaddr *)&m_server , sizeof(m_server)) < 0)
  	{
    		perror("connect failed. Error");
		exit(EXIT_FAILURE);
  	}

}

bool TCPClient::Send(string data)
{
	if( send(m_sock , data.c_str() , strlen( data.c_str() ) , 0) < 0)
	{
		cout << "Send failed : " << data << endl;
		return false;
	}
	return true;
}

string TCPClient::receive(int size)
{
  	char buffer[size];
  	string reply;
	if( recv(m_sock , buffer , size, 0) < 0)// sizeof(buffer) 
  	{
	    cout << "receive failed!" << endl;
  	}
	buffer[size]='\0';
  	reply = buffer;
  	return reply;
}

string TCPClient::read()
{
  	char buffer[1] = {};
  	string reply;
  	while (buffer[0] != '\n') {
    		if( recv(m_sock , buffer , sizeof(buffer) , 0) < 0)
    		{
      			cout << "receive failed!" << endl;
      			break;
    		}
		reply += buffer[0];
	}
	return reply;
}
