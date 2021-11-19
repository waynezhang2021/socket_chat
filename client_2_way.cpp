#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <process.h>
#include <math.h>
#include <iostream>
#define    BUFLEN        2000
#define WSVERS        MAKEWORD(2, 2)
using namespace std;
SOCKET    sock,sockets[100] = {NULL};
char *packet = NULL;
char *pts,*input;
HANDLE hThread;
unsigned threadID;
unsigned int __stdcall Chat(PVOID PM )
{
	time_t    now;
	(void) time(&now);
	pts = ctime(&now);
	char buf[2000];
	while(1)
	{
		int cc = recv(sock, buf, BUFLEN, 0);
		cout<< endl;
		if(cc == SOCKET_ERROR|| cc == 0)
		{
			cout<< "error:lost connection to server,error id " << GetLastError()<< endl;
			CloseHandle(hThread);
			(void)closesocket(sock);
			break;
		}
		else if(cc > 0)
		{
			printf("received[%d bytes]:%s\n",cc,buf);
		}
	}
	return 0;
}
int main(int argc, char *argv[])
{
	time_t    now;
	(void) time(&now);
	pts = ctime(&now);
	char    host[64];
	char service[64];
	cout<<"connect tcp://";
	string t;
	cin>>t;
	int hptr=0,sptr=0;
	for(int i=0;i<t.length();i++)
	{
		if(t[i]!=':')
		{
			host[hptr]=t[i];
			hptr++;
		}
		else
		{
			host[hptr]='\0';
			for(int j=i+1;j<t.length();j++)
			{
				service[sptr]=t[j];
				sptr++;
			}
			service[sptr]='\0';
			break;
		}
	}
	struct  sockaddr_in sin;
	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata);
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons((u_short)atoi(service));
	sin.sin_addr.s_addr = inet_addr(host);
	sock = socket(PF_INET, SOCK_STREAM,0);
	connect(sock, (struct sockaddr *)&sin, sizeof(sin));
	printf("connected %s:%s\ntwo-way client started\n",host,service);
	hThread = (HANDLE)_beginthreadex(NULL, 0,Chat, NULL, 0, &threadID);
	while(1)
	{
		char buf1[2000];
		printf("send:");
		cin>> buf1;
		send(sock,buf1, sizeof(buf1), 0);
	}
end:
	CloseHandle(hThread);
	closesocket(sock);
	WSACleanup();
	getchar();
	return 0;
}
