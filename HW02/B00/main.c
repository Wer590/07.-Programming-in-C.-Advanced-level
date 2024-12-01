/*
 * Максимальный блок
Описана структура данных
typedef struct list {
uint64_t address;
size_t size;
char comment[64];
struct list *next;
} list;
Требуется реализовать только одну функцию, которая в данном списке находит
 адрес блока памяти занимающий больше всего места.
 Адрес хранится в поле address, поле size - соответствующий размер данного блока.
 Если список пустой, то функция должна возвращать NULL.
 Если есть несколько таких блоков, то вернуть адрес любого из них.
 Прототип функции: uint64_t findMaxBlock(list *head)
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
/* -----------------end----------------- */

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

    insert(&head, 140525067852320, 10);
    insert(&head, 140525067852900, 100);
    insert(&head, 140525067852350, 30);
    

    printList(head);

    printf("%llu", (uint64_t)findMaxBlock(head));

    return 0;
}
