/*
Всего памяти
Описана структура данных для хранения информации об использованной памяти:
typedef struct list {
uint64_t address;
size_t size;
char comment[64];
struct list *next;
} list;
Требуется реализовать только одну функцию, которая анализирует данный
список и возвращает сколько всего памяти используется.
Адрес хранится в поле address, поле size - соответствующий размер данного блока.
Если список пустой, то функция должна возвращать NULL.
Прототип функции: size_t totalMemoryUsage(list *head)
*/


#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stddef.h>


typedef struct list {
    uint64_t address;
    size_t size;
    char comment[64];
    struct list *next;
} list;

void printList(list *head) {
    while(head) {
        printf("addess = %llu size = %d\n", head->address, head->size);
        head = head -> next;
    }
    printf("\n");
}

/* блок ниже был загружен для проверки в автотесты*/
size_t totalMemoryUsage(list *head) {
    if (head == NULL) {
        return 0;
    }
    size_t sum =0;

    while(head)
    {
        sum +=head->size;
        head = head->next;
    }
    return sum;
}
/* -----------------end----------------- */

uint64_t findMaxBlock(list *head) {
    if (head == NULL) {
        return 0;
    }
    uint64_t address = head->address;
    size_t size = head->size;
    uint64_t max = address;

    while(head)
    {
        if(head->size > size) {
            size = head->size;
            max = head->address;
        }
        head = head->next;
    }
    return max;
}

void insert(list **p, uint64_t address, size_t size) {
    list *elem;
    elem = malloc(sizeof(list));
    elem->address = address;
    elem->size = size;
    elem->next = *p;
    *p=elem;
}

int main(void) {

    list *head = NULL;

    insert(&head, 140525067852320, 1);
    insert(&head, 140525067852328, 8);
    insert(&head, 140525067852700, 100);
    insert(&head, 140525067852360, 20);
    insert(&head, 140525067852500, 21);

    printList(head);
    
    printf("%d\n", totalMemoryUsage(head));

    printf("%llu\n", findMaxBlock(head));

    return 0;
}
