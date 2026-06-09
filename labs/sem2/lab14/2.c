#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Узел очереди */
typedef struct Node {
    char data;
    struct Node *next;
} Node;

/* Очередь: указатели на голову (front) и хвост (rear) */
typedef struct {
    Node *front;
    Node *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

/* Добавить элемент в хвост очереди (enqueue) */
void enqueue(Queue *q, char val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

/* Удалить элемент из головы очереди (dequeue) */
char dequeue(Queue *q) {
    if (q->front == NULL) return '\0';
    Node *tmp = q->front;
    char val = tmp->data;
    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;
    free(tmp);
    return val;
}

/* Удаление дубликатов:
   seen[c] = 1 означает, что буква c уже встречалась.
   Обходим очередь: если буква уже есть в seen — удаляем узел,
   иначе помечаем как встреченную и идём дальше. */
void removeDuplicates(Queue *q) {
    int seen[26] = {0};   /* seen[i] = 1, если буква 'a'+i уже была */

    Node *cur = q->front;
    Node *prev = NULL;

    while (cur != NULL) {
        int idx = cur->data - 'a';

        if (seen[idx]) {
            /* Буква уже встречалась — удаляем узел */
            Node *tmp = cur;
            if (prev == NULL)
                q->front = cur->next;
            else
                prev->next = cur->next;
            if (cur->next == NULL)
                q->rear = prev;
            cur = cur->next;
            free(tmp);
        } else {
            /* Первый раз встретили — запоминаем */
            seen[idx] = 1;
            prev = cur;
            cur = cur->next;
        }
    }
}

void printQueue(Queue *q) {
    if (q->front == NULL) { printf("Очередь пуста\n"); return; }
    Node *cur = q->front;
    while (cur != NULL) {
        printf("%c ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    /* Заполняем очередь: a b c a d b e c f a */
    char input[] = "abcadbecfa";
    for (int i = 0; input[i]; i++)
        enqueue(&q, input[i]);

    printf("До удаления:    ");
    printQueue(&q);

    removeDuplicates(&q);

    printf("После удаления: ");
    printQueue(&q);

    return 0;
}