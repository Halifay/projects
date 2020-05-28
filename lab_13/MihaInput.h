//
// Created by mikhail on 27.05.2020.
//

#ifndef LAB_13_MIHAINPUT_H
#define LAB_13_MIHAINPUT_H

#include <stdio.h>

void clear_input();
int get_int();


void clear_input()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}


int get_int()
{
    //function for integer reading
    long a;
    char c;
    while ((scanf("%ld%c", &a, &c) != 2 || c != '\n')||(a!=(long)(int)a)
           ||(a < 0))
    {
        printf("Incorrect integer, please try again:");
        while(c !='\n' && getchar() != '\n');
    }
    //returns an integer from console
    return a;
}

#endif //LAB_13_MIHAINPUT_H
