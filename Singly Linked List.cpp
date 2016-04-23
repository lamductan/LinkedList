#include <stdio.h>
#include <malloc.h>

struct SNode{
    int data;
    SNode* next;
};

struct SList{
    SNode* head;
};

void init(SList &l){
    l.head = NULL;
}

bool isEmpty(SList l){
    return (l.head == NULL);
}

//Searching Functions
SNode* findI(SList l, int i){
    SNode* p = l.head;
    while (i && p != NULL)
        p = p->next, i--;
    return p;
}

SNode* findX(SList l, int x){
    if (isEmpty(l)) return NULL;
    SNode* p = l.head;
    for(p = l.head; p; p = p->next)
        if (p->data == x) return p;
    return NULL;
}

SNode* findTail(SList l){
    SNode* p = l.head;
    while (p->next != NULL)
        p = p->next;
    return p;
}

//Add Member Functions
SNode* addHead(SList &l, int x){
    SNode* p = new SNode;
    p->data = x;
    p->next = l.head;
    l.head = p;
    return p;
}

SNode* addTail(SList l, int x){
    if (isEmpty(l)) return(addHead(l, x));
    SNode* pTail = findTail(l);
    SNode* p = new SNode;
    p->data = x;
    p->next = NULL;
    pTail->next = p;
    return p;
}

SNode* insertBefore(SList l, int x, int k){ //Add a member whose value is x before the k-position
    if (k == 0) return(addHead(l, x));
    else {
        SNode* cur = l.head, *prev = cur;
        while (k && cur->next != NULL)
            prev = cur, cur = cur->next, k--;
        if (k > 0) return NULL;
        SNode* p = new SNode;
        p->data = x;
        p->next = cur;
        prev->next = p;
        return p;
    }
}

//Print list to debug
void printList(SList l){
    if (isEmpty(l)) {
        printf("Empty list\n");
        return;
    }
    printf("Members of Linked List:\n");
    for(SNode* p = l.head; p; p = p->next)
        printf("%d\n", p->data);
    printf("\n");
}

//Delete Functions
void delHead(SList &l){
    if (l.head->next == NULL){
        delete l.head;
        l.head = NULL;
    }
    else {
        SNode* tmp = l.head;
        l.head = l.head->next;
        delete tmp;
    }
}

void delTail(SList &l){
    if (isEmpty(l)) return;
    if (l.head->next == NULL) delHead(l);
    else {
        SNode *tail = l.head, *prev = tail;
        while (tail->next != NULL)
            prev = tail, tail = tail->next;
        prev->next = NULL;
        delete tail;
    }
}

void delMid(SList &l, int k) { //Delete the member at the k-position
    if (isEmpty(l)) return;
    SNode* cur = l.head, *prev = cur;
    while (k && cur->next != NULL)
        prev = cur, cur = cur->next, k--;
    if (k > 0) return;
    prev->next = cur->next;
    delete cur;
}

void delList(SList &l){
    while (l.head) delHead(l);
}

int main(){
    SList l;
    int k;
    int n = 0;
    init(l);

    do {
        printf("Enter an integer (enter 0 to exit): ");
        scanf("%d", &k);
        if (k == 0) break;
        addHead(l, k);
        ++n;
    } while (k != 0);

    do {
        printf("Enter an integer (enter 0 to exit): ");
        scanf("%d", &k);
        if (k == 0) break;
        addTail(l, k);
        ++n;
    } while (k != 0);

    //insertBefore(l, 10000, 3);
    printList(l);

    delHead(l);
    delTail(l);
    printList(l);
    delMid(l, 5);
    printList(l);

    delList(l);
    printList(l);
}
