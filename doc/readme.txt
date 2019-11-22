****************************************************
Yuhang Xu	student number: 0926193
CIS*3210	assignment: A1
Due date : Oct.11.2019
****************************************************

************
Compilation
************
make

./server 8080
./client 127.0.0.1 8080
***********************


*****************
explanation
*****************

You start your client and server, there will be a welcome screen
Type in commands SUBMIT,GET,REMOVE. YOU MUST TYPE THIS IN UPPERCASE

----------------------------------------------------------eg(IF you want to submit a book)

Client side:
>>>SUBMIT       
>>>TITLE THIS IS A BOOK
>>>AUTHOR ME
>>>LOCATION HEAVEN'S dooe
>>>                             //this is a enter key pressed
202,ok
Fri Oct 11 18:09:30 2019
>>>

server side:
server received 1 bytes: 
server received 7 bytes: SUBMIT
server received 21 bytes: TITLE THIS IS A BOOK
server received 10 bytes: AUTHOR ME
server received 23 bytes: LOCATION HEAVEN'S dooe


User message(Any fields that's not filled out would be put UNKNOWN):
SUBMIT
TITLE: THIS IS A BOOK
AUTHOR: ME
LOCATION: HEAVEN'S dooe
//A book has been submitted.



---------------------------------------------------------------eg(IF you want to GET a book)
client side:
>>>GET 
>>>AUTHOR ME
>>>
204,ok
title: THIS IS A BOOK
author: ME
location: HEAVEN'S dooe

server side:

SEARCH: , ME, 
Seach criteria-Title:0,Author:1,Location:0
Seach criteria-Title:0,Author:1,Location:0



*****************
limitation
*****************
1, if there is a missing field for example TITLE is not filled. It will be replace with UNKNOWN

2, if you call remove you must specify all fields, else it's not going to find the book.
eg.
client side:
>>>REMOVE
>>>TITLE THIS IS A BOOK
>>>AUTHOR ME
>>>LOCATION HEAVEN'S dooe
>>>
206,OK(BOOK DELETE)
