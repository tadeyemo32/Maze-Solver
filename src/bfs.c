#include "grid.h"
#include "raylib.h"
#include <stdio.h>
#include "bfs.h"
#include "stdlib.h"
Node* head = NULL;
Node* rear = NULL;
int queueCount = 0;
Node* GOAL = NULL;


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



bool enQueue(Node *node) {
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

bool isQueueEmpty(void){

    if(queueCount == 0)return true;
    

    return false;
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


// BFS function for a grid
bool bfs(){
    resetQueue();
    enQueue(head);
 while (!isQueueEmpty()) {
    Node* current = head; // or get current from queue
    Vector2 pos = current->pos;
  int x = pos.x;
  int y= pos.y;

  if(grid[(int)y][(int)x] == CELL_GOAL){
    
  }

    
    deQueue(); // after processing
}



return false;

}