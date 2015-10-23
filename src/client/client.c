#include <stdio.h>
#include "core.h"
#include "utils.h"
#include <sys/socket.h>	/* basic socket definitions */
#include <netinet/in.h>	/* sockaddr_in{} and other Internet defns */
//#include <linux/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

/* Miscellaneous constants */
#define	MAXLINE		4096	/* max text line length */
#define	BUFFSIZE	8192	/* buffer size for reads and writes */

int main(int argc,char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in serveraddr;

    if (argc != 2) {
        fprintf(stderr,"usage:%s <IP Address>\n",argv[0]);
        exit(-1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr,"socket error:%s\n",strerror(errno));
    }

    bzero(&serveraddr,sizeof(struct sockaddr_in));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(13); /* daytime server port */
    if (inet_pton(AF_INET, argv[1], &serveraddr.sin_addr) < 0) {
        fprintf(stderr, "unrecognized IP address:%s\n",argv[1]);
        exit(-1);
    }

    if (connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
        printf("connect error\n");
    }

    while ((n = read(sockfd,recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        if (fputs(recvline,stdout) == EOF) {
            fprintf(stderr,"fputs error");
        }
    }
    if (n < 0) {
        fprintf(stderr,"read error\n");
    }
    exit(0);
}

