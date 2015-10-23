#ifndef NETBEE_SERVER_C
#define NETBEE_SERVER_C

#endif // NETBEE_SERVER_C

#include "utils.h"
#include <sys/socket.h>	/* basic socket definitions */
#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
//#include <linux/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>

#include <time.h>
/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */


int main(int argc, char **argv)
{
    int listenfd, connfd,nSize;
    struct sockaddr_in servaddr,clientaddr;
    char buff[MAXLINE + 1];

    timer_t ticks;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0))<0) {
        fprintf(stderr,"socket error:%s\n",strerror(errno));
        exit(-1);
    }

    bzero(&servaddr,sizeof(struct sockaddr_in));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13);

    nSize = sizeof(clientaddr);
    bzero(&clientaddr,nSize);



    if (bind(listenfd,(struct sockaddr *)&servaddr,sizeof(servaddr)) < 0) {
        fprintf(stderr,"bind error:%s\n",strerror(errno));
        exit(-1);
    }

    if (listen(listenfd,10) < 0) {
        fprintf(stderr, "listen error:%s\n",strerror(errno));
        exit(-1);
    }

    for (;;) {
        if ((connfd = accept(listenfd, (struct sockaddr *)&clientaddr, &nSize)) < 0) {
            fprintf(stderr,"accept error:%s\n",strerror(errno));
            exit(-1);
        }

        char *peer;
        if ((peer = inet_ntoa(clientaddr.sin_addr)) != NULL)
            fprintf(stdout,"connectd by %s\n",peer);

        ticks = time(NULL);
        snprintf(buff,sizeof(buff), "%.24s\r\n",ctime(&ticks));
        if (write(connfd, buff, strlen(buff)) < 0) {
            fprintf(stderr,"write error\n");
        }

        close(connfd);
    }
}
