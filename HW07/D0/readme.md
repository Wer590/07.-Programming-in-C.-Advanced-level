Submit a solution for D0-Отсортировать слова
Дана строка, состоящая из английских букв и пробелов. В конце строки символ точка. Все слова разделены одним пробелом. Необходимо составить из слов односвязный список и упорядочить по алфавиту. Список необходимо удалить в конце программы. Для сравнение строк можно использовать strcmp. Необходимо использовать данную структуры организации списка. struct list { char word[20]; struct list *next; } Необходимо реализовать односвязный список и обслуживающие его функции. add_to_list swap_elements print_list delete_list

Examples

	Input
	efg abcd zzz.

	Output
	abcd efg zzz

	Input
	fffff kkkkkk a.

	Output
	a fffff kkkkkk

