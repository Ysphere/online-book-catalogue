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
#include "linkList.h"


BookCatalogue * createBook(char * title, char * author, char * location ) { /*initialize */
    BookCatalogue * list = NULL;

    if(title != NULL && author != NULL && location != NULL ) { /*check condition*/
        list = malloc(sizeof (BookCatalogue) + 1);
        list->title = malloc(sizeof (BookCatalogue) * 50);
        strcpy(list->title, title);
        list->author = malloc(sizeof (BookCatalogue) * 50);
        strcpy(list->author, author);
        list->location = malloc(sizeof (BookCatalogue) * 50);
        strcpy(list->location, location);

        list->next=NULL;
    }else {
        printf("Failing creating book data\n");
    }
  return list;
}
BookCatalogue * getLastItem(BookCatalogue * theList) { // gets last item
    if (theList != NULL) {
        while (theList->next != NULL) {
            theList = theList->next;
        }
    }
    return theList;
}

BookCatalogue * getFirstItem(BookCatalogue * theList) { // gets the head
    return theList;
}


BookCatalogue * addToFront(BookCatalogue * theList, BookCatalogue * toBeAdded) { // adds a node to the head
        toBeAdded->next = theList;
        getFirstItem(theList);
        theList = toBeAdded;
        return theList;
}

BookCatalogue * addToBack(BookCatalogue * theList, BookCatalogue * toBeAdded) { // adds a node to the tail
    if (toBeAdded == NULL) {
        theList = addToFront(theList, toBeAdded);
    } else if (theList == NULL) {
        toBeAdded->next = theList;
        theList = toBeAdded;
    } else {
        BookCatalogue * back = getLastItem(theList);
        back->next = toBeAdded;
        toBeAdded->next = NULL;
    }
    return theList;
}

int searchList(BookCatalogue * root,char * title, char * author, char * location)
{
      if(strcmp(title, "") == 0 ){
          strcpy(title,"UNKNOWN");
      }if(strcmp(author, "") == 0 ){
          strcpy(author,"UNKNOWN");
      }if(strcmp(location, "") == 0 ){
        strcpy(location,"UNKNOWN");
      }
    int index = 0;
    while(root != NULL)
    {
        if(strcmp(root->title,title) == 0 && strcmp(root->author,author) == 0  && strcmp(root->location,location) == 0)
        {
            return index;
        }
        root = root->next;
        index++;
    }
    return 9999;
}

BookCatalogue* deleteNode(BookCatalogue *theList, int index) /*Remove a node*/
{
  int i=0;
  BookCatalogue *a, *b;
  a = theList;
  if(theList==NULL){
    return NULL;
  }
  else if(index == 0){
    theList = theList->next;
    free(a);
  }
  else{
    while(i!= index-1){
      a = a->next;
      i++;
    }
    b = a->next;
    a->next = b->next;

    free(b);
  }

  return theList;
}

