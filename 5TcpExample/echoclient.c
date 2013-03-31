#include "../head.h"


int main(void)
{
    int ret = 0;
    int connfd = 0;
    char buff[BUFFSIZE_MY];
    int count = 0;
    char c;
    
    struct sockaddr_in servaddr;
    
    connfd = socket(PF_INET, SOCK_STREAM, 0);
    
    bzero(&servaddr, sizeof(servaddr));
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7788);
    if(inet_pton(AF_INET, "192.168.1.66", &servaddr.sin_addr) <= 0)
        printf("inet_pton error\n");
    

    if(connfd <= 0)
    {
        perror("socket error\n");
        printf("socket error\n");
    }
again:
    ret = connect(connfd, (SA *)&servaddr, sizeof(servaddr));
    if(ret >= 0)
    for( ; ; )
    {
        count = 0;
        bzero(buff, strlen(buff));
        while((c = getchar()) != '\n')
        {
            buff[count++] = c;
/*            if('\n' == c)
            {
                buff[count++] = 0;//NULL
            }
            */
        }
        buff[count++] = c;
        buff[count++] = 0;
        if(count != write(connfd, buff, count))
            printf("write error\n");
        bzero(buff, strlen(buff));
        while(read(connfd, buff, BUFFSIZE_MY) > 0)
            printf("receive:\n%s\n", buff);
    }
    else
    {
        perror("connect");
        printf("connect failed\n");
        sleep(2);
        goto again;
    }
    return 0;
}