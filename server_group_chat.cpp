#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include "conio.h"
#include <windows.h>
#include <process.h>
#include <math.h>
#include <iostream>
#define QLEN       5
#define    WSVERS    MAKEWORD(2, 2)
#define    BUFLEN    2000
using namespace std;
SOCKET    msock, ssock;
SOCKET    sockets[100] = {NULL};
int cc;
char    *pts;
time_t    now;
char buf[2000];
char *input;
HANDLE hThread1,hThread[100] = {NULL};
unsigned int threadID,ThreadID[100],number;
struct    sockaddr_in fsin;
struct    sockaddr_in Sin;
unsigned int __stdcall Chat(PVOID PM)
{
	char buf1[2000];
	char buf2[2000];
	char buf3[2000];
	char buf4[2000];
	(void) time(&now);
	pts = ctime(&now);
	sockets[number] = ssock;
	SOCKET    sock = ssock;
	ThreadID[number] = threadID;
	unsigned int threadid = threadID;
	sprintf(buf2,"thread No.%d,client %s:%d connected\0",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port);
	printf("%s ",buf2);
	for(int i=0; i<=number; i++)
	{
		if(sockets[i] != NULL && sockets[i] != sock)
		{
			send(sockets[i],buf2, sizeof(buf2), 0);
			cout<< "\nsend message to thread No."<< ThreadID[i] << " successful" <<endl;
		}
	}
	cout<< endl;
flag1:
	cc = recv(sock, buf3, BUFLEN, 0);
	if(cc == SOCKET_ERROR|| cc == 0)
	{

		sprintf( buf3,"thread No.%d,client %s:%d quit\0",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port);
		sock = NULL;
		sockets[number] = NULL;
		CloseHandle(hThread[number]);
		printf("%s ", buf3);
		for(int i=0; i<=number; i++)
		{
			if(sockets[i] != NULL && sockets[i] != sock)
			{
				(void) send(sockets[i], buf3, sizeof(buf3), 0);
				printf("\nsend to thread No.%d successful",ThreadID[i]);
			}
		}
		printf(" \n");
	}
	else if(cc > 0)
	{
		(void) time(&now);
		pts = ctime(&now);
		sprintf(buf4,"thread No.%d,client %s:%d says %s\0",threadid,inet_ntoa(fsin.sin_addr),fsin.sin_port,buf3);
		printf("%s ",buf4);

		for(int i=0; i<=number; i++)
		{
			if(sockets[i] != NULL && sockets[i] != sock)
			{
				(void) send(sockets[i],buf4, sizeof(buf4), 0);
				printf("\nsend to thread No.%d successful",ThreadID[i]);
			}
		}
		printf(" \n");
		goto flag1;
	}
	closesocket(sock);
	return 0;
}
int  main(int argc, char *argv[])
{
	int     alen;
	WSADATA wsadata;
	char    service[64];
	cout<<"listen on tcp://127.0.0.1:";
	cin>>service;
	WSAStartup(WSVERS, &wsadata);
	msock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&Sin, 0, sizeof(Sin));
	Sin.sin_family = AF_INET;
	Sin.sin_addr.s_addr = INADDR_ANY;
	Sin.sin_port = htons((u_short)atoi(service));
	if( bind(msock, (struct sockaddr *)&Sin, sizeof(Sin)) == 0)
	{
		cout<< "server bind() successful,running on port " << service << endl;
		if(listen(msock, 5) == 0)
		{
			cout<< "server listen() successful"<<endl;
			cout<< "chatting room server started successfully" <<endl;
		}
		else
		{
			cout<< "server listen() failed" << endl;
			WSACleanup();
			exit(0);
		}
	}
	else
	{
		cout<< "server bind() failed" << endl;
		WSACleanup();
		exit(0);
	}
	(void) time(&now);
	pts = ctime(&now);
	number = -1;
	while(1)
	{
		alen = sizeof(struct sockaddr);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		number ++;
		hThread[number] = (HANDLE)_beginthreadex(NULL, 0,Chat,NULL, 0, &threadID);
	}
	closesocket(msock);
	WSACleanup();
	return 0;
}
