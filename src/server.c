/*
Name:Yuhang Xu
Cis*3210
ID:0926193
Oct.11.2019
A1
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <time.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "linkList.h"
#define BUFSIZE 1024
#define MAX_THREADS 64

pthread_t* thread_handles;
int numThreads = 0;  
#if 0

#endif

/*
 * error - wrapper for perror
 */
void error(char *msg) {
  perror(msg);
  exit(1);
}




 BookCatalogue * bookList = NULL;


void *server(void *arg){    // This function is about parsing and connecting
  
    char requestString[2000] = "";
    char ReturnMessage[2000] = "NOMESSAGE";
    char buf[BUFSIZE]; /* Message buffer */
    int n;             /* Message byte size */

    int childfd = *(int*)arg; //Get current child number
    while(1){
        /* 
         * read: read input string from the client
         */
        bzero(buf, BUFSIZE);
        n = read(childfd, buf, BUFSIZE);
        if ((strncmp(buf, "quit", 4)) == 0 || (strncmp(buf, "QUIT", 4)) == 0) { // detect if user have quit
                printf("A user has disconnected\n");
                break;
            }
        if (strlen(buf) == 0) { 
                printf("A user has disconnected\n");
                break;
            }


        if (n < 0) 
          error("ERROR reading from socket");

        if(n == 1 && (strcmp(buf, "\n")) == 0){ /*When user press ENTER two timeand their input is nothing*/
          char *token = strtok(requestString, " \n"); 
          int counter = 1;
          char requestCommand[500] ="";
          char requestTitle[500] = "";
          char requestAuthor[500]= "";
          char requestLocation[500]= "";
          int titleFlag = 0; // if there is title
          int authroFlag=0;// if there is author
          int locationFlag=0;// if there is location
          int don = 0; // avoid flag
            while (token != NULL) { 
              //Get book info
                if(strcmp(token, "TITLE") ==0){
                    titleFlag = 1;
                    authroFlag=0;
                    locationFlag=0;
                     don = 1;
                    //continue;
                }else if(strcmp(token, "AUTHOR") ==0){
                    authroFlag = 1;
                    locationFlag=0;
                    titleFlag = 0;
                    don = 1;
                    //continue;
                }else if(strcmp(token, "LOCATION") ==0){
                    locationFlag = 1;
                    titleFlag = 0;
                    authroFlag = 0;
                    don = 1;
                    //continue;
                }


              //Get content
              if(titleFlag == 1 && don ==0){
                  if(strlen(requestTitle) == 0){
                      strcat(requestTitle,token);
                  }else{
                      strcat(requestTitle," ");
                      strcat(requestTitle,token);
                  }
                //titleFlag = 0;
              }else if(authroFlag == 1  && don == 0){
                if(strlen(requestAuthor) == 0){
                      strcat(requestAuthor,token);
                  }else{
                      strcat(requestAuthor," ");
                      strcat(requestAuthor,token);
                  }
               // authroFlag = 0;
              }else if(locationFlag == 1  && don == 0){
                  if(strlen(requestLocation) == 0){
                      strcat(requestLocation,token);
                  }else{
                      strcat(requestLocation," ");
                      strcat(requestLocation,token);
                  }
              }
              //Get command
                if(counter == 1){
                    if(strcmp(token, "SUBMIT") == 0){
                      strcpy(requestCommand,token);
                    }else if(strcmp(token, "GET") == 0){
                       strcpy(requestCommand,token);
                    }else if (strcmp(token, "REMOVE") == 0){
                         strcpy(requestCommand,token);
                    }else{                                  //if there is a command that's not found.
                        strcpy(ReturnMessage,"");
                        strcat(ReturnMessage,"501, Unrecognized or not implemented\n");
                        break;
                    }
                }


                don = 0;
                //printf("%s", token); 
                token = strtok(NULL, " \n"); 
                counter++;
              }
              
          printf("\n--------------\n");/*This print what user have entered*/
          printf("\nUser message(Any fields that's not filled out would be put UNKNOWN):\n");
          printf("%s\n",requestCommand);
          printf("TITLE: %s\n",requestTitle);
          printf("AUTHOR: %s\n",requestAuthor);
          printf("LOCATION: %s\n",requestLocation);
          printf("--------------\n");

          if(strcmp(requestCommand, "SUBMIT") == 0 ){  // If user command is submit
            if(strcmp(requestTitle, "") == 0 && strcmp(requestAuthor, "") == 0 && strcmp(requestLocation, "") == 0){
                  strcpy(ReturnMessage,"");
                  strcat(ReturnMessage,"401,Bad request(Check your syntax)\n");
                  printf("Syntax error, empty record!\n");
            }else{
                  if(strcmp(requestTitle, "") == 0 ){
                      strcpy(requestTitle,"UNKNOWN");
                  }if(strcmp(requestAuthor, "") == 0 ){
                      strcpy(requestAuthor,"UNKNOWN");
                  }if(strcmp(requestLocation, "") == 0 ){
                      strcpy(requestLocation,"UNKNOWN");
                  }

                  if(searchList(bookList,requestTitle, requestAuthor,requestLocation)!= 9999){
                      strcpy(ReturnMessage,"");
                      strcat(ReturnMessage,"403,Forbidden(Data duplicated)\n");
                      printf("//Duplicate Data found!\n");
                  }else{
                      bookList = addToBack(bookList, createBook(requestTitle, requestAuthor,requestLocation));
                       strcpy(ReturnMessage,"");
                      strcat(ReturnMessage,"202,ok\n");
                      time_t mytime = time(NULL);
                      char * time_str = ctime(&mytime);
                      time_str[strlen(time_str)-1] = '\0';
                      strcat(ReturnMessage,time_str);
                       strcat(ReturnMessage,"\n");
                       printf("//A book has been submitted.\n");
                 }
                 }
          }else if(strcmp(requestCommand, "GET") == 0){ // If user command is get
              strcpy(ReturnMessage,"");
              strcat(ReturnMessage,"204,ok\n");
              printf("SEARCH: %s, %s, %s\n",requestTitle, requestAuthor,requestLocation);
            if(strcmp(requestTitle, "") == 0 && strcmp(requestAuthor, "") == 0 && strcmp(requestLocation, "") == 0){
                  strcpy(ReturnMessage,"");
                  strcat(ReturnMessage,"401,Bad request(Check your syntax)\n");
                  printf("Syntax error, empty record!\n");
            }else if(strcmp((printBook(bookList,requestTitle, requestAuthor,requestLocation,0)),"") == 0){
                strcpy(ReturnMessage,"");
                 strcat(ReturnMessage,"208,NO CONTENT FOUND\n");
                 printf("//Search cotent is nothing\n");
              }else{
              strcat(ReturnMessage,printBook(bookList,requestTitle, requestAuthor,requestLocation,0));
            }

          }else if (strcmp(requestCommand, "REMOVE") == 0){ // If user command is remove
            if(strcmp(requestTitle, "") == 0 && strcmp(requestAuthor, "") == 0 && strcmp(requestLocation, "") == 0){
                  strcpy(ReturnMessage,"");
                  strcat(ReturnMessage,"401,Bad request(Check your syntax)\n");
                  printf("Syntax error, empty record!\n");
            }else{
              int index = searchList(bookList,requestTitle, requestAuthor,requestLocation);
              if(index == 9999){
                      strcpy(ReturnMessage,"");
                      strcat(ReturnMessage,"403,Forbidden(Nothing found to delete)\n");
                      printf("//Nothing found to delete!\n");
              }else{
                  
                  bookList = deleteNode(bookList,index);
                  strcpy(ReturnMessage,"");
                  strcat(ReturnMessage,"206,OK(BOOK DELETE)\n");
                 // strcat(ReturnMessage,index);
                  printf("Index %d\n",index );
              }
            }
          }
          strcpy(requestString,"");
         // printBook(bookList);
        }else{
            strcat(requestString,buf);
        }
        printf("server received %d bytes: %s", n, buf);
        
        /* 
         * write: echo the input string back to the client 
         */
        n = write(childfd, ReturnMessage, strlen(ReturnMessage));
        strcpy(ReturnMessage,"NOMESSAGE");
          if (n < 0) 
            error("ERROR writing to socket");
        }
close(childfd);

}


