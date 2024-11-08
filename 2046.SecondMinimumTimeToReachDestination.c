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

void enqueue(List** head, Node* node) {
    List* newElement = (List*)malloc(sizeof(List));
    newElement->node = node;
    newElement->next = NULL;

    if (*head == NULL) {
        *head = newElement;
    } else {
        List* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newElement;
    }
}

Node* dequeue(List** head) {
    if (*head == NULL) {
        return NULL;
    }
    List* temp = *head;
    Node* node = temp->node;
    *head = (*head)->next;
    free(temp);
    return node;
}

int isVisited(int* visited, int value, int numNodes) {
    return visited[value - 1];
}

void markVisited(int* visited, int value, int numNodes) {
    visited[value - 1] = 1;
}

void breadthFirstSearch(Node* startNode, int numNodes) {
    int* visited = (int*)calloc(numNodes, sizeof(int));  
    List* queue = NULL;

    enqueue(&queue, startNode);   
    markVisited(visited, startNode->value, numNodes); 

    while (queue != NULL) {
        Node* currentNode = dequeue(&queue);
        printf("%d ", currentNode->value);

        List* neighbor = currentNode->neighbors;
        while (neighbor != NULL) {
            if (!isVisited(visited, neighbor->node->value, numNodes)) {
                enqueue(&queue, neighbor->node);
                markVisited(visited, neighbor->node->value, numNodes);
            }
            neighbor = neighbor->next;
        }
    }
    printf("\n");

    free(visited);
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



void findAllPaths(Node* currentNode, Node* destination, int* path, int pathLength, int* visited) {
    visited[currentNode->value - 1] = 1;
    path[pathLength] = currentNode->value;
    pathLength++;

    if (currentNode == destination) {
        printf("Path: ");
        for (int i = 0; i < pathLength; i++) {
            printf("%d ", path[i]);
        }
        printf("\n");
    } else {
        List* neighbor = currentNode->neighbors;
        while (neighbor != NULL) {
            if (!visited[neighbor->node->value - 1]) {
                findAllPaths(neighbor->node, destination, path, pathLength, visited);
            }
            neighbor = neighbor->next;
        }
    }

    visited[currentNode->value - 1] = 0;
}

void exploreAllPaths(Node* startNode, Node* endNode, int numNodes) {
    int* path = (int*)malloc(numNodes * sizeof(int));   
    int* visited = (int*)calloc(numNodes, sizeof(int)); 

    findAllPaths(startNode, endNode, path, 0, visited);

    free(path);
    free(visited);
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

    exploreAllPaths(nodes[0], nodes[4], numNodes);

    
    freeGraph(nodes, numNodes);

    return 0;
}