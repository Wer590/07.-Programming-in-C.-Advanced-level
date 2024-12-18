#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

struct list
{
	char word[20];
	struct list *next;
}list;

void add_to_list(struct list **list, const char* word)
{
	struct list* new = (struct list*)malloc(sizeof(struct list));
	strcpy(new->word, word);
	new->next = *list;
	*list = new;
}

void delete_list(struct list **list)
{
	struct list* prev = NULL;
	while((*list)->next)
	{
		prev = *list;
		*list = (*list)->next;
		free(prev);
	}
	free(*list);
}

void swap_elements(struct list *list_a, struct list *list_b)
{
	char temp[20];
	strcpy(temp, list_a->word);
	strcpy(list_a->word, list_b->word);
	strcpy(list_b->word, temp);
}

void sort_list(struct list *list)
{
	struct list *list_a, *list_b;
	for(list_a = list; list_a != NULL; list_a = list_a->next)
	{
		for(list_b = list_a->next; list_b != NULL; list_b = list_b->next)
		{
			if (strcmp(list_a->word, list_b->word) > 0)
			{
				swap_elements(list_a, list_b);
			}
		}
	}
}

void print_list(struct list *list)
{

	while(list)
	{
		int len = strlen(list->word);
		if(len != 0)
		{
			printf("%s ", list->word);
		}
		list = list->next;
	}
	printf("\n");
}

int main(void)
{
	struct list *head = &list;
	head = calloc(1,sizeof(struct list));

	char input_str[500];
	fgets(input_str, sizeof(input_str), stdin);

	int len = strlen(input_str);

	//if (input_str[len - 1] == '\n')
	//{
	//	input_str[len - 1] = '\0';
	//}


	input_str[len - 2] = '\0';

	char *token = strtok(input_str, " ");
	while(token)
	{ 
		add_to_list(&head, token);
		token = strtok(NULL, " ");
	}

	sort_list(head);
	print_list(head);
	delete_list(&head);

	return 0;
}
