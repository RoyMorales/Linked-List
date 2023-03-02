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

//--------------------------------------------------------------------
//                              Print
//--------------------------------------------------------------------

void printLinkedList(Header **head) {
    if (*head == NULL) {
        printf("----------------------------------------------\n");
        printf("           Cannot print empty list\n");
        printf("----------------------------------------------\n");
        return;
    }

    Node *temp = (*head)->chain_node;
    int length = (*head)->length;
    tail = (*head)->link;

    printf("\n\n>>>>>>>>>>>>>>>>>>> Head <<<<<<<<<<<<<<<<<<<\n");
    printf("Pointer to Head: %d\n", (*head)->link->link);
    printf("Pointer to Tail: %d\n", (*head)->link);
    printf("Lenght of List : %d\n", (*head)->length);

    int counter = 0;
    while (temp != NULL) {
        counter++;
        if (counter == length) {
            printf("\n\n>>>>>>>>>>>>>>>>>>> Tail <<<<<<<<<<<<<<<<<<<<\n");
            printf("Pointer to Head: %d\n", tail->link);
            printf("Pointer to Tail: %d\n", tail->link->link);
            printf("Lenght of List : %d\n", tail->length);
        }

        printf("********************** %d ********************\n", counter);
        printf("Pointer to current Node: %d\n", temp);  
        printf("Data of current Node   : %d\n", temp->data);
        printf("---------------------------------------------\n");
        printf("Pointer to prev Node   : %d\n", temp->prev);
        printf("Pointer to next Node   : %d\n", temp->next);        
        printf("*********************************************\n\n");

        if (counter == 1 || counter == length) {
            printf(">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<\n\n\n\n");
        }

        temp = temp->next;
    }

    printf("Length of Linked List : %d\n", (*head)->length);
    printf("Counter of Linked List: %d\n", counter);

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

    Node *temp = tail->chain_node;
    int length = tail->length;
    tail = (*head)->link;

    printf("\n\n>>>>>>>>>>>>>>>>>>> Tail <<<<<<<<<<<<<<<<<<<<\n");
    printf("Pointer to Head: %d\n", tail->link);
    printf("Pointer to Tail: %d\n", tail->link->link);
    printf("Lenght of List : %d\n", tail->length);

    int counter = length + 1;
    while(temp != NULL) {
        counter--;
        if (counter == 1) {
            printf("\n\n>>>>>>>>>>>>>>>>>>> Head <<<<<<<<<<<<<<<<<<<\n");
            printf("Pointer to Head: %d\n", (*head)->link->link);
            printf("Pointer to Tail: %d\n", (*head)->link);
            printf("Lenght of List : %d\n", (*head)->length);

        }

        printf("********************** %d ********************\n", counter);
        printf("Pointer to current Node: %d\n", temp);  
        printf("Data of current Node   : %d\n", temp->data);
        printf("---------------------------------------------\n");
        printf("Pointer to prev Node   : %d\n", temp->prev);
        printf("Pointer to next Node   : %d\n", temp->next);        
        printf("*********************************************\n\n");


        if (counter == 1 || counter == tail->length) {
            printf(">>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<\n\n\n\n");
        }
        
        temp = temp->prev;  
    }

    printf("Length of Linked List: %d\n", (*head)->length);
    printf("Counter of Linked List: %d\n", counter);

    // Redundant +/- free of memory: Pointer = Null -> Null
    free(temp);
}

//--------------------------------------------------------------------
//                              Insertion
//--------------------------------------------------------------------

