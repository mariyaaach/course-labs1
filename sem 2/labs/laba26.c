#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1000
typedef struct {
	int data[MAX_SIZE];
	int rear, front;
} Queue;


void initializeQueue(Queue* q);
int isFull(Queue* q);
int isEmpty(Queue* q);
void enqueue(Queue* q, int num);
void dequeue(Queue*q);
void sortQueue(Queue* q);
void displayQueue(Queue* q);

int main() {
	Queue q; // Queue declaration
	int choice, element;

	initializeQueue(&q); // Initialize the queue

	do {
		printf("\nQUEUE MENU\n");
		printf("1. Enqueue an element\n");
		printf("2. Sort the queue in ascending order\n");
		printf("3. Display the queue\n");
		printf("4. Quit\n");
        printf("5. Pop\n");
		printf("Enter your choice : ");
		scanf("%d", &choice);
        switch (choice) {
        case 1:
            printf("\nEnter the element to be added to queue : ");
            scanf("%d", &element);
            enqueue(&q, element);
            break;
        case 2:
            sortQueue(&q);
            break;
        case 3:
            displayQueue(&q);
            break;
        case 4:
            break;
        case 5:
            dequeue(&q);
            break;
        default:
            printf("\nInvalid choice.\n");
        }
    } while (choice != 4);

    return 0;
}
void dequeue(Queue*q) {
    if (isEmpty(q))
        printf("Queue is empty. Can't dequeue.\n");
    else if (q->front == q->rear) {
        printf("Dequeued %d.\n", q->data[q->front]);
        q->front = q->rear = -1;
    } else {
        printf("Dequeued %d.\n", q->data[q->front]);
        q->front++;
    }
}

void initializeQueue(Queue* q) {
    q->rear = -1;
    q->front = 0;
}



int isFull(Queue* q) {
    if (q->rear == MAX_SIZE - 1) {
        return 1;
    }
    else {
        return 0;
    }
}
int isEmpty(Queue* q) {
    if (q->front > q->rear) {
        return 1;
    }
    else {
        return 0;
    }
}


void enqueue(Queue* q, int num) {
    if (isFull(q) == 1) {
        printf("Queue is full. Cannot enqueue an element.\n");
    }
    else {
        q->rear++;
        q->data[q->rear] = num;
    }
}


void sortQueue(Queue* q) {
    int i, j, k, temp;
    for (i = q->front; i <= q->rear; i++) {
        k = i;
        temp = q->data[i];

        for (j = i + 1; j <= q->rear; j++) {
            if (q->data[j] < temp) {
                k = j;
                temp = q->data[j];
            }
        }

        q->data[k] = q->data[i];
        q->data[i] = temp;
    }

    printf("\nQueue sorted in ascending order.\n");
}

void displayQueue(Queue* q) {
    int i;
    if (isEmpty(q) == 1) {
        printf("\nQueue is empty.\n");
    }
    else {
        printf("\n");

        for (i = q->front; i <= q->rear; i++) {
            printf("%d ", q->data[i]);
        }
    }
}

