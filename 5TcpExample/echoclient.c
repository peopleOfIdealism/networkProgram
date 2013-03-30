#include "../head.h"


int main(void)
{
    int ret = 0;
    int connfd = 0;
    char buff[BUFFSIZE_MY];
    int count = 0;
    char c;
    
    struct sockaddr_in servaddr;
    
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7788);
    if(inet_pton(AF_INET, "192.168.1.66", &servaddr) <= 0)
        printf("inet_pton error\n");
    
    connfd = socket(AF_INET, SOCK_STREAM, 0);
    if(connfd <= 0)
        printf("socket error\n");
    
    ret = connect(connfd, (SA *)&servaddr, sizeof(servaddr));
    if(ret > 0)
    for( ; ; )
    {
        count = 0;
        bzero(buff, strlen(buff));
        while((c = getchar()) != EOF)
        {
            buff[count++] = c;
            if('\n' == c)
            {
                buff[count++] = 0;//NULL
            }
        }
        if(count != write(connfd, buff))
            printf("write error\n");
        bzero(buff, strlen(buff));
        while(read(connfd, buff, BUFFSIZE_MY) > 0)
            printf("receive:\n%s\n", buff);
    }
    else
    {
        printf("connect failed\n");
    }
    return 0;
}