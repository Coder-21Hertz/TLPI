#include "socket.h"

int sockfd;//¿Í»§¶Ësocket
typedef struct sockaddr SA;
char name[30];


void init(){
    sockfd = socket(PF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in addr;
    addr.sin_family = PF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (connect(sockfd,(SA*)&addr,sizeof(addr)) == -1)
       errExit("connect");
       
    printf("The client started successfully.\n");
}

static void *recv_thread(void *p){
    while(1){
        char buf[100] = {};
        if (recv(sockfd,buf,sizeof(buf),0) <= 0){
            return NULL;
        }
        printf("%s\n",buf);
    }
}

void start(){
    pthread_t id;
    pthread_create(&id,0,recv_thread,0);
    char buf2[100] = {};
    sprintf(buf2,"%s joined the chat room.",name);
    send(sockfd,buf2,strlen(buf2),0);
    while(1){
        char buf[100] = {};
        scanf("%s",buf);
        char msg[131] = {};
        sprintf(msg,"%s:%s",name,buf);
        send(sockfd,msg,strlen(msg),0);
        if (strcmp(buf,"bye") == 0){
            memset(buf2,0,sizeof(buf2));
            sprintf(buf2,"%s left the chat room.",name);
            send(sockfd,buf2,strlen(buf2),0);
            break;
        }
    }
    close(sockfd);
}

 
int main(){
    init();
    printf("Please enter your name: ");
    scanf("%s",name);
    start();
    return 0;
}

