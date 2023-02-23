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
}

void addLast(int data) {
    // Create Node and associated data
    Node *temp = malloc(sizeof(Node));
    temp->data = data;
    temp->link = NULL;

    // Base Case -> No elements in Linked List
    if (head == NULL) {
        head = temp;
    }
    // Search Linked List for the last element -> Node pointer = Null
    else {
        Node *ptr = head;
        while (ptr->link !=NULL)
        {
            ptr = ptr->link;
        }
        ptr->link = temp;
    }
}

void addFirst(int data) {
    // Create Node and associated data
    Node *temp = malloc(sizeof(Node));
    temp->data = data;
    temp->link = NULL;

    // Base Case -> No elements in Linked List
    if (head == NULL) {
        head = temp;
    }
    else {
        temp->link = head;
        head = temp;
    }
}

// ToDo!
void addPos(int data, int position) {
    Node *next_node = malloc(sizeof(Node));
    Node *prev_node = malloc(sizeof(Node));



    // Base Case -> No elements in Linked List
    if (head == NULL) {
        head = next_node;
        return;
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

Node shadowLinkedList() {
    Node *temp = malloc(sizeof(Node));
    temp->link = head;
    return *temp;
}



int main() {
    addLast(10);
    addLast(20);
    addLast(30);
    addFirst(40);
    printList();
    deleteLast();
    deleteLast();
    deleteLast();
    printList();

    Node copy_list = shadowLinkedList();
    printList();

}