void addFirst(Header **head, int data) {
    // Reserve Memory to struct Header and substruct Node
    Header *new_head = malloc(sizeof(Header));
    new_head->chain_node = malloc(sizeof(Node));
    new_head->chain_node->data = data;
    new_head->chain_node->prev = NULL;

    // Base Case -> Empty Linked List
    if (*head == NULL) {
        // Associate all proprieties to the new head
        new_head->chain_node->next = NULL;
        new_head->length = 1;

        // Node is both head and tail
        // Link points to itself
        new_head->link = new_head;
    }
    // Base Case -> One element in Linked List
    else if ((*head)->chain_node->next == NULL) {
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
        tail = (*head)->link;

        // Convert head to a chain node
        Node *node_head = malloc(sizeof(Node));
        node_head->data = (*head)->chain_node->data;
        node_head->next = (*head)->chain_node->next;
        node_head->prev = new_head->chain_node;
        node_head->next->prev = node_head;

        // Associate all proprieties of old head to the new head
        new_head->chain_node->next = node_head;
        new_head->length = (*head)->length + 1;
        new_head->link = tail;
        tail->link = new_head;
        tail->length = (*head)->length + 1;

        free((*head)->chain_node);
        free(*head);
    }
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
        tail = (*head)->link;

        // Convertion of old tail to a chain node
        Node *node_tail = malloc(sizeof(Node));
        node_tail->next = new_tail->chain_node;
        node_tail->data = tail->chain_node->data;
        node_tail->prev = tail->chain_node->prev;
        node_tail->prev->next = node_tail; 

        // Associate all proprietes to new tail and head update
        new_tail->chain_node->prev = node_tail;
        new_tail->length = tail->length + 1;
        new_tail->link = *head;
        (*head)->link = new_tail;
        (*head)->length += 1;

        // Free old header Node
        free(tail->chain_node);
        free(tail);
    
        *head = new_tail->link;
    }
}


void addPos(Header **head, int data, int position) {
    // Identical to the addFirst Function
    if (position == 0 || *head == NULL) {
        addFirst(head, data);
        return;
    } 

    int length = (*head)->length;
    // ToDo! 
    // Implement negative position
    // Verification of lenght list
    if (position < 0 || position > length) {        
        printf("Position Invalid. Cannot add element to Linked List\n");
        return;
    }
    // Special Case -> Last Node
    // Node to be added is Header Node
    else if (position == length) {
        addLast(head, data);
    } 
    // Special Case 
    // Last Node needs to be transformed to Header
    else {
        tail = (*head)->link;

        // Creation of Node chain
        Node *new_node = malloc(sizeof(Node));
        new_node->data = data;
        
        // Efficienty Stuff
        // Use of Head Pointer
        if ((length - position) > position) {
            Node *ptr_next = (*head)->chain_node;
            Node *ptr_prev = NULL;

            for(int i = 0; i < position; i++) {
                ptr_prev = ptr_next;
                ptr_next = ptr_next->next;
            }

            // Update new Node
            new_node->next = ptr_next;
            new_node->prev = ptr_prev;

            // Update neighbors Nodes
            ptr_next->prev = new_node;
            ptr_prev->next = new_node;
        }
        // Use of Tail Pointer
        else {
            Node *ptr_next = NULL;
            Node *ptr_prev = tail->chain_node;

            int path = length - position;

            for(int i = 0; i < path; i++) {
                ptr_next = ptr_prev;
                ptr_prev = ptr_prev->prev;
            }
            // Update new Node
            new_node->next = ptr_next;
            new_node->prev = ptr_prev;

            // Update neighbors Nodes
            ptr_next->prev = new_node;
            ptr_prev->next = new_node;
        }   

        // Update Head and Tail Header
        tail->length += 1;
        (*head)->length += 1;
    }
}


//--------------------------------------------------------------------
//                              Deletion
//--------------------------------------------------------------------

void deleteFirst(Header **head) {
    if (*head == NULL) {
        printf("Empty List - Cannot delete first element\n");
        return;
    }
    // Base Case - Only one Node 
    if ((*head)->chain_node->next == NULL && (*head)->chain_node->prev == NULL) {
        free((*head)->chain_node);
        free(*head);

        *head = NULL;
    }
    // Base Case - Two Nodes in Linked List
    else if ((*head)->chain_node->next->next == NULL) {
        tail = (*head)->link;

        tail->length = 1;
        tail->link = tail;
        tail->chain_node->prev = NULL;

        // Free Original Head
        free((*head)->chain_node);
        free(*head);

        // Tail is now head
        *head = tail;
    }
    else {        
        // Convertion of node chain to Header
        Header *new_head = malloc(sizeof(Header));
        new_head->chain_node = malloc(sizeof(Node));

        new_head->link = (*head)->link;
        new_head->link->length -= 1;

        new_head->length = (*head)->length - 1;
        new_head->link->link = new_head;

        new_head->chain_node->data = (*head)->chain_node->next->data;
        new_head->chain_node->prev = NULL;
        new_head->chain_node->next = (*head)->chain_node->next->next;

        // Change Pointer next of chain node to new head
        new_head->chain_node->next->prev = new_head->chain_node;

        // Free Original Head
        free((*head)->chain_node);
        free(*head);

        // Free converted node
        free((*head)->chain_node->next);

        *head = new_head;
    }
}


