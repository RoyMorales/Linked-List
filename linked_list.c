// Implemantacion of a Linked List in C

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Node {
    // Any Data Type -> ToDo!
    int data;
    // Pointer to the next Node
    struct Node *link;
} Node;


struct Node *head = NULL;


void printList(Node **head) {
    Node *temp = *head;
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
        printf("Pointer to next Node   : %d\n", temp->link);        
        printf("--------------------------------\n");
        temp = temp->link;
    }
    free(temp);
}


void addFirst(Node **head, int data) {
    // Create Node and associated data
    Node *ptr = malloc(sizeof(Node));
    ptr->data = data;
    ptr->link = *head;

    // Change Head pointer to new Node
    *head = ptr;
}


void addLast(Node **head, int data) {
    // Create Node and associated data
    Node *ptr = malloc(sizeof(Node));
    ptr->data = data;
    ptr->link = NULL;

    // Base Case -> No elements in Linked List
    if (*head == NULL) {
        *head = ptr;
    }
    else {
        // Search Linked List for the last element -> Node pointer = Null
        Node *ptr_prev = *head;
        while (ptr_prev->link != NULL) {
            ptr_prev = ptr_prev->link;
        }
        ptr_prev->link = ptr;
    }
}


void addPos(Node **head, int data, int position) {
    // Create Node and associated data
    Node *ptr = malloc(sizeof(Node));
    ptr->data = data;
    ptr->link = NULL;

    // ToDo! 
    // Implement negative position
    // Verification of lenght list
    if (position < 0) {        
        printf("Position Invalid. Cannot add element to Linked List\n");
        return;
    }

    // Identical to the addFirst Function
    if (position == 0) {
        addFirst(head, data);
    } 
    else {
        Node *ptr_next = *head;
        Node *ptr_prev = NULL;
        for(int i = 0; i < position; i++) {
            ptr_prev = ptr_next;
            ptr_next = ptr_next->link;
        }
        ptr_prev->link = ptr;
        ptr->link = ptr_next; 
    }
}


void replacePos(Node **head, int data, int position) {
    // Create Node and associated data
    Node *ptr = malloc(sizeof(Node));
    ptr->data = data;
    ptr->link = NULL;

    // ToDo! 
    // Implement negative position
    // Verification of lenght list
    if (position < 0) {        
        printf("Position Invalid. Cannot replace element of Linked List\n");
        return;
    }

    if (position == 0) {
        Node *ptr_next = *head;        
        ptr->link = ptr_next->link;
        *head = ptr;    
        free(ptr_next);
    }
    else {
        Node *ptr_next = *head;
        Node *ptr_prev = NULL;
        for(int i = 0; i < position; i++) {
            ptr_prev = ptr_next;
            ptr_next = ptr_next->link;
        }
        ptr_prev->link = ptr;
        ptr->link = ptr_next->link; 
        free(ptr_next);
    }
}


void deleteFirst(Node **head) {
    // Base Case -> No elements in Linked List
    if (*head == NULL) {
        printf("Empty List - Cannot delete first element\n");
    }
    // Create a new node in order to free the memory of the original head
    else {
        Node *ptr = *head;
        *head = ptr->link;
        free(ptr);
    }
}


void deleteLast(Node **head) {
    // Base Case -> No elements in Linked List
    if (*head == NULL) {
        printf("Empty List - Cannot delete last element\n");
    }
    else if ((*head)->link == NULL) {
        // Same as the deleteFrist -> Results in a Empty List
        Node *ptr = *head;
        *head = ptr->link;
        free(ptr); 
    }
    else {
        Node *ptr_next = *head;
        Node *ptr_prev = NULL;
        while (ptr_next->link != NULL) {
            ptr_prev = ptr_next;
            ptr_next = ptr_next->link;
        }
        ptr_prev->link = NULL;
        free(ptr_next);
    }
}


void deleteAll(Node **head) {
    while(*head != NULL) {
        deleteFirst(head);
    }
}


void deletePos(Node **head, int position) {
    // ToDo! 
    // Implement negative position
    // Verification of lenght list
    if (position < 0) {        
            printf("Position Invalid. Cannot delete element of Linked List\n");
            return;
    }

    // Identical to the deleteFirst Function
    if (position == 0) {
        deleteFirst(head);
        return;
    } 
    else {
        Node *ptr_next = *head;
        Node *ptr_prev = NULL;
        for(int i = 0; i < position; i++) {
            ptr_prev = ptr_next;
            ptr_next = ptr_next->link;
        }
        ptr_prev->link = ptr_next->link;
        free(ptr_next);
    }
}


int searchFristLinkedList (Node **head, int data) {
    Node *ptr = *head;
    
    int index = 0;
    while (ptr->data != data){
        if (ptr->link == NULL) {
            printf("Data not found.\n");
            return -1;
        }
        ptr = ptr->link;
        index++;
    }
    return index;
}


int countElementLinkedList (Node **head, int data) {
    Node *temp = *head;
    
    int index = 0;
    while (true) {
        if (temp->data == data) {
            index++;
        }
        if (temp->link == NULL) {
            break;
        } 
        else {
        temp = temp->link;
        }
    }
    return index;
}

int lengthLinkedList(Node **head) {
    Node *temp = *head;

    if (*head == NULL) {
        return 0;
    }

    int index = 1;
    while(temp->link != NULL) {
        index++;
        temp = temp->link;
    }
    return index;
}


Node *copyLinkedList(Node **head) {
    Node *shadow = *head;
    return shadow;
}


Node *cloneLinkedList(Node **head) {
    Node *clone = NULL;
    Node *tail = NULL;
    Node *temp = *head;

    while (temp != NULL) {
        // Special case for the first Node
        if (clone == NULL) {
            clone = (Node *)malloc(sizeof(Node));
            clone->data = temp->data;
            clone->link = NULL;
            tail = clone;
        }
        else {
            tail->link = (Node *)malloc(sizeof(Node));
            tail = tail->link;
            tail->data = temp->data;
            tail->link = NULL;
        }
        temp = temp->link;
    }
    free(temp);
    return clone;
}


int main () {
    printf("\n\n ---------------------------------------- \n\n");
    Node *List_1 = NULL;
    addLast(&List_1, 10);
    addLast(&List_1, 20);
    addLast(&List_1, 30);
    addLast(&List_1, 40);
    addLast(&List_1, 50);
    printList(&List_1);
    int lenght_list = lengthLinkedList(&List_1);
    printf("Lenght: %d", lenght_list);

    printf("\n\n ---------------------------------------- \n\n");
    Node *clone = cloneLinkedList(&List_1);
    deleteLast(&clone);
    deleteLast(&clone);
    int len_list_2 = lengthLinkedList(&clone);
    printf("Len: %d", len_list_2);

    printList(&clone);
    printf("\n\n ---------------------------------------- \n\n");
}
