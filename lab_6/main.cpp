#include <iostream>
#include <cmath>

int get_int_size()
{
//function for integer reading
    long a;
    char c;
    while ((scanf("%ld%c", &a, &c) != 2 || c != '\n')||(a < 0))
    {
        printf("Incorrect, please try again:");
        while(c !='\n' && getchar() != '\n');
    }
//returns an integer from console
    return a;
}

int get_int()
{
//function for integer reading
    long a;
    char c;
    while ((scanf("%ld%c", &a, &c) != 2 || c != '\n'))
    {
        printf("Incorrect, please try again:");
        while(c !='\n' && getchar() != '\n');
    }
//returns an integer from console
    return a;
}

void create_matrix(int ***mat, int x, int y)
{
    *mat = (int **) calloc(sizeof(int*), x);
    for(int i = 0; i < x; i++)
    {
        (*mat)[i] = (int *) calloc(sizeof(int), y);
    }
}

void print_matrix(int ***mat, int x, int y)
{
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            printf("%d ", (*mat)[i][j]);
        }
        printf("\n");
    }
}

int get_sum(int ***mat, int x, int y)
{
    int sum = 0;
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y - i - 1; j++)
        {
            if((*mat)[i][j] % 2 == 0)
                sum += (*mat)[i][j];
        }
    }
    return sum;
}

int main() {
    int x, y;
    int **mat = NULL;
    // user input
    printf("Type number of rows here:");
    x = get_int_size();
    printf("Type number of columns here:");
    y = get_int_size();
    create_matrix(&mat, x, y);
    // mat = (int **) calloc(sizeof(int*), x);
    for(int i = 0; i < x; i++)
    {
        mat[i] = (int *) calloc(sizeof(int), y);
    }
    for(int i = 0; i < x; i++)
    {
        for(int j = 0; j < y; j++)
        {
            printf("Type element number %d of row number %d here:", j, i);
            mat[i][j] = get_int();
        }
    }
    print_matrix(&mat, x, y);
    printf( "answer is %d", get_sum(&mat, x, y));
    return 0;
}
