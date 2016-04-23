#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

struct CNode{
    int data;
    CNode* next;
};

struct CList{
    CNode* head;
};

void init(CList &l){
    l.head = NULL;
}

bool isEmpty(CList l){
    return (l.head == NULL);
}

//Searching Functions
CNode* findI(CList l, int i){
    CNode* p = l.head;
    while (i && p->next != l.head)
        p = p->next, i--;
    if (i > 0) {
        printf("The number of members of list is smaller than k.\n");
        return NULL;
    }
    return p;
}

CNode* findX(CList l, int x){
    if (isEmpty(l)) return NULL;
    CNode* p = l.head;
    if (x == l.head->data) return l.head;
    for(p = l.head->next; p != l.head; p = p->next)
        if (p->data == x) return p;

    printf("No member has this value.\n");
    return NULL;
}

CNode* findTail(CList l){
    CNode* p = l.head;
    do {
        p = p->next;
    } while (p->next != l.head);
    return p;
}

//Add Member Functions
CNode *addHead(CList &l, int x){
    CNode* p = new CNode;
    p->data = x;
    if (isEmpty(l)){
        l.head = p;
        l.head->next = p;
    }
    CNode *tail = findTail(l);
    p->next = l.head;
    l.head = p;
    tail->next = p;
    return p;
}

CNode *addTail(CList &l, int x){
    if (isEmpty(l)) return(addHead(l, x));
    CNode* pTail = findTail(l);
    CNode* p = new CNode;
    p->data = x;
    p->next = l.head;
    pTail->next = p;
    return p;
}

CNode *insertBefore(CList &l, int x, int k){ //Add a member whose value is x before the k-position
    if (k == 0) return(addHead(l, x));
    else {
        CNode* cur = l.head, *prev = cur;
        while (k && cur->next != l.head)
            prev = cur, cur = cur->next, k--;
        if (k > 0) {
            printf("The number of members of list is smaller than k.\n");
            return NULL;
        }
        CNode* p = new CNode;
        p->data = x;
        p->next = cur;
        prev->next = p;
        return p;
    }
}

//Print list to debug
void printList(CList l){
    if (isEmpty(l)) {
        printf("Empty list\n");
        return;
    }
    printf("Members of Circular Linked List:\n");
    printf("%d\n", l.head->data);
    if (l.head->next == l.head) return;
    for(CNode* p = l.head->next; p != l.head; p = p->next)
        printf("%d\n", p->data);
    printf("\n");
}

//Delete Functions
void delHead(CList &l){
    if (isEmpty(l)) return;
    if ((l.head != NULL) && (l.head->next == l.head)){
        delete l.head->next;
        delete l.head;
        l.head = NULL;
    }
    else {
        CNode* tmp = l.head;
        CNode* tail = findTail(l);
        l.head = l.head->next;
        tail->next = l.head;
        delete tmp;
    }
}

void delTail(CList &l){
    if (isEmpty(l)) return;
    if (l.head->next == l.head) delHead(l);
    else {
        CNode *tail = l.head, *prev = tail;
        while (tail->next != l.head)
            prev = tail, tail = tail->next;
        prev->next = l.head;
        delete tail;
    }
}

void delMid(CList &l, int k) { //Delete the member at the k-position
    if (isEmpty(l)) return;
    if (k == 0) delHead(l);
    CNode* cur = l.head, *prev = cur;
    while (k && cur->next != l.head)
        prev = cur, cur = cur->next, k--;
    if (k > 0) {
        printf("The number of members of list is smaller than k.\n");
        return;
    }
    prev->next = cur->next;
    delete cur;
}

void delList(CList &l){
    while (l.head) delHead(l);
}

int main(){
    CList l;
    char c[20];
    int k, x;
    CNode *p;

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
