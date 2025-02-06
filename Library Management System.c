#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Book{
    char book_id[100];
    char title[100];
    char author[100];
    int quantity;
    int quantity_old;
    int available;
    struct Book *next;
}Book;

Book *Stack = NULL;
Book *Queue = NULL;
Book *Library = NULL;

Book *insertion_LL(Book *root,char BOOK_ID[100],char title[100],char author[100],int quantity){
        Book *extraNode = NULL,*temp=root,*finder=root;
        int checker = 0;
        while(finder!=NULL){
            if(strcmp(BOOK_ID,finder->book_id)==0){
                checker = 1;
                break;
            }
            finder = finder->next;
        }    
        if(checker==0){
            extraNode =(Book *) malloc(sizeof(Book));
            extraNode->next = NULL;
            strcpy(extraNode->book_id  , BOOK_ID);
            strcpy(extraNode->title    , title);
            strcpy(extraNode->author   , author);
            extraNode->quantity = quantity;
            extraNode->quantity_old = quantity;
            extraNode->available = 1;
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = extraNode;
        }
        else{
            finder->quantity += quantity;
            extraNode->available = 1;
        }
        return root;
}

void push(char BOOK_ID[100],int quantity){
    Book *newNode;

    newNode =(Book *) malloc(sizeof(Book));
    strcpy(newNode->book_id, BOOK_ID);

    newNode->next = Stack;
    Stack = newNode;

    printf("\n >> Book %s is pushed to stack\n", BOOK_ID);
    newNode->quantity_old = newNode->quantity;
    newNode->quantity -= quantity;
    if(newNode->quantity == 0){
        newNode->available = 0;
    }
    else{
        newNode->available = 1;
    }
}

void insert(char BOOK_ID[100],int quantity){
    Book *newNode;    
    newNode =(Book *) malloc(sizeof(Book));

    strcpy(newNode->book_id,BOOK_ID);
    newNode->next = Queue;
    Queue = newNode;

    newNode->quantity_old = newNode->quantity;
    newNode->quantity += quantity;
    newNode->available = 1;
}

void display_book_details(Book *root, char BOOK_ID[100]){
    printf("\n>> Title : %s\n",root->title);
    printf(">> Author : %s\n",root->author);
    printf(">> quentity available : %d ",root->quantity);
    if(root->available==0){
        printf("\nThus,this book is not available for you..\n");
    }
    else{
        printf("and so you can take this book..\n");
    }
}

Book *bookSearcher(Book *root,char BOOK_ID[100]){
    while(root!=NULL){
        if(strcmp(BOOK_ID,root->book_id)==0){
            return root;
        }
        root = root->next;
    } 
    return NULL;
}

void display_stack_and_queue(Book *LL,Book *lib){
    Book *root = LL,*temp=lib;
    int i=1;
    while(root!=NULL){
        temp = bookSearcher(lib,root->book_id);
        printf("\t%d. %s ( Quantity was : %d | Quantity is : %d )\n",i,temp->title,temp->quantity_old,temp->quantity);
        root = root->next;
        ++i;
    }
}

int main(){
    Book *Temp,*TempCheckerS,*TempCheckerQ,*TempCheckerD,*TempCheckerSQ,*BookShower;
    int Length = 0,choice,Quantity,Position;
    char bookId[100],Title[100],Author[100];
    printf(" :: Welcome to the LIBRARY MANAGEMENT SYSTEM :: \n");

    while(1){
        printf("\nEnter the choice from the below : \n1. Insert new book\n2. Checkout the book\n3. Return a book\n4. Display the book details and availability\n5. Display the list of the books currently checked out\nOther for the exit..\nEnter the choice number : ");
        scanf("%d",&choice);
        switch (choice){
        case 1 :
            printf("Enter the ID of the book : ");
            scanf(" %[^\n]%*c", bookId);
            printf("Enter the title of the book : ");
            scanf(" %[^\n]%*c", Title);
            printf("Enter the author of the book : ");
            scanf(" %[^\n]%*c", Author);
            printf("Enter the quantity of the book : ");
            scanf("%d",&Quantity);
            if(Quantity == 0){
                printf("\n >> You entered quantity = 0 so no book will inserted..\n");
            }
            else if(Quantity>0){
                if (Library == NULL) {  
                    Library = (Book *)malloc(sizeof(Book));
                    strcpy(Library->book_id, bookId);
                    strcpy(Library->title, Title);
                    strcpy(Library->author, Author);
                    Library->quantity = Quantity;
                    Library->quantity_old = Quantity;
                    Library->available = 1;
                    Library->next = NULL;
                    printf("\n >> First book successfully inserted.\n");
                }
                else{
                    Library = insertion_LL(Library,bookId,Title,Author,Quantity);
                    printf("\n >> Successfully insertion is done..\n");
                }
            }
            else{
                printf("\n >> You entered quantity < 0 so no book will inserted..\n");
            }
            break;
        
        case 2 :
            printf("Enter the ID of the book : ");
            scanf(" %[^\n]%*c", bookId);
            TempCheckerS = bookSearcher(Library,bookId);
            if(TempCheckerS==NULL){
                printf("\n >> This book is not found..\n");
            }
            else{
                printf("Enter the quantity of the book : ");
                scanf("%d",&Quantity);
                if (Quantity > TempCheckerS->quantity){
                    printf("\n >> That much quantity is not avialable of this book..\n");
                }
                else if(Quantity<=TempCheckerS->quantity){
                    push(bookId,Quantity);
                    TempCheckerS->quantity -= Quantity;
                    if(TempCheckerS->quantity == 0){
                        TempCheckerS->available = 0;
                    }
                    else{
                        TempCheckerS->available = 1;
                    }
                }
            }
            break;

        case 3 :
            printf("Enter the ID of the book : ");
            scanf(" %[^\n]%*c", bookId);

            TempCheckerQ = bookSearcher(Library,bookId);
            if(TempCheckerQ==NULL){
                printf("\n >> This book is not found..\n");
            }
            else{
                printf("Enter the number how much quantity you want to return : ");
                scanf("%d", &Quantity);
                insert(bookId,Quantity);   
                TempCheckerQ->quantity += Quantity;
                TempCheckerQ->available = 1;
                printf("\n >> %s is inserted into the queue..\n", bookId);
            }
            break;

        case 4 :
            printf("Enter the ID of the book : ");
            scanf(" %[^\n]%*c", bookId);
            TempCheckerD = bookSearcher(Library,bookId);
            if(TempCheckerD==NULL){
                printf("\n >> This book is not found..\n");
            }
            else{
                BookShower = bookSearcher(Library,bookId);
                display_book_details(BookShower,bookId);
            }
            break;

        case 5 :
            if(Stack==NULL && Queue==NULL){
                printf("\n >> No tranjection is occured till now..\n");
            }
            else if(Stack==NULL && Queue!=NULL){ 
                printf("\n >> No one is checked out the book..\n");
                printf("\n >> Displaying the list of the books which are currently returned : \n");
                display_stack_and_queue(Queue,Library);
            }
            else if(Queue==NULL && Stack!=NULL){
                printf("\n >> No one was returned the book..\n");
                printf("\n >> Displaying the list of the books which are currently checked out : \n");                    display_stack_and_queue(Stack,Library);
            }
            else{
                printf("\n >> Displaying the list of the books which are currently checked out : \n");                    display_stack_and_queue(Stack,Library);
                printf("\n >> Displaying the list of the books which are currently returned : \n");
                display_stack_and_queue(Queue,Library);
            }
            break;

        default:
            return 0;
        }
    }
    return 0;
}