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
int sock;
// client socket discriptor

unsigned int len;
char ch[3]="no";
char ch1[3];
struct sockaddr_in client;
if((sock=socket(AF_INET,SOCK_STREAM,0))==-1)
// client socket is created.
{
perror("socket: ");
exit(-1);
}
client.sin_family=AF_INET;
client.sin_port=htons(10000);
// initializing socket parameters
client.sin_addr.s_addr=INADDR_ANY;
bzero(&client.sin_zero,0);
// appending 8 byte zeroes to 'struct sockaddr_in', to make it equal in size with 'struct sockaddr'.
len=sizeof(struct sockaddr_in);
if((connect(sock,(struct sockaddr *)&client,len))==-1)
//connecting to client
{
perror("connect: ");
exit(-1);
}
	char otp[1000];
	recv(sock, &otp, 1000, 0);
	printf("OTP IS = %s\n",otp);
	char c[1000];
	cout<<"Enter OTP"<<endl;
	scanf("%s",c);
	if(strcmp(c,otp)!=0)
	{
		cout<<"Wrong OTP"<<endl;
		close(sock);
		exit(0);
	}
	cout<<"Connected to server"<<endl;
	while(1)
	{
		
		char word[1000];
		cout<<"Enter word"<<endl;
		scanf("%s",word);
		send(sock,&word,1000,0);
		char ans[1000];
		recv(sock,&ans,1000,0);
		if(strcmp(ans,"not found")==0)
		{
			cout<<"MEaning not found,enter the meaning"<<endl;
			char mean[1000];
			scanf("%s",mean);
			send(sock,&mean,1000,0);
		}
		else
		{
			cout<<"meaning is = ";
			puts(ans);
		}
		int chec=1;
		cout<<"To exit press 0"<<endl;
		cin>>chec;
		if(chec==0)
			break;
	}
	close(sock);
	exit(0);
}
