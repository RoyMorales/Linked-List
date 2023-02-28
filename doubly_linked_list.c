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

    printf("Length of Linked List: %d\n", (*head)->length);

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
    int length = (*head)->length;

    // ToDo! 
    // Implement negative position
    // Verification of lenght list
    if (position < 0 || position > length) {        
        printf("Position Invalid. Cannot add element to Linked List\n");
        return;
    }
    // Identical to the addFirst Function
    if (position == 0) {
        printf("First Case - AddPos\n");
        addFirst(head, data);
    } 
    // Special Case -> Last Node
    // Node to be added is Header Node
    else if (position == length) {
        printf("Second Case - AddPos\n");
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
            printf("Normal Case -> First\n");  
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
            printf("Final\n");

        }
        // Use of Tail Pointer
        else {
            printf("Normal Case -> Second\n");
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

// Does Not Work
void deleteFirst(Header **head) {
    if (*head == NULL) {
        printf("Empty List - Cannot delete first element\n");
        return;
    }

    // Base Case - Only one Node 
    if ((*head)->chain_node->next == NULL && (*head)->chain_node->prev == NULL) {
        printf("First Case\n");

        free((*head)->chain_node);
        free((*head));

        printf("Pointer After Free: %d\n", *head);
    }
    // Base Case - Two Nodes in Linked List
    else if ((*head)->chain_node->next->next == NULL) {
        tail = (*head)->link;
        tail->link = tail;
        tail->length = 1;

        free((*head)->chain_node);
        free(*head);
    }



}






int main() {
    // Test Stuff
    Header *List_test = NULL;

    //addFirst(&List_addFirst, 69);
    //addFirst(&List_addFirst, 666);
    //addFirst(&List_addFirst, 420);
    //addFirst(&List_addFirst, 700);

    //printLinkedList(&List_addFirst);

    addLast(&List_test, 999);
    addLast(&List_test, 100);
    addLast(&List_test, 200);
    addLast(&List_test, 300);
    addLast(&List_test, 400);
    addLast(&List_test, 500);
    addLast(&List_test, 600);
    addPos(&List_test, 77777, 0);
    addPos(&List_test, 66666, 2);
    printf(" New Node Here\n");
    //addPos(&List_test, 321, 3);
    //printf(" New Node Here\n");


    //addPos(&List_test, 321, 7);

    printLinkedListReverse(&List_test);

}



