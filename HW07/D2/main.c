#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
    int key;
    struct tree *left, *right;
    struct tree *parent; 
} tree;

tree *findNode(tree *root, int key) {
    if (root == NULL) {
        return NULL; 
    }
    if (root->key == key) {
        return root; 
    }
 
    tree *leftResult = findNode(root->left, key);
    if (leftResult != NULL) {
        return leftResult;
    }
    return findNode(root->right, key);
}

tree *findBrother(tree *root, int key) {
    
    tree *node = findNode(root, key);
    if (node == NULL || node->parent == NULL) {
        return NULL; 
    }

    if (node->parent->left == node) {
        return node->parent->right; 
    } else if (node->parent->right == node) {
        return node->parent->left; 
    }

    return NULL; 
}

tree *createNode(int key, tree *parent) {
    tree *newNode = (tree *)malloc(sizeof(tree));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = parent;
    return newNode;
}


int main() {

    tree *root = createNode(10, NULL);
    root->left = createNode(5, root);
    root->right = createNode(15, root);
    root->left->left = createNode(3, root->left);
    root->left->right = createNode(7, root->left);
    root->right->left = createNode(13, root->right);
    root->right->right = createNode(18, root->right);
    root->left->left->left = createNode(1, root->left->left);
    root->left->left->right = createNode(6, root->left->left);

    tree *brother = findBrother(root, 10);
    if (brother != NULL)
    {
        printf("%d\n", brother->key);
    }
    else
    {
        printf("0\n");
    }

    return 0;
}
