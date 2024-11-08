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

typedef struct Path {
    int size;
    List* nodes;
    struct Path* next;
} Path;


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


void addPath(Path** pathList, int* path, int pathLength, Node* nodes[]) {
    Path* newPath = (Path*)malloc(sizeof(Path));
    newPath->size = pathLength;
    newPath->nodes = NULL;
    newPath->next = NULL;

    List* current = NULL;
    for (int i = 0; i < pathLength; i++) {
        List* newNode = (List*)malloc(sizeof(List));
        newNode->node = nodes[path[i] - 1];
        newNode->next = NULL;

        if (newPath->nodes == NULL) {
            newPath->nodes = newNode;
        } else {
            current->next = newNode;
        }
        current = newNode;
    }

    newPath->next = *pathList;
    *pathList = newPath;
}

void findAllPaths(Node* currentNode, Node* destination, int* path, int pathLength, int* visited, Path** pathList, Node* nodes[]) {
    visited[currentNode->value - 1] = 1;
    path[pathLength] = currentNode->value;
    pathLength++;

    if (currentNode == destination) {
        addPath(pathList, path, pathLength, nodes);
    } else {
        List* neighbor = currentNode->neighbors;
        while (neighbor != NULL) {
            if (!visited[neighbor->node->value - 1]) {
                findAllPaths(neighbor->node, destination, path, pathLength, visited, pathList, nodes);
            }
            neighbor = neighbor->next;
        }
    }

    visited[currentNode->value - 1] = 0;
}

Path* exploreAllPaths(Node* startNode, Node* endNode, int numNodes, Node* nodes[]) {
    Path* pathList = NULL;

    int* path = (int*)malloc(numNodes * sizeof(int));
    int* visited = (int*)calloc(numNodes, sizeof(int));

    findAllPaths(startNode, endNode, path, 0, visited, &pathList, nodes);

    free(path);
    free(visited);

    return pathList;
}

void printPaths(Path* pathList) {
    Path* path = pathList;
    while (path != NULL) {
        printf("Path of size %d: ", path->size);
        List* node = path->nodes;
        while (node != NULL) {
            printf("%d -> ", node->node->value);
            node = node->next;
        }
        printf("NULL\n");
        path = path->next;
    }
}


int secondMinimum(int n, int** edges, int edgesSize, int* edgesColSize, int time, int change) {
    Node* nodes[n];
    for (int i = 0; i < n; i++) {
        nodes[i] = createNode(i + 1);
    }

    for (int i = 0; i < edgesSize; i++) {
        int src = edges[i][0];
        int dest = edges[i][1];
        addEdge(nodes, src, dest, n);
    }
    printGraph(nodes,n);
    Path *paths=exploreAllPaths(nodes[0],nodes[n-1],n,nodes);
    printPaths(paths);

    if(paths->next!=NULL){
        return(paths->next->size);
    }else{
        return(paths->size+2);
    }
}


int main(){
    int numNodes = 5;
    
    int edgesSize = 5;
    int* edges[] = {
        (int[]){1, 2},
        (int[]){1, 3},
        (int[]){1, 4},
        (int[]){3, 4},
        (int[]){4, 5}
    };
    int edgesColSize[] = {2, 2, 2, 2, 2};

    int result = secondMinimum(numNodes, edges, edgesSize, edgesColSize, 0, 0);
    printf("Second minimum path length: %d\n", result);

    return 0;
}