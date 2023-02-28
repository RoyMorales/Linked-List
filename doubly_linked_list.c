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



// ToDo! -> Error with  tail - (*head)->link can point to nothing if the list is empty 
void printLinkedList(Header **head) {
    Node *temp = (*head)->chain_node;
    int length = (*head)->length;

    if (temp == NULL) {
        printf("----------------------------------------------\n");
        printf("           Cannot print empty list\n");
        printf("----------------------------------------------\n");
        return;
    }

    tail = (*head)->link;
    printf("\n\n>>>>>>>>>>>>>>>>>>> Header <<<<<<<<<<<<<<<<<<<\n\n");
    printf("Pointer to Head: %d\n", (*head)->link->link);
    printf("Pointer to Tail: %d\n", (*head)->link);
    printf("Lenght of List : %d\n", (*head)->length);

    int counter = 0;
    while (temp != NULL) {
        counter++;
        if (counter == length) {
            printf(">>>>>>>>>>>>>>>>>>> Tail <<<<<<<<<<<<<<<<<<<<\n\n");
            printf("Pointer to Head: %d\n", tail->link);
            printf("Pointer to Tail: %d\n", tail->link->link);
            printf("Lenght of List : %d\n", tail->length);
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
        (*head)->link->length = counter;
    }

    printf("Length of Linked List: %d", (*head)->length);

    // Redundant +/- free of memory: Pointer = Null -> Null
    free(temp);
}


void printLinkedListReverse (Header **head) {
    if (*head == NULL) {
        printf("----------------------------------------------\n");
        printf("           Cannot print empty list\n");
        printf("----------------------------------------------\n");
        return;
    }

    // Temp -> Tail
    Node *temp = (*head)->link->chain_node;
}

// Something Wrong with prev pointer -> Frist case ?? Second Case
// Third Case seen right
void addFirst(Header **head, int data) {
    // Reserve Memory to struct Header and substruct Node
    Header *new_head = malloc(sizeof(Header));
    new_head->chain_node = malloc(sizeof(Node));
    new_head->chain_node->data = data;
    new_head->chain_node->prev = NULL;

    // Base Case -> Empty Linked List
    if (*head == NULL) {
        printf("\n\nFirst Case\n\n");

        // Associate all proprieties to the new head
        new_head->chain_node->next = NULL;
        new_head->length = 1;

        // Node is both head and tail
        // Link points to itself
        new_head->link = new_head;
    }
    // Base Case -> One element in Linked List
    else if ((*head)->chain_node->next == NULL) {
        printf("\n\nSecond Case\n\n");

        // Associate all proprieties of old head to the new head
        new_head->chain_node->next = (*head)->chain_node;
        new_head->length = 2;

        // Associate all proprieties of old head to the new head
        // Head now is the tail
        (*head)->chain_node->prev = new_head->chain_node;
        (*head)->length = 2;

        // Node is Head and next Node is Tail
        // Link points from itself to the next Node
        new_head->link = (*head);
        (*head)->link = new_head;
    }
    // Remmaing Cases -> length > 2
    else {
        printf("\n\nThird Case\n\n");

        // Convert head to a chain node
        Node *node_head = malloc(sizeof(Node));
        node_head->data = (*head)->chain_node->data;
        node_head->next = (*head)->chain_node->next;
        node_head->prev = new_head->chain_node;

        // Associate all proprieties of old head to the new head
        new_head->chain_node->next = node_head;
        new_head->link = (*head)->link;
        new_head->length = (*head)->length + 1;
        new_head->link->length = (*head)->length + 1;

        free((*head)->chain_node);
        free(*head);
    }
    printf("Head Pointer: %d\n", new_head);
    printf("Tail Pointer: %d\n", new_head->link);
    printf("Chain Node inside Tail: %d\n", new_head->link->chain_node);

    *head = new_head;
}



void addLast(Header **head, int data) {
    // New Tail
    Header *new_tail = malloc(sizeof(Header));
    new_tail->chain_node = malloc(sizeof(Node));
    new_tail->chain_node->data = data;
    new_tail->chain_node->next = NULL;


    // Base Case -> Empty Linked List
    if (*head == NULL) {
        printf("Frist Case\n");

        // Associate all proprieties to the new head
        new_tail->chain_node->prev = NULL;
        new_tail->length = 1;

        // Node is both head and tail
        // Link points to itself
        new_tail->link = new_tail;
        *head = new_tail->link;
    }
    // Base Case -> One Node
    else if ((*head)->link->chain_node->prev == NULL) {
        printf("Second Case\n");

        // Associate all proprietes of old tail to the new tail
        new_tail->chain_node->prev = (*head)->chain_node;
        new_tail->length = 2;

        // Associate all proprieties of old tail to the new head
        // Old tail now is the head
        (*head)->chain_node->next = new_tail->chain_node;
        (*head)->length = 2;

        // Node is Tail and prev Node is Tail
        // Link points from itself to the prev Node
        new_tail->link = *head;
        (*head)->link = new_tail;
    }
    else {
        printf("Third Case\n");

        tail = (*head)->link;

        // Convertion of old tail to a chain node
        Node *node_tail = malloc(sizeof(Node));
        node_tail->next = new_tail->chain_node;
        node_tail->prev = tail->chain_node->prev;
        node_tail->data = tail->chain_node->data;

        // Associate all proprietes to new tail and head update
        new_tail->chain_node->prev = node_tail;
        new_tail->length = tail->length + 1;
        new_tail->link = *head;
        (*head)->link = new_tail;
        (*head)->length += 1;

        // Free old header Node
        free(tail);
        free(tail->chain_node);
    
        *head = new_tail->link;
    }
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


    Header *List_test = NULL;

    //addFirst(&List_test, 69);
    //addFirst(&List_test, 420);
    //addFirst(&List_test, 13);
    //addFirst(&List_test, 7);
    
    
    addLast(&List_test, 123);
    addLast(&List_test, 999);
    addLast(&List_test, 666);
    
    
    printLinkedList(&List_test);
}


