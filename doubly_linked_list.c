// Implemantaion of a Doubly Linked List
// With a head and tail pointer

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    // Any Data Type -> ToDo!
    int data;
    // Pointer to the next Node
    struct Node *next;
    // Pointer to the previous Node
    struct Node *prev;
} Node;

typedef struct Header {
    // Frist Node of the Linked list with a special Node with information about
    // the length of the list.
    int length;
    // Super Set of the original Node
    struct Node *chain_node;
} Header;

// Two pointers to the linked List
// One on the head and the other on the tail

struct Header *head = NULL;
struct Header *tail = NULL;

void printLinkedList(Header **head) {
    printf("Head Next: %d\n", (*head)->chain_node);
    printf("Head Node Next: %d\n", ((*head)->chain_node->next));
    Node *temp = (*head)->chain_node->next;
    printf("Head: %d", temp);

    if (temp == NULL) {
        printf("\n--------------------------------\n");
        printf("\n   Cannot print empty list\n");
        printf("\n--------------------------------\n");
        return;
    }

    while (temp != NULL) {
        printf("\n--------------------------------\n");
        printf("Pointer to current Node: %d\n", temp);        
        printf("Data of current Node   : %d\n", temp->data);
        printf("Pointer to next Node   : %d\n", temp->next);        
        printf("--------------------------------\n");
        temp = temp->next;
    }
    free(temp);


}

void printLinkedListReverse(Header **tail) {
    printf("ToDo!");
}

void addFrist(Header **head, int data) {
    Node *ptr = malloc(sizeof(Node));
}

void addLast(Header **tail, int data) {
    Header *ptr = malloc(sizeof(Header));


}


int main() {
    Header *head = malloc(sizeof(Header));
    Node *node_1 = malloc(sizeof(Node));
    Node *node_2 = malloc(sizeof(Node));
    Node *node_3 = malloc(sizeof(Node));
    Header *tail = malloc(sizeof(Header));
    printf("ok\n\n");

    head->length = 5;
    head->chain_node->data = 0;
    head->chain_node->prev = NULL;
    head->chain_node->next = node_1;

    node_1->data = 1;
    node_1->prev = head->chain_node;
    node_1->next = node_2;

    printf("Node I want: %d\n", node_1);

    node_2->data = 2;
    node_2->prev = node_1;
    node_2->next = node_3;

    node_3->data = 4;
    node_3->prev = node_2;
    node_3->next = tail->chain_node;

    tail->length = 5;
    tail->chain_node->data = 5;
    tail->chain_node->prev = node_3; 
    tail->chain_node->next = NULL; 



    printLinkedList(&head);

}






