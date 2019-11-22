/*
Name:Yuhang Xu
Cis*3210
ID:0926193
Oct.11.2019
A1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

#define BUFSIZE 1024

/* 
 * error - wrapper for perror
 */ 

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char **argv) {
    int sockfd, portno, n;
    struct sockaddr_in serveraddr;
    struct hostent *server;
    char *hostname;
    char tempstr[BUFSIZE];
    char buf[BUFSIZE];
    /* check command line arguments */
    if (argc != 3) {
       fprintf(stderr,"usage: %s <hostname> <port>\n", argv[0]);
       exit(0);
    }
    hostname = argv[1];
    portno = atoi(argv[2]);

    /* socket: create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");

    /* gethostbyname: get the server's DNS entry */
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host as %s\n", hostname);
        exit(0);
    }

    /* build the server's Internet address */
    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
	  (char *)&serveraddr.sin_addr.s_addr, server->h_length);
    serveraddr.sin_port = htons(portno);

    /* connect: create a connection with the server */

    if (connect(sockfd, &serveraddr, sizeof(serveraddr)) < 0) 
        error("ERROR connecting");
    printf("\n");
    printf("/----------------------------------------/\n");
    printf("|Welcome to Online Book Catalogue Client.|\n");
    printf("|OBC have three command SUBMIT/GET/REMOVE|\n");
    printf("|  Make Sure command are in UPPERCASE!   |\n");
    printf("|----------------------------------------|\n");
    printf("\n");
    while(1){
      bzero(buf, BUFSIZE);
      printf(">>>");
      
      fgets(buf, BUFSIZE, stdin);
      strcpy(tempstr,buf);
      n = write(sockfd, buf, strlen(buf));
          if (n < 0) 
            error("ERROR writing to socket");
          bzero(buf, BUFSIZE);
          n = read(sockfd, buf, BUFSIZE);
         // printf("%s", tempstr);
        if ((strncmp(tempstr, "quit", 4)) == 0 || (strncmp(tempstr, "QUIT", 4)) == 0) {  /*Client exit*/
            printf("-Client Exit- \n"); 
            //close(sockfd);
           exit(0);
        }
        if (n < 0) 
           error("ERROR reading from socket"); 

        if(strcmp(buf,"NOMESSAGE")!= 0){ /*If no client message then no echo anything*/
          printf("%s", buf);
      }
           
    }
    printf("connection close\n");
    close(sockfd);


   
    return 0;
}


