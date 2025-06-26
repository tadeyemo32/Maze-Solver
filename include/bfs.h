#ifndef BFS_H
#define BFS_H

#include "grid.h"
#include "raylib.h"
#include <stdbool.h>

// Define Node structure for BFS
typedef struct {
    Vector2 pos;
} Node;

// Queue operations
void enQueue(Node node);    
Node deQueue(void);           // Remove and return a node from the queue
bool isQueueEmpty(void);      // Check if queue is empty
void resetQueue(void);        // Optional: Reset queue before a new BFS

// BFS function for a grid
bool bfs(Vector2 start, Vector2 goal);

#endif // BFS_H
