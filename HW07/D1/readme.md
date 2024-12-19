Submit a solution for D1-Вид сверху

В программе описана структура для хранения двоичного дерева: typedef struct tree { datatype key; struct tree *left, *right; } tree; Необходимо реализовать функцию, которая печатает вид дерева сверху. Функция должна строго соответствовать прототипу: void btUpView(tree *root)

Examples

Input

10 5 15 3 7 13 18 1 6 14 0

Output

1 3 5 10 15 18