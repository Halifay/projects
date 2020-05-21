//
// Created by mikhail on 19.05.2020.
//

#ifndef LAB_12_DOUBLYLINKEDLIST_H
#define LAB_12_DOUBLYLINKEDLIST_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const int str_max_length = 64;

typedef struct node_{
    void *prev, *next;
    char *word;
} node;

typedef struct list_{
    node *first, *last;
} list;

void new_list(list *);
void read_list(list *);
void print_list(list *);
void split_list(list *, list *, char *);
void *find_word(list *, char *);
void destroy_list(list *);
void clear();

void clear()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void new_list(list *text)
{
    text->first = NULL;
    text->last = NULL;
}

void read_list(list *text)
{
    text->first = NULL;
    text->last = NULL;
    char *word = NULL;
    while(word == NULL || (strlen(word) > 0 && strchr(word, '.')==NULL))
    {
        word = (char *)calloc(str_max_length, sizeof(char));
        scanf("%s", word);
        node *addition = (node *)calloc(1, sizeof(node));
        addition->word = word;
        if(text->first == NULL)
        {
            text->first = addition;
        }
        if(text->last != NULL)
        {
            text->last->next = addition;
        }
        addition->prev = text->last;
        text->last = addition;
        addition->next = NULL;
    }
    char * dot = strchr(text->last->word, '.');
    *dot = '\0';
}

void print_list(list *text)
{
    node *cur = text->first;
    while(cur != NULL)
    {
        printf("%s ", cur->word);
        cur = cur->next;
    }
    printf("\n");
}

void *find_word(list *text, char *word)
{
    node *ret = text->first;
    while(ret != NULL)
    {
        if(strcmp(ret->word, word)==0)
            return ret;
        ret = ret->next;
    }
    return NULL;
}


void destroy_list(list *text)
{
    node *first, *second;
    first = text->first;
    while(first != NULL)
    {
        second = first->next;
        free(first->word);
        free(first);
        first = second;
    }
}


//first argument is list with some text, the second is an empty list
//function finds first word equal to input and splits initial list in left and right
// for this word
void split_list(list *text1, list *text2, char *word)
{
    destroy_list(text2);
    node *center = find_word(text1, word);
    if(center == NULL)
    {
        printf("There is no word %s in list.\n", word);
        return;
    }

    text2->first = center->next;
    if(center->next == NULL)
        text2->last = NULL;
    else
    {
        text2->last = text1->last;
        text2->first->prev = NULL;
    }

    text1->last = center->prev;
    if(center->prev == NULL)
        text1->first = NULL;
    else
        text1->last->next = NULL;

    free(center->word);
    free(center);
}






#endif //LAB_12_DOUBLYLINKEDLIST_H
