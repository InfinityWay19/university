#include <stdio.h>
#include <stdlib.h>

/* Структура узла односвязного списка */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

/* Добавление элемента в конец списка */
void push(Node **head, int val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = val;
    newNode->next = NULL;
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *cur = *head;
    while (cur->next != NULL)
        cur = cur->next;
    cur->next = newNode;
}

/* Удаление всех отрицательных элементов */
void deleteNegatives(Node **head) {
    /* Удаляем отрицательные элементы в начале списка */
    while (*head != NULL && (*head)->data < 0) {
        Node *tmp = *head;
        *head = (*head)->next;
        free(tmp);
    }

    /* Удаляем отрицательные элементы в середине и конце */
    Node *cur = *head;
    while (cur != NULL && cur->next != NULL) {
        if (cur->next->data < 0) {
            Node *tmp = cur->next;
            cur->next = tmp->next;
            free(tmp);
        } else {
            cur = cur->next;
        }
    }
}

/* Вывод списка на экран */
void printList(Node *head) {
    if (head == NULL) {
        printf("Список пуст\n");
        return;
    }
    Node *cur = head;
    while (cur != NULL) {
        printf("%d ", cur->data);
        cur = cur->next;
    }
    printf("\n");
}

/* Освобождение памяти всего списка */
void freeList(Node *head) {
    Node *tmp;
    while (head != NULL) {
        tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node *head = NULL;

    /* Создаём список: 3 -1 7 -5 0 -9 4 */
    int values[] = {3, -1, 7, -5, 0, -9, 4};
    for (int i = 0; i < 7; i++)
        push(&head, values[i]);

    printf("До удаления:    ");
    printList(head);

    deleteNegatives(&head);

    printf("После удаления: ");
    printList(head);

    freeList(head);
    return 0;
}