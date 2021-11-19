#include<windows.h>
#include<bits/stdc++.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
int main()
{
	int PORT,MSGSIZE=1024;
	string SERVER_ADDRESS;
	char c[128];
	cout<<"connect tcp://";
	scanf("%s",c);
	string t=c;
	memset(c,0,strlen(c));
	for(int i=0;i<t.length();i++)
	{
		if(t[i]!=':')
			SERVER_ADDRESS.push_back(t[i]);
		else
		{
			for(int j=i+1;j<t.length();j++)
				c[j-i-1]=t[j];
			break;
		}
	}
	PORT=atoi(c);
	cout<<"connected "<<SERVER_ADDRESS<<":"<<PORT<<endl;
	WSADATA wsaData;
	SOCKET sClient;
	SOCKADDR_IN server;
	char szMessage[MSGSIZE];
	int ret;
	WSAStartup(0x0202, &wsaData);
	sClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	memset(&server, 0, sizeof(SOCKADDR_IN));
	server.sin_family = PF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = inet_addr(SERVER_ADDRESS.c_str());
	connect(sClient, (struct sockaddr *) &server, sizeof(SOCKADDR_IN));
	gets(szMessage);
	while (TRUE)
	{
		printf("send:");
		gets(szMessage);
		send(sClient, szMessage, strlen(szMessage), 0);
	}
	closesocket(sClient);
	WSACleanup();
	return 0;
}  
