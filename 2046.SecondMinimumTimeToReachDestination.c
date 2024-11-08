#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct List* neighbors;
} Node;

typedef struct List {
    Node* node;             
    struct List* next;  
} List;


Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->neighbors = NULL;
    return newNode;
}


void addNeighbor(Node* src, Node* dest) {
    List* newNeighbor = (List*)malloc(sizeof(List));
    newNeighbor->node = dest;
    newNeighbor->next = NULL;

    if (src->neighbors == NULL) {
        src->neighbors = newNeighbor;
    } else {
        List* current = src->neighbors;
        List* previous = NULL;

        while (current != NULL && current->node->value < dest->value) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) {
            newNeighbor->next = src->neighbors;
            src->neighbors = newNeighbor;
        } else {
            previous->next = newNeighbor;
            newNeighbor->next = current;
        }
    }
}



int areConnected(Node* src, Node* dest) {
    List* current = src->neighbors;
    while (current != NULL) {
        if (current->node == dest) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}


void addEdge(Node* nodes[], int srcValue, int destValue, int numNodes) {
    Node *src = NULL, *dest = NULL;
    
    for (int i = 0; i < numNodes; i++) {
        if (nodes[i]->value == srcValue) src = nodes[i];
        if (nodes[i]->value == destValue) dest = nodes[i];
    }

    if (src == NULL || dest == NULL) {
        return;
    }

    if (!areConnected(src, dest)) {
        addNeighbor(src, dest);
        addNeighbor(dest, src);
    }
}

void printGraph(Node* nodes[], int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        Node* node = nodes[i];
        printf("%d: ", node->value);
        List* neighbor = node->neighbors;
        while (neighbor) {
            printf("%d -> ", neighbor->node->value);
            neighbor = neighbor->next;
        }
        printf("NULL\n");
    }
}


void freeGraph(Node* nodes[], int numNodes) {
    for (int i = 0; i < numNodes; i++) {
        List* neighbor = nodes[i]->neighbors;
        while (neighbor) {
            List* temp = neighbor;
            neighbor = neighbor->next;
            free(temp);
        }
        free(nodes[i]);
    }
}



int secondMinimum(int n, int** edges, int edgesSize, int* edgesColSize, int time, int change) {
 return 0;   
}


int main(){
    int numNodes = 5;
    Node* nodes[numNodes];

    for (int i = 0; i < numNodes; i++) {
        nodes[i] = createNode(i + 1);
    }

    addEdge(nodes, 1, 2, numNodes);
    addEdge(nodes, 1, 3, numNodes);
    addEdge(nodes, 1, 4, numNodes);
    addEdge(nodes, 2, 1, numNodes);
    addEdge(nodes, 3, 4, numNodes);
    addEdge(nodes, 4, 5, numNodes);

    printGraph(nodes, numNodes);

    freeGraph(nodes, numNodes);

    return 0;
}