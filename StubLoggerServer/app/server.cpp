#include <iostream>
#include "TCPServer.h"


TCPServer* t;


void rxCallBack(char * m)
{
	cout<<m;

}


int main()
{
	cout<<"Server Started"<<endl;
	t= new TCPServer("127.0.0.1",11999,rxCallBack);



	//wait till connection
	t->connect();

	t->Send("Hello From Your Server, Start Sending Your Data!");
	t->receive();

	delete t;
	return 0;
}
