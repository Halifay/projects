//
// Created by mikhail on 21.05.2020.
//

#ifndef LAB_13_BINARYTREE_H
#define LAB_13_BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_
{
    char *word;
    int quantity;
    void *left, *right;
} node;

// typedef struct tree_
// {
//     node *first;
// } tree;

void dfs(node *);
void bfs(node *);
void new_node(node *);
// void new_tree(node *);
void add_word(node *, char *);
int get_quantity(node *, char *);
void destroy_tree(node *);

const int str_max_size = 20;


void new_node(node *one)
{
    one->word = NULL;
    one->left = NULL;
    one->right = NULL;
    one->quantity = 0;
}


void add_word(node *one, char *word)
{
    if(one->word == NULL)
    {
        one->word = (char *)calloc(str_max_size, sizeof(char));
        strcpy(one->word, word);
        one->left = (node *)calloc(1, sizeof(node));
        new_node(one->left);
        one->right = (node *)calloc(1, sizeof(node));
        new_node(one->right);
        one->quantity = 1;
        return;
    }

    int res = strcmp(one->word, word);
    if(res < 0)
    {
        add_word(one->right, word);
        return;
    }

    if(res == 0)
    {
        one->quantity++;
        return;
    }

    if(res > 0)
    {
        add_word(one->left, word);
        return;
    }
}


int get_quantity(node *one, char *word)
{
    if(one->word == NULL)
    {
        return 0;
    }

    int res = strcmp(one->word, word);
    if(res < 0)
    {
        return get_quantity(one->left, word);
    }

    if(res == 0)
    {
        return one->quantity;
    }

    if(res > 0)
    {
        return get_quantity(one->right, word);
    }
}


void dfs(node *one)
{
    if(one->word == NULL)
        return;

    printf("%s - %d\n", one->word, one->quantity);
    dfs(one->left);
    dfs(one->right);
}

int get_size(node *one)
{
    if(one->word == NULL)
    {
        return 0;
    }
    return 1 + get_size(one->left) + get_size(one->right);
}

void bfs(node *one)
{
    if(one->word == NULL)
    {
        return;
    }
    int size = get_size(one);
    node **queue = (node **)calloc(size*2 + 1, sizeof(node *));
    int pos = 0;
    int last = 1;
    queue[0] = one;
    for(int cur = 0; cur < size*2 + 1; cur++)
    {
        node *one = queue[cur];
        if(one == NULL || one->word == NULL)
        {
            continue;
        }

        queue[last++] = one->left;
        queue[last++] = one->right;

        printf("%s - %d\n", one->word, one->quantity);
    }
}


void destroy_tree(node *one)
{
    if(one->word == NULL)
    {
        return;
    }
    destroy_tree(one->left);
    destroy_tree(one->right);

    free(one->word);
    free(one->left);
    free(one->right);
}


void get_max(node *one)
{
    if(((node *)(one->right))->word == NULL)
    {
        printf("The biggest word in tree is %s. It occurs %d time", one->word, one->quantity);
        if(one->quantity > 1)
        {
            printf("s");
        }
        printf(" in the text.\n");
        return;
    }
    get_max(one->right);
}
#endif //LAB_13_BINARYTREE_H
