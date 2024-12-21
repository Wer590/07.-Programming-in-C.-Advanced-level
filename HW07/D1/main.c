#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"

typedef struct tree 
{
	int key;
	struct tree *left, *right;
} tree;

void insert(tree **root, int key)
{
	if(!(*root))
	{
		*root = (tree*) malloc(sizeof(tree));
		(*root)->key = key;
		(*root)->left = (*root)->right = NULL;
	}
	else if (key < ((*root)->key))
		insert(&((*root)->left), key);
	else
		insert(&((*root)->right), key);
}

void btUpView(tree *root)
{
	if (!root)
	{
		return;
	}

	void inorder(tree *root)
	{
		if(root == NULL)
			return;
		if(root->left)
		{
			inorder(root->left);
		}
		printf("%d ", root->key);
}
	void outorder(tree *root)
	{
		if( root == NULL)
			return;

		printf("%d ", root->key);
		if((root->right))
			outorder(root->right);
	}
	inorder(root);
	if ( root && root->right)
		outorder(root->right);
	printf("\n");
}

int main()
{
	tree *tr = NULL;
	insert(&tr, 10);
	insert(&tr, 5);
	insert(&tr, 15);
	insert(&tr, 3);
	insert(&tr, 7);
	insert(&tr, 13);
	insert(&tr, 18);
	insert(&tr, 1);
	insert(&tr, 6);
	insert(&tr, 14);
	insert(&tr, 0);

	btUpView(tr);

	return 0;
}
