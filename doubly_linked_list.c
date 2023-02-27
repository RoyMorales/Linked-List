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
    // Frist and last Node of the Linked List with a special Node with information about
    // the length of the list and pointer to the other Header.
    int length;
    struct Header *link;
    // SuperSet of the original Node
    struct Node *chain_node;
} Header;

struct Header *head = NULL;
struct Header *tail = NULL;

void printLinkedList(Header **head) {
    Node *temp = (*head)->chain_node;
    int length = (*head)->length;

    if (temp == NULL) {
        printf("----------------------------------------------\n");
        printf("\n        Cannot print empty list\n");
        printf("----------------------------------------------\n");
        return;
    }

    printf("\n\n>>>>>>>>>>>>>>>>>>> Header <<<<<<<<<<<<<<<<<<<\n\n");

    int counter = 0;
    while (temp != NULL) {
        counter++;
        if (counter == length) {
            printf(">>>>>>>>>>>>>>>>>>> Tail <<<<<<<<<<<<<<<<<<<<\n\n");
        }

        printf("**********************************************\n");
        printf("Pointer to current Node: %d\n", temp);  
        printf("Data of current Node   : %d\n", temp->data);
        printf("----------------------------------------------\n");
        printf("Pointer to prev Node   : %d\n", temp->prev);
        printf("Pointer to next Node   : %d\n", temp->next);        
        printf("----------------------------------------------\n\n");
        temp = temp->next;
    }
    // Verify if the lenght of linked list is corrected
    if (counter != (*head)->length) {
        printf("Lenght of the list was corrected.\n");
        (*head)->length = counter;
    }

    printf("Length of Linked List: %d", (*head)->length);

    // Redundant free of memory: Pointer = Null -> Null
    // Clean code
    free(temp);
}


void addFirst(Header **head, int data) {
    // Reserve Memory to struct Header and substruct Node
    Header *new_head = malloc(sizeof(Header));
    new_head->chain_node = malloc(sizeof(Node));

    // Base Case -> Empty Linked List
    if ((*head)->chain_node->next == NULL) {
        // Associate all proprieties of old head to the new head
        new_head->chain_node->data = data;
        new_head->chain_node->next = NULL;
        new_head->chain_node->prev = NULL;
        new_head->length = 1;

        // Node is both head and tail
        // Link points to itself
        new_head->link = new_head;
        *head = new_head;
    }
    // Base Case -> One element in Linked List
    else if ((*head)->chain_node->next->next == NULL) {
        // Associate all proprieties of old head to the new head
        new_head->chain_node->data = data;
        new_head->chain_node->next = (*head)->chain_node;
        new_head->chain_node->prev = NULL;
        new_head->length = 2;

        // Node is Head and next Node is Tail
        // Link points from itself to the next Node
        new_head->link = (*head)->link;
        (*head)->link = new_head;
    }
    // Remmaing Cases -> length > 2
    else {
        // Convert head to a chain node
        Node *node_head = malloc(sizeof(Node));
        node_head->data = (*head)->chain_node->data;
        node_head->next = (*head)->chain_node->next;
        node_head->prev = new_head->chain_node;

        // Associate all proprieties of old head to the new head
        new_head->chain_node->data = data;
        new_head->chain_node->next = (*head)->chain_node;
        new_head->chain_node->prev = NULL;
        new_head->link = (*head)->link;
        new_head->length = (*head)->length + 1;
    }

    *head = new_head;
}



int main() {

    /*
    // Test Stuff
    Header *head = malloc(sizeof(Header));
    head->chain_node = malloc(sizeof(Node));
    Node *node = malloc(sizeof(Node));
    Header *tail = malloc(sizeof(Header));
    tail->chain_node = malloc(sizeof(Node));


    head->length = 3;
    head->link = tail;
    head->chain_node->data = 20;
    head->chain_node->prev = NULL;
    head->chain_node->next = node;

    node->data = 7;
    node->prev = head->chain_node;
    node->next = tail->chain_node;

    tail->length = 3;
    tail->link = head;
    tail->chain_node->data = 420;
    tail->chain_node->prev = node;
    tail->chain_node->next = NULL;

    addFirst(&head, 13);
    printLinkedList(&head);
    */

    // Test Stuff
    Header *List = NULL;
    List->chain_node = NULL;
    //addFirst(&List, 69);
    printLinkedList(&List);
}


