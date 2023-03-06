// Implementation of a binary tree

typedef struct Node
{
    int data;

    struct Node *left;
    struct Node *right;
} Node;

struct Node *root = NULL;

Node *createNode(int data) {
    Node * new_node = malloc(sizeof(Node));

    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}