void deleteLast(Header **head) {
    if (*head == NULL) {
        printf("Empty List - Cannot delete last element\n");
        return;
    }

    tail = (*head)->link;
    if (tail->chain_node->prev == NULL && tail->chain_node->next == NULL) {
        free(tail->chain_node);
        free(tail);

        *head = NULL;
        tail = NULL;
    }
    else if (tail->chain_node->prev->prev == NULL) {
        (*head)->length = 1;
        (*head)->link = *head;
        (*head)->chain_node->next = NULL;

        free(tail->chain_node);
        free(tail);

        tail = *head;
    }
    else {
        // Convertion of node chain to Header
        Header *new_tail = malloc(sizeof(Header));
        new_tail->chain_node = malloc(sizeof(Node));

        // Change Stuff
        (*head)->length -= 1;
        (*head)->link = new_tail;
        
        new_tail->length = tail->length - 1;
        new_tail->link = (*head);

        new_tail->chain_node->data = tail->chain_node->prev->data;
        new_tail->chain_node->prev = tail->chain_node->prev->prev;
        new_tail->chain_node->next = NULL;

        // Change Pointer next of chain node to new head
        new_tail->chain_node->prev->next = new_tail->chain_node;

        // Free Original Tail
        free(tail->chain_node);
        free(tail);

        // Free converted node
        free(tail->chain_node->prev);

        tail = new_tail;
    }
}


void deletePos(Header **head, int position) {
    if (*head == NULL) {
        printf("Empty List - Cannot delete element.\n");
        return;
    }
    if (position < 0 || position >= (*head)->length) {
        printf("Position Invalid. Cannot delete element.\n");
        return;
    }

    if (position == 0) {
        deleteFirst(head);
    }
    else if (position == (((*head)->length) - 1)) {
        deleteLast(head);
    }
    else {
        tail = (*head)->link;
        
        // Efficienty Stuff
        // Use of Head Pointer
        if (((*head)->length - position) > position) {
            Node *ptr_next = (*head)->chain_node;
            Node *ptr_prev = NULL;

            for(int i = 0; i < position; i++) {
                ptr_prev = ptr_next;
                ptr_next = ptr_next->next;
            }

            // Update neighbors Nodes
            ptr_next->next->prev = ptr_prev;
            ptr_prev->next = ptr_next->next;

            free(ptr_next);
        }
        // Use of Tail Pointer
        else {
            Node *ptr_next = NULL;
            Node *ptr_prev = tail->chain_node;

            int path = tail->length - position;

            for(int i = 0; i < path; i++) {
                ptr_next = ptr_prev;
                ptr_prev = ptr_prev->prev;
            }

            // Update neighbors Nodes
            ptr_next->next->prev = ptr_prev;
            ptr_prev->next = ptr_next->next;
        }   

        // Update Head and Tail Header
        tail->length -= 1;
        (*head)->length -= 1;
    }
}


void deleteAll(Header **head) {
    if (*head == NULL) {
        printf("Empty List - Cannot delete element.\n");
        return;
    }

    while(*head != NULL) {    
        deleteFirst(head);
    }
}


//--------------------------------------------------------------------
//                              Replacement
//--------------------------------------------------------------------

void replaceFirst(Header **head, int data) {
    if (*head == NULL) {
        printf("Cannot replace non existing Node");
        return;
    } 

    deleteFirst(head);
    addFirst(head, data);
}


void replaceLast(Header **head, int data) {
    if (*head == NULL) {
        printf("Cannot replace non existing Node");
        return;
    } 

    deleteLast(head);
    addLast(head, data);

}

// To Do!
void replacePos(Header **head, int data, int position) {
    if (*head == NULL) {
        printf("Cannot replace non existing Node");
        return;
    } 

    int lenght = (*head)->length;
    if (position < 0 || position > lenght) {
        printf("Position Invalid. Cannot add element to Linked List\n");
        return;
    }
}


//--------------------------------------------------------------------
//                            Search and Counting
//--------------------------------------------------------------------




//--------------------------------------------------------------------
//                             Copy and Clonning
//--------------------------------------------------------------------





int main() {
    // Test Stuff
    Header *List_test = NULL;

    addLast(&List_test, 111);
    addLast(&List_test, 123);
    addLast(&List_test, 321);

    replaceFirst(&List_test, 69);
    replaceLast(&List_test, 420);

    printLinkedList(&List_test);  

}



