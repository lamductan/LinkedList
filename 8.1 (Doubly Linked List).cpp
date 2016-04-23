#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct DNode{
    int data;
    DNode *next;
    DNode *prev;
};

struct DList{
    DNode *head;
    DNode *tail;
};

void init(DList &l){
    l.head = l.tail = NULL;
}

bool isEmpty(DList l){
    return (l.head == NULL && l.tail == NULL);
}

//Searching Functions
DNode* findI(DList l, int i){ //Find member at i-position
    if (isEmpty(l)) return NULL;
    DNode *p = l.head;
    while (i && p->next != NULL)
        p = p->next, i--;
    if (i > 0) {
        printf("Number of members  of list is smaller than k.\n");
        return NULL;
    }
    return p;
}

DNode* findX(DList l, int x){ //Find member whose value is x
    for(DNode *p = l.head; p; p = p->next)
        if (p->data == x) return p;
    printf("No member has this value.\n");
    return NULL;
}

DNode* findTail(DList l){
    return l.tail;
}

//Add member function
DNode *make_DNode(int x){
    DNode *p = new DNode;
    p->data = x;
    p->next = p->prev = NULL;
    return p;
}

DNode* addHead(DList &l, int x){
    DNode *p = make_DNode(x);
    if (isEmpty(l)){
        l.head = l.tail = p;
    }
    else {
        l.head->prev = p;
        p->next = l.head;
        l.head = p;
    }
    return p;
}

DNode* addTail(DList &l, int x){
    if (isEmpty(l)) return(addHead(l, x));
    else {
        DNode *p = make_DNode(x);
        l.tail->next = p;
        p->prev = l.tail;
        l.tail = p;
        return p;
    }
}

DNode* insertBefore(DList &l, int x, int k){ //Add a member whose value is x before the k-position member
    if (k == 0) {
        return(addHead(l, x));
    }
    DNode *cur = l.head;
    while (k && cur->next != NULL)
        cur = cur->next, k--;
    if (k > 0) {
        printf("Number of members  of list is smaller than k.\n");
        return NULL;
    }
    DNode *p = new DNode;
    p->data = x;
    p->next = cur;
    p->prev = cur->prev;
    cur->prev->next = p;
    cur->next->prev = p;
    return p;
}

//Delete functions
void delHead(DList &l){
    if (isEmpty(l)) return;
    if (l.head->next == NULL){
        delete l.head;
        l.head = l.tail = NULL;
    }
    else {
        DNode *tmp = l.head;
        l.head = l.head->next;
        l.head->prev = NULL;
        delete tmp;
    }
}

void delTail(DList &l){
    if (isEmpty(l)) return;
    if (l.tail == l.head) delHead(l);
    else {
        DNode *tmp = l.tail;
        l.tail = l.tail->prev;
        l.tail->next = NULL;
        delete tmp;
    }
}

void delMid(DList &l, int k){ //Delete member at k-position
    if (isEmpty(l)) return;
    if (k == 0) delHead(l);
    else {
        DNode *p = l.head;
        while (k && p->next != NULL)
            p = p->next, k--;
        if (k > 0){
            printf("Number of members  of list is smaller than k.\n");
            return;
        }
        if (p->next == NULL) {
            delTail(l);
            return;
        }
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
    }
}

void delList(DList &l){
    while (l.head) delHead(l);
}

void printList(DList l){
    if (isEmpty(l)){
        printf("Empty list\n");
        return;
    }
    printf("Members of this Doubly Linked List:\n");
    if (l.head->next == NULL){
        printf("%d\n\n", l.head->data);
        return;
    }
    for(DNode *p = l.head; p; p = p->next)
        printf("%d\n", p->data);
    printf("\n");
    return;
}

int main(){
    DList l;
    char c[20];
    int k, x;
    DNode *p;

    init(l);

    printf("Add members to the first position:\n");
    do {
        printf("Enter an integer (enter # to exit): ");
        scanf("%s", &c);
        if (c[0] == '#') break;
        k = atoi(c);
        addHead(l, k);
    } while (c[0] != '#');

    printf("\nAdd members to the last position:\n");
     do {
        printf("Enter an integer (enter # to exit): ");
        scanf("%s", &c);
        if (c[0] == '#') break;
        k = atoi(c);
        addTail(l, k);
    } while (c[0] != '#');

    printf("\n");
    printList(l);

    printf("Insert a member before the k-position:\n");
    printf("Enter a position: ");
    scanf("%d", &k);
    printf("Enter a value: ");
    scanf("%d", &x);
    insertBefore(l, x, k);
    printList(l);
    system("pause");

    printf("\nFind the address of the k-position member:\n");
    printf("Enter a position: ");
    scanf("%d", &k);
    p = findI(l, k);
    if (p != NULL) printf("findI(l, %d) = %d\n", k, p);
    system("pause");

    printf("\nFind the address of the member whose value is k:\n");
    printf("Enter a value: ");
    scanf("%d", &x);
    p = findX(l, x);
    if (p != NULL) printf("findX(l, %d) = %d\n", x, p);
    system("pause");

    printf("\nFind the address of the last member:\n");
    printf("findTail(l) = %d\n", findTail(l));
    system("pause");

    printf("\nDelete the first member\n");
    delHead(l);
    printList(l);
    system("pause");

    printf("\nDelete the last member:\n");
    delTail(l);
    printList(l);
    system("pause");

    printf("\nDelete the k-position member:\n");
    printf("Enter a position: ");
    scanf("%d", &k);
    delMid(l, k);
    printList(l);
    system("pause");

    printf("\nDelete all the list:\n");
    delList(l);
    printList(l);
}
