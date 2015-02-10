#include "myheader.h"

typedef struct node *nodePtr;
typedef struct node node;

struct node {
    int data;
    nodePtr next;
};

void printLinkedList(nodePtr currentNode) {
    printf("Node data: %d\n", currentNode->data);
    
    if (currentNode->next != NULL)
        printLinkedList(currentNode->next);
}

void insertNodeAndKeepSorted(nodePtr currentNode, int newData) {
    
    if (currentNode->next == NULL || newData < currentNode->next->data) {
        // insert node here
        nodePtr newNode = malloc(sizeof(node));
        newNode->data = newData;
        newNode->next = NULL;
        
        if (currentNode->next != NULL) {
            newNode->next = currentNode->next;
        }
        currentNode->next = newNode;
    }
    else {
        insertNodeAndKeepSorted(currentNode->next, newData);
    }
}

void deleteNodeFromList(nodePtr currentNode, int data) {
    if (currentNode->next != NULL) {
        if (currentNode->next->data == data) {
            // delete next node
            nodePtr delNode = currentNode->next;
            currentNode->next = NULL;
            if (delNode->next != NULL) {
                currentNode->next = delNode->next;
            }
            free(delNode);
        }
        else {
            deleteNodeFromList(currentNode->next, data);
        }
    } 
}

void deleteLinkedList(nodePtr root) {
    if (root->next->next == NULL) {
        printf("first del node w/ data = %d\n", root->next->data);
        free(root->next);
        root->next = NULL;
        return;
    } else {
        deleteLinkedList(root->next);
        printf("second del node w/ data = %d\n", root->next->data);
        free(root->next);
        root->next = NULL;
    }
}

int main(int argc, const char *argv[]) {

    nodePtr root = malloc(sizeof(node));
    root->next = NULL;

    insertNodeAndKeepSorted(root, 42);
    insertNodeAndKeepSorted(root, 69);
    insertNodeAndKeepSorted(root, 55);
    insertNodeAndKeepSorted(root, -5);
    insertNodeAndKeepSorted(root, 45);

    printf("\n- - Printing linked list - -\n");
    printLinkedList(root);

    //deleteNodeFromList(root, 55);

    deleteLinkedList(root->next);

    printf("\n- - Printing linked list - -\n");
    printLinkedList(root);

    printf("\n-------- END ---------\n"); 
    return EXIT_SUCCESS;
}

