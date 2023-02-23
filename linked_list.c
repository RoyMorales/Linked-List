// Implemantacion of a Linked List in C

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    // Any Data Type 
    int data;
    // Pointer to the next Node
    struct Node *link;
} Node;

struct Node *head = NULL;

void printList() {
    Node *temp = head;
    printf("\n--------------------------------\n");
    if (temp == NULL) {
        printf("\nCannot print empty list\n");
        printf("\n--------------------------------\n");
        return;
    }

    while (temp != NULL) {
        printf("Pointer to current Node: %d\n", temp);        
        printf("Data of current Node   : %d\n", temp->data);
        printf("Pointer to next Node   : %d\n", temp->link);        
        printf("--------------------------------\n");
        temp = temp->link;
    }
    free(temp);
}

void addLast(int data) {
    // Create Node and associated data
    Node *ptr = malloc(sizeof(Node));
    ptr->data = data;
    ptr->link = NULL;
    // Base Case -> No elements in Linked List
    if (head == NULL) {
        head = ptr;
    }
    // Search Linked List for the last element -> Node pointer = Null
    else {
        Node *ptr_prev = head;
        while (ptr_prev->link != NULL) {
            ptr_prev = ptr_prev->link;
        }
        ptr_prev = ptr->link;
    }
}

void addFirst(int data) {
    // Create Node and associated data
    Node *ptr = malloc(sizeof(Node));
    ptr->data = data;
    ptr->link = NULL;

    // Base Case -> No elements in Linked List
    if (head == NULL) {
        head = ptr;
    }
    else {
        ptr->link = head;
        head = ptr;
    }
}

void addPos(int data, int position) {
    // Create Node and associated data
    Node *ptr = malloc(sizeof(Node));
    ptr->data = data;
    ptr->link = NULL;

    // ToDo! 
    // Implement negative position
    // Verification of lenght list
    if (position < 0) {        
        printf("Position Invalid. Cannot add to element to Linked List");
        return;
    }

    // Identical to the addFirst Function
    if (position == 0) {
        addFirst(data);
    } 
    else {
        Node *ptr_next = head;
        Node *ptr_prev = NULL;
        for(int i = 0; i < position; i++) {
            ptr_prev = ptr_next;
            ptr_next = ptr_next->link;
        }
        ptr_prev->link = ptr;
        ptr->link = ptr_next->link; 
    }
}

void deleteFirst() {
    // Base Case -> No elements in Linked List
    if (head == NULL) {
        printf("Empty List - Cannot delete first element");
    }
    // Create a new node in order to fre the memory of the original head
    Node *ptr = head;
    head = ptr->link;
    free(ptr);
}

void deleteLast() {
    // Base Case -> No elements in Linked List
    if (head == NULL) {
        printf("Empty List - Cannot delete first element");
    }
    else if (head->link == NULL) {
        // Same as the deleteFrist -> Results in a Empty List
        Node *ptr = head;
        head = ptr->link;
        free(ptr); 
    }
    else {
        Node *ptr_next = head;
        Node *ptr_prev = NULL;
        while (ptr_next->link != NULL) {
            ptr_prev = ptr_next;
            ptr_next = ptr_next->link;
        }
        ptr_prev->link = NULL;
        free(ptr_next);
    }
}

// ToDo!
Node copyLinkedList() {
    Node *temp = malloc(sizeof(Node));
    temp->link = head;
    return *temp;
}


// ToDo!
Node cloneLinkedList() {
    Node *temp = malloc(sizeof(Node));
}



int main() {
    addLast(0);
    addLast(1);
    addLast(2);
    addLast(3);
    addLast(4);
    addLast(5);
    addPos(6,3);
    printList();
}
