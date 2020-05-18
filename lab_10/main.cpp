#include <iostream>
#include <cstring>
#include <cstdio>
#include <stdio_ext.h>
#include <cassert>

const int STRING_MAX_SIZE = 300;
const char *path = "/home/mikhail/Garage/from_old/C/lab_10/";//path to working directory in my system


void print_text_result(char ***text, int *nlines)
{
    for(int i = 0; i < *nlines; i++)
    {
        printf("%s", (*text)[i]);
    }
}


void print_numbers_result(float **numbers, int *nelements)
{
    for(int i = 0; i < *nelements; i++)
    {
        printf("%f ", (*numbers)[i]);
    }
}


// makes working path to file on my system
char *get_full_path(char *filename)
{
    char *ret = (char *)calloc(strlen(path) + strlen(filename), sizeof(char));
    strcat(ret, path);
    strcat(ret, filename);
    return ret;
}

// fills variable with text from file
void text_from_file(char *filename, char ***text, int *nlines)
{
    char *fullpath = get_full_path(filename);
    FILE *file = fopen(fullpath, "rb");
    assert(file != NULL);
    int capacity = 2;// maximum numbers of lines in array
    *nlines = 0;
    *text = (char **)calloc(capacity, sizeof(char **));
    char line[STRING_MAX_SIZE];
    fgets(line, STRING_MAX_SIZE * sizeof(char), file);
    while(feof(file) == 0)
    {
        if(*nlines == capacity)
        {
            capacity *=2;
            *text = (char **)realloc(*text, capacity*sizeof(char **));
        }
        (*text)[*nlines] = (char *)calloc(strlen(line), sizeof(char *));
        strcat((*text)[*nlines], line);
        //memset(line, '\0', STRING_MAX_SIZE*sizeof(char));
        fgets(line, STRING_MAX_SIZE * sizeof(char), file);
        (*nlines)++;
    }

    free(fullpath);
}

//write lines into file from variable
void text_to_file(char *filename, char ***text, int *nlines)
{
    char *fullname = get_full_path(filename);
    FILE *file = fopen(fullname, "wb");
    for(int i = 0; i < *nlines; i++)
        fprintf(file, "%s", (*text)[i]);

    free(fullname);
}

void numbers_from_file(char *filename, float **numbers, int *nelements)
{
    char *fullpath = get_full_path(filename);
    FILE *file = fopen(fullpath, "rb");
    assert(file != NULL);
    int capacity = 2;
    *nelements = 0;
    *numbers = (float *)calloc(capacity, sizeof(float));
    float num;
    fscanf(file, "%f", &num);
    while(feof(file) == 0)
    {
        if(*nelements == capacity)
        {
            capacity *=2;
            *numbers = (float *)realloc(*numbers, capacity*sizeof(float));
        }
        (*numbers)[*nelements] = num;
        fscanf(file, "%f", &num);
        (*nelements)++;
    }

    free(fullpath);
}


void numbers_to_file(char *filename, float **numbers, int *nelements)
{
    char *fullname = get_full_path(filename);
    FILE *file = fopen(fullname, "wb");
    for(int i = 0; i < *nelements; i++)
        fprintf(file, "%f ", (*numbers)[i]);

    free(fullname);
}


//task a
void plan_a(char *input, char *output, bool do_print)
{
    float *numbers;
    int nelements = 0;
    numbers_from_file(input, &numbers, &nelements);
    float *new_numbers = (float *)calloc(nelements, sizeof(float));
    int new_size = 0;
    int last_biggest = 0;
    for(int i = 0; i < nelements; i++)
        if(numbers[last_biggest] <= numbers[i])
            last_biggest = i;

    for(int i = 0; i < nelements; i++)
        if(i <= last_biggest || numbers[i] <= 0)
        {
            new_numbers[new_size] = numbers[i];
            new_size++;
        }

    numbers_to_file(output, &new_numbers, &new_size);
    if(do_print)
        print_numbers_result(&new_numbers, &new_size);

    free(numbers);
    free(new_numbers);
}


//task b
void plan_b(char *input, char *output, bool do_print)
{
    char **text;
    int nlines = 0;
    text_from_file(input, &text, &nlines);
    for(int i = 0; i < nlines; i++)
    {
        int first_ast = -1;
        for(int j = 0; j < strlen(text[i]); j++)
            if(text[i][j] == '*')
            {
                first_ast = j;
                break;
            }
        for(int j = 0; j < first_ast; j++)
        {
            if(text[i][j] >='a' && text[i][j] <= 'z')
                text[i][j] = '3';
        }
    }
    if(do_print)
        print_text_result(&text, &nlines);
    text_to_file(output, &text, &nlines);

    free(text);
}


int main() {
    char program_key, result_key;
    printf("Which program to run? a/b\n");
    scanf(" %c", &program_key);
    printf("%c\n", program_key);
    //add check
    printf("Show result? y/n\n");
    scanf(" %c", &result_key);
    printf("%c\n", result_key);
    //add check
    //__fpurge(stdin);

    char *input = "f.bin", *output = "g.bin";
    bool do_print = true;
    if(result_key != 'y')
        do_print = false;

    if(program_key == 'a')
    {
        plan_a(input, output, do_print);
    }
    else
    {
        plan_b(input, output, do_print);
    }

    return 0;
}
