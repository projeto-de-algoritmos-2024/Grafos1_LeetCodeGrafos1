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

    printPaths(newPath);

    if (*pathList == NULL || (*pathList)->size > newPath->size) {
        newPath->next = *pathList;
        *pathList = newPath;
    } else {
        Path* currentPath = *pathList;
        while (currentPath->next != NULL && currentPath->next->size < newPath->size) {
            currentPath = currentPath->next;
        }

        newPath->next = currentPath->next;
        currentPath->next = newPath;
    }
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
    Path *paths=exploreAllPaths(nodes[0],nodes[n-1],n,nodes);
    int currentTime=0;

    int size;


    if(paths->next==NULL){
        size=paths->size+1;
    }else{
        size=paths->size;

        while (paths->next!=NULL && paths->next->size==size){
            paths=paths->next;
        }
        

        if(paths->next==NULL){
            size+=1;
        }
        else{
            size=paths->next->size-1;
        }
    }
    

    for(int i=0;i<size;i++){
        if((currentTime/change)%2==0){
            currentTime+=time;
        }else{
            currentTime+=change-(currentTime%change);
            i--;
        }
    }
    return(currentTime);
}


int main(){
    int numNodes = 19;

    // Definindo as arestas conforme os dados fornecidos
    int edgesSize = 72;
    int* edges[] = {
        (int[]){1, 2}, (int[]){2, 3}, (int[]){1, 4}, (int[]){2, 5}, (int[]){2, 6}, (int[]){2, 7},
        (int[]){7, 8}, (int[]){8, 9}, (int[]){7, 10}, (int[]){9, 11}, (int[]){11, 12}, (int[]){1, 13},
        (int[]){3, 14}, (int[]){13, 15}, (int[]){14, 16}, (int[]){8, 17}, (int[]){4, 18}, (int[]){11, 19},
        (int[]){17, 11}, (int[]){3, 19}, (int[]){19, 7}, (int[]){12, 5}, (int[]){8, 1}, (int[]){15, 7},
        (int[]){19, 6}, (int[]){18, 9}, (int[]){6, 8}, (int[]){14, 19}, (int[]){13, 18}, (int[]){15, 2},
        (int[]){13, 12}, (int[]){1, 5}, (int[]){16, 18}, (int[]){3, 16}, (int[]){6, 1}, (int[]){18, 14},
        (int[]){12, 1}, (int[]){16, 6}, (int[]){13, 11}, (int[]){1, 14}, (int[]){16, 13}, (int[]){11, 16},
        (int[]){4, 15}, (int[]){17, 5}, (int[]){5, 9}, (int[]){12, 2}, (int[]){4, 10}, (int[]){9, 16},
        (int[]){17, 9}, (int[]){3, 5}, (int[]){10, 2}, (int[]){18, 1}, (int[]){15, 18}, (int[]){12, 17},
        (int[]){10, 6}, (int[]){10, 18}, (int[]){19, 12}, (int[]){12, 15}, (int[]){19, 13}, (int[]){1, 19},
        (int[]){9, 14}, (int[]){4, 3}, (int[]){17, 13}, (int[]){9, 3}, (int[]){17, 10}, (int[]){19, 10},
        (int[]){5, 4}, (int[]){5, 7}, (int[]){14, 17}, (int[]){1, 10}, (int[]){4, 11}, (int[]){6, 4},
        (int[]){5, 10}, (int[]){7, 14}, (int[]){8, 14}, (int[]){18, 17}, (int[]){15, 10}, (int[]){11, 8},
        (int[]){14, 11}, (int[]){7, 3}, (int[]){5, 18}, (int[]){13, 8}, (int[]){4, 12}, (int[]){11, 3},
        (int[]){5, 15}, (int[]){15, 9}, (int[]){8, 10}, (int[]){13, 3}, (int[]){17, 1}, (int[]){10, 11},
        (int[]){15, 11}, (int[]){19, 2}, (int[]){1, 3}, (int[]){7, 4}, (int[]){18, 11}, (int[]){2, 14},
        (int[]){9, 1}, (int[]){17, 15}, (int[]){7, 13}, (int[]){12, 16}, (int[]){12, 8}, (int[]){6, 12},
        (int[]){9, 6}, (int[]){2, 17}, (int[]){15, 6}, (int[]){16, 2}, (int[]){12, 7}, (int[]){7, 9},
        (int[]){8, 4}
    };

    int edgesColSize[] = {
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2
    };

    // Defina os valores de `time` e `change` conforme os dados fornecidos
    int time = 850;
    int change = 411;

    // Chamar a função `secondMinimum` com os novos dados
    int result = secondMinimum(numNodes, edges, edgesSize, edgesColSize, time, change);
    printf("Second minimum path length: %d\n", result);


    return 0;
}