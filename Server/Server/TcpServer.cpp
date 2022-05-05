#include "TcpServer.h"
#include "TcpSocket.h"
#include "TcpSocket.h"
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <asm/sockios.h>

TcpServer::TcpServer(){}
TcpServer::~TcpServer() {}
//���������ü���
int TcpServer::setListen(unsigned short port) {
	int ret = 0;
	sockaddr_in srv_addr;
	memset(&srv_addr, 0, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(port);
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_lfd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_lfd < 0) {
		ret = errno;
		return ret;
	}
	//���ö˿ڸ���
	int on = 1;
	ret = setsockopt(m_lfd, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
	if (ret == -1) {
		ret = errno;
		return ret;
	}
	socklen_t srv_addr_len = sizeof(srv_addr);
	//�󶨵�ַ�ṹ
	ret = bind(m_lfd, (sockaddr*)&srv_addr, srv_addr_len);
	if (ret == -1) {
		ret = errno;
		return ret;
	}
	ret = listen(m_lfd, 128);
	if (ret == -1) {
		ret = errno;
		return ret;
	}
}

// �ȴ������ܿͻ�����������, Ĭ�����ӳ�ʱʱ��Ϊ10000s
TcpSocket* TcpServer::acceptConnect(int timeout) {
	int ret = 0;
	fd_set accept_fdset;
	struct timeval to = {timeout, 0};
	FD_ZERO(&accept_fdset);
	FD_SET(m_lfd, &accept_fdset);
	do {
		ret = select(m_lfd + 1, &accept_fdset, NULL, NULL, &to);
	} while (ret < 0 && errno ==EINTR);

	//��������
	// һ������ ��select�¼���������ʾ�Եȷ�������������֣��ͻ����������ӽ���
	// ��ʱ�ٵ���accept���������
	struct sockaddr_in addrClient;
	socklen_t addrClient_len = sizeof(addrClient);
	int connfd = accept(m_lfd, (struct sockaddr*)&addrClient, &addrClient_len);
	if (connfd == -1) {
		return NULL;
	}
	return new TcpSocket(connfd);
}

void TcpServer::closefd() {
	if (m_lfd > 0) {
		close(m_lfd);
	}
}