#include <iostream>
#include <cmath>

int get_int()
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

bool compare(double a, double b)
{
    return fabs(a - b) < 0.0000001;
}

double get_double()
{
//function for float reading
    double a;
    char c;
    while (scanf("%lf%c", &a, &c) != 2 || c != '\n')
    {
        printf("Incorrect, please try again:");
        while(c !='\n' && getchar() != '\n');
    }
//returns a float from console
    return a;
}

void print_all(double *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%lf ", arr[i]);
    }
    printf("\n");
}

void delete_all_before_the_last_maximum(double *arr, int *size)
{
    int last_max = 0;
    for (int i = 0; i < *size; i++)
    {
        if(arr[last_max] < arr[i] || compare(arr[last_max], arr[i]))
            last_max = i;
    }

    int cur = 0;
    for(int i = 0; i < *size; i++)
    {
        if(arr[i] > 0 && i < last_max)
            continue;
        arr[cur] = arr[i];
        cur++;
    }
    // printf("%ld \n", last_max);
    // printf("%ld ", )
    *size = cur;
}

int main() {
    int k;
    double *arr = NULL;
    // user input
    printf("Print k here:");
    k = get_int();
    arr = (double *) calloc(sizeof(double), k);
    printf("Type all elements of array separated by line breaks \n");
    for(int i = 0; i < k; i++)
    {
        arr[i] = get_double();
    }
    // work and output
    print_all(arr, k);
    delete_all_before_the_last_maximum(arr, &k);
    print_all(arr, k);

    return 0;
}
