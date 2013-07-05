/*
 * =====================================================================================
 *
 *       Filename:  echo_server.cpp
 *
 *    Description:	a echo server
 *
 *        Version:  1.0
 *        Created:  07/05/2013 12:37:27 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  李海鑫 (xavier), xavier.ssdut@gmail.com
 *        Company:  ssdut.dlut.edu.cn
 *
 * =====================================================================================
 */

#include	<cstdio>
#include	<unistd.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<sys/types.h>

static const int SERVER_PORT = 15382;

static const int BUF_SIZE = 1024;

int main(int argc, char *argv[])
{
	int listen_fd ;
	int client_fd ;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	char buffer[BUF_SIZE];

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	
	//打开一个socket file descripor
	listen_fd = socket(AF_INET, SOCK_STREAM, 0);

	//绑定本地网络地址
	bind (listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));

	//开始监听
	listen(listen_fd, 5);
	printf("start listening...\n");

	socklen_t client_len = sizeof(client_addr);
	for(;;)
	{
		client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_len);
		printf("server: got connection from (%s:%d)\n", 
				inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

		int recv_num = recv(client_fd, buffer, BUF_SIZE, 0);
		buffer[recv_num] = 0;
		printf("server:[receive] : %s\n", buffer);

		send(client_fd, buffer, recv_num, 0);

		close(client_fd);
	}
}
