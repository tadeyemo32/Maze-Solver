// bfs.h
#ifndef BFS_H
#define BFS_H

#include "grid.h"
#include "raylib.h"
#include <stdbool.h>

// Proper typedef for Node
typedef struct Node {
    Vector2 pos;
    struct Node* next;
    
} Node;

// Global queue state (if used globally)
extern Node* head;
extern Node* GOAL;
extern int queueCount;

// Function declarations
Node* createNode(Vector2 pos);
bool enQueue(Node* node);
bool deQueue(void);
bool isQueueEmpty(void);
void resetQueue();
bool bfs();

#endif // BFS_H
