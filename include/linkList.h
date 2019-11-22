/*
Name:Yuhang Xu
Cis*3210
ID:0926193
Oct.11.2019
A1
*/

#ifndef __list_H__
#define __list_H__


struct BookCatalogue{ /*Book catalogue strcut*/
  char * title;
  char * author;
  char * location;
  struct BookCatalogue * next;
};
typedef struct BookCatalogue BookCatalogue;

/*create info of a book*/
BookCatalogue * createBook(char * title, char * author, char * location );
/*add to end of the list*/
BookCatalogue * addToBack(BookCatalogue * theList, BookCatalogue * toBeAdded); // adds a node to the tail
/*get the first item of the list*/
BookCatalogue * getFirstItem(BookCatalogue * theList); // gets the head
/*add to the front of the list*/
BookCatalogue * addToFront(BookCatalogue * theList, BookCatalogue * toBeAdded);// adds a node to the head
/*get the last item of the list*/
BookCatalogue * getLastItem(BookCatalogue * theList); // gets last item
/*search the list*/
int searchList(BookCatalogue * root,char * title, char * author, char * location);
/*remove head of the list*/
BookCatalogue* deleteNode(BookCatalogue *theList, int index); /*Remove a node*/

const char * printBook(BookCatalogue * toPrint, char * title, char * author, char * location, int printAll );






#endif