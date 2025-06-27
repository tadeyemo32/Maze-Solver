#include "grid.h"
#include "raylib.h"
#include <stdio.h>
#include "bfs.h"
#include <stdlib.h>

Node* head = NULL;
Node* rear = NULL;
int queueCount = 0;
Node* GOAL = NULL;

Vector2 parent[GRID_ROWS][GRID_COLS];

Node* createNode(Vector2 pos) {
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(1);
    }

    newNode->pos = pos;
    newNode->next = NULL;
    return newNode;
}

bool enQueue(Node* node) {
    if (queueCount == 0) {
        head = node;
        node->next = NULL;
        queueCount++;
        return true;
    } else if (queueCount == 1) {
        head->next = node;
        node->next = NULL;
        queueCount++;
        return true;
    } else {
        Node* curr = head;
        while (curr->next) {
            curr = curr->next;
        }
        curr->next = node;
        node->next = NULL;
        queueCount++;
        return true;
    }
    return false;
}

bool deQueue() {
    if (head == NULL) return false;

    Node* temp = head;
    head = head->next;

    if (head == NULL) {
        rear = NULL;
    }

    free(temp);
    queueCount--;
    return true;
}

bool isQueueEmpty(void) {
    return (queueCount == 0);
}

void resetQueue() {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    queueCount = 0;
}


bool bfs() {
    resetQueue();

    // Clear parent array
    for (int y = 0; y < GRID_ROWS; y++) {
        for (int x = 0; x < GRID_COLS; x++) {
            parent[y][x] = (Vector2){ -1, -1 };
        }
    }

    enQueue(createNode(start));
    grid[(int)start.y][(int)start.x] = CELL_VISITED;

    while (!isQueueEmpty()) {
        Node* current = head;
        Vector2 pos = current->pos;
        int x = (int)pos.x;
        int y = (int)pos.y;

        if (grid[y][x] == CELL_GOAL) {
            // Trace back path
            Vector2 trace = (Vector2){ x, y };

            while (!(trace.x == start.x && trace.y == start.y)) {
                trace = parent[(int)trace.y][(int)trace.x];
                if (!(trace.x == start.x && trace.y == start.y)) {
                    grid[(int)trace.y][(int)trace.x] = CELL_TRACE;
                }
            }
            return true;
        }

        // Directions: up, down, left, right
        Vector2 directions[4] = {
            {x, y - 1},
            {x, y + 1},
            {x - 1, y},
            {x + 1, y}
        };

        for (int i = 0; i < 4; i++) {
            int nx = (int)directions[i].x;
            int ny = (int)directions[i].y;

            // Check bounds
            if (nx >= 0 && nx < GRID_COLS && ny >= 0 && ny < GRID_ROWS) {
                pathType type = grid[ny][nx];

                if (type == CELL_EMPTY || type == CELL_GOAL) {
                    parent[ny][nx] = (Vector2){ x, y };

                    if (type != CELL_GOAL)
                        grid[ny][nx] = CELL_VISITED;

                    enQueue(createNode((Vector2){ nx, ny }));
                }
            }
        }

        deQueue(); // Done with current node
    }

    return false; // Goal not found
}
