#include<bits/stdc++.h>
#include<windows.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main()
{
	int PORT=8080,MSGSIZE=1024;
	cout<<"listen on tcp://127.0.0.1:";
	cin>>PORT;
	WSADATA wsaData;
	SOCKET sListen;
	SOCKET sClient;
	SOCKADDR_IN local;
	SOCKADDR_IN client;
	char szMessage[MSGSIZE];
	int ret;
	cout<<"listening on port "<<PORT<<endl;
	int iaddrSize = sizeof(SOCKADDR_IN);
	WSAStartup(0x0202, &wsaData);
	sListen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	local.sin_family = AF_INET;
	local.sin_port = htons(PORT);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(sListen, (struct sockaddr *) &local, sizeof(SOCKADDR_IN));
	listen(sListen, 1);
	sClient = accept(sListen, (struct sockaddr *) &client, &iaddrSize);
	printf("accepted client:%s:%d\n", inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	while (1)
	{
	    ret = recv(sClient, szMessage, MSGSIZE, 0);
	    if(ret==-1)
	    {
	    	MessageBox(0,"client quitted","error",MB_OK+16);
	    	exit(0);
		}
	    szMessage[ret] = '\0';
	    printf("received [%d bytes]: %s\n", ret, szMessage);
	    cout<<"\a";
	}
	return 0;
}  
