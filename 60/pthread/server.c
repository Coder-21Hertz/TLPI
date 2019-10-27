#include "socket.h"

int sockfd;//������socket
int fds[100];//�ͻ��˵�socketfd,100��Ԫ�أ�fds[0]~fds[99]
int size =100 ;//�������ƽ��������ҵ�����Ϊ100����
typedef struct sockaddr SA;


void init() {
	sockfd = socket(PF_INET,SOCK_STREAM,0);
	if (sockfd == -1)
		errExit("socket");

	struct sockaddr_in addr;
	addr.sin_family = PF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sockfd,(SA*)&addr,sizeof(addr)) == -1)
		errExit("bind");

	if (listen(sockfd,100) == -1)
		errExit("listen");
}


void SendMsgToAll(char* msg) {
	int i;
	for (i = 0; i < size; i++) {
		if (fds[i] != 0) {
			printf("sendto%d\n",fds[i]);
			send(fds[i],msg,strlen(msg),0);
		}
	}
}

static void *service_thread(void *p) {
	int fd = *(int*)p;
	printf("pthread = %d\n",fd);
	while(1) {
		char buf[100] = {};
		if (recv(fd,buf,sizeof(buf),0) <= 0) {
			int i;
			for (i = 0; i < size; i++) {
				if (fd == fds[i]) {
					fds[i] = 0;
					break;
				}
			}
			printf("quit: fd = %dquit\n",fd);
			return NULL;
//                pthread_exit((void*)i);
		}
		//�ѷ��������ܵ�����Ϣ�������еĿͻ���
		SendMsgToAll(buf);
	}
}


void service() {
	printf("Server startup\n");
	while(1) {
		struct sockaddr_in fromaddr;
		socklen_t len = sizeof(fromaddr);
		int fd = accept(sockfd,(SA*)&fromaddr,&len);
		if (fd == -1)
			errExit("accept");

		int i = 0;
		for (i = 0; i < size; i++) {
			if (fds[i] == 0) {
				//��¼�ͻ��˵�socket
				fds[i] = fd;
				printf("fd = %d\n",fd);
				//�пͻ�������֮�������̸߳��˿ͻ�����
				pthread_t tid;
				pthread_create(&tid,0,service_thread,&fd);
				break;
			}
			if (size == i) {
				//���͸��ͻ���˵����������
				char* str = "Sorry, the chat room is full!";
				send(fd,str,strlen(str),0);
				close(fd);
			}
		}
	}
}




int main(int argc, char *argv[]) {
	init();
	service();

	return 0;
}
