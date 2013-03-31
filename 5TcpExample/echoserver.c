#include "../head.h"

int str_echo(int fd)
{
    int n = 1;
    char buff[BUFFSIZE_MY];
    long arg1 = 0;
    long arg2 = 0;
//    printf("\nbuff %s\n", buff);
    bzero(buff, BUFFSIZE_MY);
    while(1)
    {
        if(0 == (n = read(fd, buff, BUFFSIZE_MY)))
            return;
        
        if(2 == sscanf(buff, "%ld%ld", &arg1, &arg2))
            snprintf(buff, sizeof(buff), "%ld\n", arg1+arg2);
        else
            snprintf(buff, sizeof(buff), "input error\n");
        n = strlen(buff);
        printf("\nbuff\nlen %d\n%s\n", (int)strlen(buff), buff);
        write(fd, buff, n);
        bzero(buff, BUFFSIZE_MY);
    }
}

void sig_chld(int signo)
{
    pid_t pid;
    int stat;
    while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
        printf("child %d terminated\n", pid);

    return;
}

int main(void)
{
    int ret = 0;
    int listenfd = 0;
    int connfd = 0;
    char buff[BUFFSIZE_MY];
    int len = 0;
    int n = 0;
    pid_t pid;
    
    struct sockaddr_in servaddr;
    
    struct sockaddr_in cliaddr;
    
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(7788);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    
    bind(listenfd, (SA *)&servaddr, sizeof(servaddr));
    
    listen(listenfd, 5);
    
    signal(SIGCHLD, sig_chld);
    while(1)
    {
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (SA *)&cliaddr, &len);
        if(EINTR == errno)
            continue;
        else
            printf("accept error\n");
        if(0 == (pid = fork()))
        {
            close(listenfd);
            str_echo(connfd);
            exit(0);
        }
        close(connfd);
    }
    
    
    return 0;
}
