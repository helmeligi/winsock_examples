#include <iostream>
#include "TCPClient.h"
#include <pthread.h>
#include <unistd.h>
#include<stdio.h>
#include<winsock2.h>
#include <stdbool.h>
#include <limits.h>
#include <stdint.h>

int runClient()
{

	TCPClient tcp("127.0.0.1", 11999);

	string rec = tcp.receive();
	if (rec != "")
			{
		cout << "Server Response:" << rec << endl;
	}

	while (1)
	{
		string msg = "Hello From the other side";

		tcp.Send(msg);


		sleep(1);
	}
	exit(0);
	return 0;

}
