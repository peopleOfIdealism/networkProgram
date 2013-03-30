#include "../head.h"

int main(void)
{
    int ret = 0;
    int listenfd = 0;
    int connfd = 0;
    char buff[BUFFSIZE_MY];
    int len = 0;
    
    struct sockaddr_in servaddr;
    
    struct sockaddr_in cliaddr;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7788);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    
    listen(listenfd, 5);
    
    len = sizeof(cliaddr);
    
    while((connfd = accept(listenfd, (SA *)&cliaddr, &len)) > 0)
    {
        read(connfd, buff, BUFFSIZE_MY);
        printf("receive buff %s\n", buff);
        write(connfd, buff, BUFFSIZE_MY);
    }
    
    
    return 0;
}