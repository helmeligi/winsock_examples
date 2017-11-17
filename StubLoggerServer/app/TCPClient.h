#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <winsock2.h>
#include <vector>

using namespace std;

class TCPClient
{
  private:
    SOCKET m_sock;
    std::string m_address;
    struct sockaddr_in m_server;
    WSADATA m_wsa;

  public:
    TCPClient(string address, int port);
    bool Send(string data);
    string receive(int size = 4096);
    string read();
};
