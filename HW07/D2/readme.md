Найти брата

В программе описано двоичное дерево: typedef struct tree { datatype key; struct tree *left, *right; struct tree *parent; //ссылка на родителя } tree; Требуется реализовать функцию, которая по ключу возвращает адрес соседнего элемента - брата. Если такого ключа нет или у узла нет брата, то необходимо вернуть 0. Прототип функции: tree * findBrother(tree *root, int key)

Examples

Input

10 5 15 3 7 13 18 1 6 14 0 3

Output

7