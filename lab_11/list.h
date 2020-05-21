//
// Created by mikhail on 18.05.2020.
//

#ifndef LAB_11_LIST_H
#define LAB_11_LIST_H
#include <stdio.h>
#include <stdlib.h>

typedef struct node_{
int power;
int coef;
void *next;
} node;

typedef struct list_{
node *first
} list;

void create_list(list *);
void print_list(list *);
node *get_power(list *, int);
void multiply(list *, int power, int a);
void destroy_list(list *);
void clear();


void create_list(list *pol)
{
    printf("Enter number of members in polynomial.\n");
    int length = 0;
    scanf("%d", &length);
    while(length < 1)
    {
        printf("Length can not be less than one. Please try again.\n");
        clear();
        scanf("%d", &length);
    }

    // pol->first = (node *)calloc(1, sizeof(node));
    pol->first = NULL;
    while(length-->0)
    {
        printf("Creating a new member of polynomial.\n");
        int power = -1;
        printf("Enter power of x for current member.\n");
        scanf("%d", &power);
        while(power < 0 || get_power(pol, power) != NULL)
        {
            printf("Power is too small or already exists. Please try again.\n");
            clear();
            scanf("%d", &power);
        }

        int coef = 0;
        printf("Enter coefficient for this power of x.\n");
        scanf("%d", &coef);
        while(coef == 0)
        {
            printf("Coefficient can't be equal to zero. Please try again.\n");
            clear();
            scanf("%d", &coef);
        }

        node *last = pol->first;
        pol->first = (node *)calloc(1, sizeof(node));
        pol->first->power = power;
        pol->first->coef = coef;
        pol->first->next = last;
    }
}


void print_list(list *pol)
{
    node *current = pol->first;
    while(current != NULL)
    {
        if(current != pol->first && current->coef>0)
            printf("+");
        if(current->power == 0)
            printf("%d", current->coef);
        else
            printf("%dx^%d", current->coef, current->power);
        current = current->next;
    }
    printf("\n");
}


void multiply(list *pol, int power, int coef)
{
    if(power < 0)
    {
        printf("Power is less than zero. Operation stopped.");
        return;
    }
    if(coef == 0)
    {
        printf("Coefficient is equal to zero. Operation stopped.");
        return;
    }

    node *current = pol->first;
    while(current != NULL)
    {
        current->power += power;
        current->coef *= coef;
        current = current->next;
    }
}


node *get_power(list *pol, int power) //UNLIMITED POWER!!!!!!
{
    node *current = pol->first;
    while(current != NULL)
    {
        if(current->power == power)
            break;
        current = current->next;
    }

    return current;
}


void clear()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void destroy_list(list *pol)
{
    node *current = pol->first;
    while(current != NULL)
    {
        pol->first = current->next;
        free(current);
        current = pol->first;
    }
}



#endif //LAB_11_LIST_H
