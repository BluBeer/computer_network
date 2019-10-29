#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main()
{
	int ssock,csock;
	// creating server and client socket discriptor

	unsigned int len;
	struct sockaddr_in server,client;
	// creating server & client socket object
	if((ssock=socket(AF_INET,SOCK_STREAM,0))==-1)
	// creating socket
	{
		perror("socket: ");
		exit(-1);
	}
	server.sin_family=AF_INET;
	server.sin_port=htons(10000);
	// initializing server socket parameters.
	server.sin_addr.s_addr=INADDR_ANY;
	bzero(&server.sin_zero,0);
	// appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.
	len=sizeof(struct sockaddr_in);
	if((bind(ssock,(struct sockaddr *)&server,len))==-1)
	// binding port & IP
	{
		perror("bind error: ");
		exit(-1);
	}
	if((listen(ssock,5))==-1)
	// listening for client
	{
		perror("listen error: ");
		exit(-1);
	}
	if((csock=accept(ssock,(struct sockaddr *)&client,&len))==-1)
	// accepting connection
	{
		perror("accept error: ");
		exit(-1);
	}
	cout<<"Server is running"<<endl;
	char otp[1000]="hello";
	send(csock, &otp, 1000, 0);
	while(1)
	{
		char word[1000];
		int chec=0;
		recv(csock,&word,1000,0);
		string wo(word),xyz,mean;
		fstream fptr,gptr;
		fptr.open("word.txt");
		gptr.open("meaning.txt");
		while(fptr >> xyz)
		{
			getline(gptr,mean);
			if(xyz==wo)
			{
				char mea[1000];
				strcpy(mea,mean.c_str());
				send(csock,&mea,1000,0);
				chec=1;
				break;
			}
		}
		if(chec==0)
		{
			char mea[1000]="not found";
			send(csock,&mea,1000,0);
			char abc[1000];
			recv(csock,&abc,1000,0);
			string ab(abc);
			fptr.close();
			fptr.open("word.txt", ios::app);
			fptr << wo;
			fptr << '\n';
			gptr.close();
			gptr.open("meaning.txt",ios::app);
			gptr << ab;
			gptr << '\n';
		}
			
		fptr.close();
		gptr.close();
	}
		
	close(ssock);
}
