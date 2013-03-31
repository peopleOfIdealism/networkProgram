#include "../head.h"

int str_cli(FILE *infd, int fd)
{
    char sendbuff[BUFFSIZE_MY];
    char recvbuff[BUFFSIZE_MY];
    int n = 0;
    
    struct args args;
    struct result result;
    
    bzero(sendbuff, BUFFSIZE_MY);
    bzero(recvbuff, BUFFSIZE_MY);
    while(fgets(sendbuff, BUFFSIZE_MY, infd) != NULL)
    {
//        write(fd, sendbuff, 1);
//        sleep(1);
//        write(fd, sendbuff+1, strlen(sendbuff)-1);
        if(2 != sscanf(sendbuff, "%ld%ld", &args.arg1, &args.arg2))
        {
            perror("sscanf");
            printf("invaild input: %s\n", sendbuff);
            continue;
        }
        printf("args size %d\nargs.arg1 %ld\nargs.arg2 %ld\n", sizeof(args),args.arg1, args.arg2);
        write(fd, &args, sizeof(args));
        
        n = read(fd, &result, sizeof(result));
        
        printf("%ld\n", result.sum);
    }
}

int main(void)
{
    int ret = 0;
    int connfd = 0;
    char buff[BUFFSIZE_MY];
    int count = 0;
    char c;
    int n = 0;
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
        str_cli(stdin, connfd);
    else
    {
        perror("connect");
        printf("connect failed\n");
        sleep(2);
        goto again;
    }
    return 0;
}