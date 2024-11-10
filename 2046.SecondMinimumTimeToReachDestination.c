#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct List* neighbors;
} Node;

typedef struct List {
    Node* node;
    int freq;
    struct List* next;
} List;

void enqueue(List** head, Node* node, int freq) {
    List* newElement = (List*)malloc(sizeof(List));
    if (!newElement) {
        exit(1);
    }
    newElement->node = node;
    newElement->freq = freq;
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

List* dequeue(List** head) {
    if (*head == NULL) {
        return NULL;
    }
    List* temp = *head;
    *head = (*head)->next;
    return temp;
}

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        exit(1);
    }
    newNode->value = value;
    newNode->neighbors = NULL;
    return newNode;
}

void addNeighbor(Node* src, Node* dest) {
    List* newNeighbor = (List*)malloc(sizeof(List));
    if (!newNeighbor) {
        exit(1);
    }
    newNeighbor->node = dest;
    newNeighbor->next = src->neighbors;
    src->neighbors = newNeighbor;
}

void addEdge(Node* nodes[], int srcValue, int destValue, int numNodes) {
    Node *src = NULL, *dest = NULL;
    for (int i = 1; i <= numNodes; i++) {
        if (nodes[i] && nodes[i]->value == srcValue) src = nodes[i];
        if (nodes[i] && nodes[i]->value == destValue) dest = nodes[i];
    }

    if (src && dest) {
        addNeighbor(src, dest);
        addNeighbor(dest, src);
    }
}

int secondMinimum(int n, int** edges, int edgesSize, int* edgesColSize, int time, int change) {
    Node* nodes[n + 1];
    for (int i = 1; i <= n; i++) {
        nodes[i] = createNode(i);
    }

    for (int i = 0; i < edgesSize; i++) {
        int src = edges[i][0];
        int dest = edges[i][1];
        addEdge(nodes, src, dest, n);
    }

    int dist1[n + 1], dist2[n + 1];
    for (int i = 1; i <= n; i++) {
        dist1[i] = -1;
        dist2[i] = -1;
    }
    dist1[1] = 0;

    List* queue = NULL;
    enqueue(&queue, nodes[1], 1);

    while (queue != NULL) {
        List* front = dequeue(&queue);
        Node* x = front->node;
        int freq = front->freq;
        int t = (freq == 1) ? dist1[x->value] : dist2[x->value];
        free(front);

        if ((t / change) % 2) {
            t = change * (t / change + 1) + time;
        } else {
            t += time;
        }

        List* neighbor = x->neighbors;
        while (neighbor != NULL) {
            Node* y = neighbor->node;
            if (dist1[y->value] == -1) {
                dist1[y->value] = t;
                enqueue(&queue, y, 1);
            } else if (dist2[y->value] == -1 && dist1[y->value] != t) {
                if (y->value == n) {
                    return t;
                }
                dist2[y->value] = t;
                enqueue(&queue, y, 2);
            }
            neighbor = neighbor->next;
        }
    }
    return 0;
}


int main(){
    int numNodes = 19;

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

    int time = 850;
    int change = 411;

    int result = secondMinimum(numNodes, edges, edgesSize, edgesColSize, time, change);
    printf("Second minimum path length: %d\n", result);


    return 0;
}