const char * printBook(BookCatalogue * toPrint, char * title, char * author, char * location, int printAll ){
      int Tflag = 0; // is title a critiria we consider?
      int Aflag = 0; //is author a critiria we consider?
      int Lflag = 0; //is location a critiria we consider?
      char * str = malloc (sizeof (char) * 10000);
      if(strcmp(title, "") != 0)
        Tflag = 1;
      if(strcmp(author, "") != 0)
        Aflag = 1;
      if(strcmp(location, "") != 0)
        Lflag = 1;
      printf("Seach criteria-Title:%d,Author:%d,Location:%d\n",Tflag,Aflag,Lflag );
      if(printAll == 1){
        while (toPrint!=NULL) {
              strcat(str, "title: ");
              strcat(str, toPrint->title);
              strcat(str, "\n");
              strcat(str, "author: ");
              strcat(str, toPrint->author);
              strcat(str, "\n");
              strcat(str, "location: ");
              strcat(str, toPrint->location);
              strcat(str, "\n\n");
              //printf("title: %s \nauthor: %s \nlocation: %s \n\n",toPrint->title,toPrint->author,toPrint->location);
              toPrint = toPrint->next;
          }
      }else if(Tflag == 1 && Aflag == 1 && Lflag == 1){
            while (toPrint!=NULL) {
              if(strcmp(toPrint->title,title) == 0 && strcmp(toPrint->author,author) == 0  && strcmp(toPrint->location,location) == 0){
              //printf("title: %s \nauthor: %s \nlocation: %s \n\n",toPrint->title,toPrint->author,toPrint->location);
                  strcat(str, "title: ");
                  strcat(str, toPrint->title);
                  strcat(str, "\n");
                  strcat(str, "author: ");
                  strcat(str, toPrint->author);
                  strcat(str, "\n");
                  strcat(str, "location: ");
                  strcat(str, toPrint->location);
                  strcat(str, "\n\n");
              }
              toPrint = toPrint->next;
          }
      }else if(Tflag == 1 && Aflag == 0 && Lflag == 0){
            while (toPrint!=NULL) {
              if(strcmp(toPrint->title,title) == 0){
                  strcat(str, "title: ");
                  strcat(str, toPrint->title);
                  strcat(str, "\n");
                  strcat(str, "author: ");
                  strcat(str, toPrint->author);
                  strcat(str, "\n");
                  strcat(str, "location: ");
                  strcat(str, toPrint->location);
                  strcat(str, "\n\n");
              }
              //printf("title: %s \nauthor: %s \nlocation: %s \n\n",toPrint->title,toPrint->author,toPrint->location);
              toPrint = toPrint->next;
          }
      }else if(Tflag == 0 && Aflag == 1 && Lflag == 0){
            while (toPrint!=NULL) {
              
              if(strcmp(toPrint->author,author) == 0){
             // printf("title: %s \nauthor: %s \nlocation: %s \n\n",toPrint->title,toPrint->author,toPrint->location);
                 strcat(str, "title: ");
                  strcat(str, toPrint->title);
                  strcat(str, "\n");
                  strcat(str, "author: ");
                  strcat(str, toPrint->author);
                  strcat(str, "\n");
                  strcat(str, "location: ");
                  strcat(str, toPrint->location);
                  strcat(str, "\n\n");
              }
            
              toPrint = toPrint->next;
            }
          
      }else if(Tflag == 0 && Aflag == 0 && Lflag == 1){
            while (toPrint!=NULL) {
              if(strcmp(toPrint->location,location) == 0){
             // printf("title: %s \nauthor: %s \nlocation: %s \n\n",toPrint->title,toPrint->author,toPrint->location);
                 strcat(str, "title: ");
                  strcat(str, toPrint->title);
                  strcat(str, "\n");
                  strcat(str, "author: ");
                  strcat(str, toPrint->author);
                  strcat(str, "\n");
                  strcat(str, "location: ");
                  strcat(str, toPrint->location);
                  strcat(str, "\n\n");
              }
            
              toPrint = toPrint->next;
              }
          
      }else if(Tflag == 1 && Aflag == 1 && Lflag == 0){
            while (toPrint!=NULL) {
              if(strcmp(toPrint->title,title) == 0 && strcmp(toPrint->author,author) == 0){
             // printf("title: %s \nauthor: %s \nlocation: %s \n\n",toPrint->title,toPrint->author,toPrint->location);
                  strcat(str, "title: ");
                  strcat(str, toPrint->title);
                  strcat(str, "\n");
                  strcat(str, "author: ");
                  strcat(str, toPrint->author);
                  strcat(str, "\n");
                  strcat(str, "location: ");
                  strcat(str, toPrint->location);
                  strcat(str, "\n\n");
              }            
           
              toPrint = toPrint->next;
          }
      }else if(Tflag == 1 && Aflag == 0 && Lflag == 1){
            while (toPrint!=NULL) {
              if(strcmp(toPrint->title,title) == 0 && strcmp(toPrint->location,location) == 0){
              //printf("title: %s \nauthor: %s \nlocation: %s \n\n",toPrint->title,toPrint->author,toPrint->location);
                  strcat(str, "title: ");
                  strcat(str, toPrint->title);
                  strcat(str, "\n");
                  strcat(str, "author: ");
                  strcat(str, toPrint->author);
                  strcat(str, "\n");
                  strcat(str, "location: ");
                  strcat(str, toPrint->location);
                  strcat(str, "\n\n");
              }
              
              toPrint = toPrint->next;
          }
      }else if(Tflag == 0 && Aflag == 1 && Lflag == 1){
            while (toPrint!=NULL) {
              if(strcmp(toPrint->author,author) == 0 && strcmp(toPrint->location,location) == 0){
             // printf("title: %s \nauthor: %s \nlocation: %s \n\n",toPrint->title,toPrint->author,toPrint->location);
                  strcat(str, "title: ");
                  strcat(str, toPrint->title);
                  strcat(str, "\n");
                  strcat(str, "author: ");
                  strcat(str, toPrint->author);
                  strcat(str, "\n");
                  strcat(str, "location: ");
                  strcat(str, toPrint->location);
                  strcat(str, "\n\n");
              }
            
              toPrint = toPrint->next;
            }
          }
      

      return str;
}