int main(int argc, char **argv) {
  int parentfd; /* parent socket */
  int childfd; /* child socket */
  int portno; /* port to listen on */
  int clientlen; /* byte size of client's address */
  struct sockaddr_in serveraddr; /* server's addr */
  struct sockaddr_in clientaddr; /* client addr */
  struct hostent *hostp; /* client host info */
  char buf[BUFSIZE]; /* message buffer */
  char *hostaddrp; /* dotted decimal host addr string */
  int optval; /* flag value for setsockopt */
  int n; /* message byte size */

  BookCatalogue * bookList = NULL;
  thread_handles = malloc(MAX_THREADS*sizeof(pthread_t)); 
  /* 
   * check command line arguments 
   */
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
  portno = atoi(argv[1]);

  /* 
   * socket: create the parent socket 
   */
  parentfd = socket(AF_INET, SOCK_STREAM, 0);
  if (parentfd < 0) 
    error("ERROR opening socket");

  /* setsockopt: Handy debugging trick that lets 
   * us rerun the server immediately after we kill it; 
   * otherwise we have to wait about 20 secs. 
   * Eliminates "ERROR on binding: Address already in use" error. 
   */
  optval = 1;
  setsockopt(parentfd, SOL_SOCKET, SO_REUSEADDR, 
	     (const void *)&optval , sizeof(int));

  /*
   * build the server's Internet address
   */
  bzero((char *) &serveraddr, sizeof(serveraddr));

  /* this is an Internet address */
  serveraddr.sin_family = AF_INET;

  /* let the system figure out our IP address */
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  /* this is the port we will listen on */
  serveraddr.sin_port = htons((unsigned short)portno);

  /* 
   * bind: associate the parent socket with a port 
   */
  if (bind(parentfd, (struct sockaddr *) &serveraddr, 
	   sizeof(serveraddr)) < 0) 
    error("ERROR on binding");

  /* 
   * listen: make this socket ready to accept connection requests 
   */
  if (listen(parentfd, 5) < 0) /* allow 5 requests to queue up */ 
    error("ERROR on listen");

  /* 
   * main loop: wait for a connection request, echo input line, 
   * then close connection.
   */

  BookCatalogue * books = NULL;
  clientlen = sizeof(clientaddr);
  while (1) {

    /* 
     * accept: wait for a connection request 
     */
    printf("im waiting\n");
    childfd = accept(parentfd, (struct sockaddr *) &clientaddr, &clientlen);
    if (childfd < 0) 
      error("ERROR on accepts");
    //printf("%d\n",childfd);


    hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr,     /* gethostbyaddr: determine who sent the message */
			  sizeof(clientaddr.sin_addr.s_addr), AF_INET);
    if (hostp == NULL)
      error("ERROR on gethostbyaddr");
    hostaddrp = inet_ntoa(clientaddr.sin_addr);
    if (hostaddrp == NULL)
      error("ERROR on inet_ntoa\n");
    printf("server established connection with %s (%s), threads: (%d)\n", hostp->h_name, hostaddrp, numThreads);
// Create thread
    pthread_create(&thread_handles[numThreads], NULL, server, &childfd);
    numThreads++;
     
  }
  

}
