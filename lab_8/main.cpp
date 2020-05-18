#include <iostream>
#include <time.h>
#include <assert.h>

//функция обмена значений для двух переменных
void swap(long *first, long *second)
{
    if(first == second)
        return;
    *first = (*first)^(*second);
    *second = (*first)^(*second);
    *first = (*first)^(*second);
}

//функция для считывания массива с заданным размером
void input_array(long **array, long *size)
{
    scanf("%ld", size);
    *array = (long *) calloc(*size, sizeof(long));
    for(long i = 0; i < *size; i++)
        scanf("%ld", &(*array)[i]);
}

//копирует массив из одного адресса в другой
void array_copy(long **to, long **from, long *size)
{
    *to = (long *) calloc(*size, sizeof(long));
    for(long i = 0; i < *size; i++)
        (*to)[i] = (*from)[i];
}

//выводит массив в консоль
void print_array(long **array, long *size)
{
    for(long i = 0; i < *size; i++)
        printf("%ld ", (*array)[i]);
    printf("\n");
}

void bubble_sort(long **array, long *size)
{
    for(long i = 0; i < *size; i++)
        for(long j = 0; j < *size - i - 1; j++)
            if((*array)[j] > (*array)[j + 1])
                swap(&((*array)[j]), &((*array)[j + 1]));
}

void insertion_sort(long **array, long *size)
{
    for(long i = 0; i < *size; i++)
        for(long j = i; j > 0; j--)
            if((*array)[j-1] > (*array)[j])
                swap(&((*array)[j-1]), &((*array)[j]));
            else
                break;
}

//функция определяющая элемент, который будет центральным в разбиении в quick sort
long get_pivot(long left, long right)
{
    return right-1;
}

void quick_sort(long **array, long left, long right)
{
    //printf("%d %d \n", left, right);
    if(right - left <= 1)
        return;
    swap(&(*array)[get_pivot(left, right)], &(*array)[right-1]);
    long pivot = (*array)[right-1];
    long i = left, j = right - 1;
    while(i <= j)
    {
        while(i < right && (*array)[i] < pivot)
            i++;
        while(j > left && (*array)[j] >= pivot)
            j--;
        if(i >= j)
            break;
        swap(&(*array)[i], &(*array)[j]);
    }
    // printf("i:%d, j:%d\n", i, j);
    //print_array(array, &a);
    swap(&(*array)[right - 1], &(*array)[i]);
    quick_sort(array, left, j+1);
    quick_sort(array, j+1, right);
}

//фукнция, проверяющая, что массив отсортирован(по возрастанию)
bool check_order(long **array, long *size)
{
    for(long i = 1; i < *size; i++)
        if((*array)[i] < (*array)[i-1])
            return false;
    return true;
}

//заполняет массив случайными эелементами
void generate_array(long **array, long *size)
{
    *array = (long *) calloc(*size, sizeof(long));
    srand(time(0));
    for(long i = 0; i < *size; i ++)
        (*array)[i] = (rand()%30);
}

//функция, выводящая скорость каждой из трех сортировок для заданного количества элементов и случайного массива
void measure(long size)
{
    long start, end;
    double time;
    long *origin, *array;
    generate_array(&origin, &size);

    if(size < 30)
    {
        printf("shuffled array looks like:\n");
        print_array(&origin, &size);
        printf("\n");
    }
    array_copy(&array, &origin, &size);
    start = clock();
    bubble_sort(&array, &size);
    assert(check_order(&array, &size));
    end = clock();
    time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Bubble sort got %f seconds with %d elements\n", time, size);
    if(size < 30)
        print_array(&array, &size);
    free(array);

    array_copy(&array, &origin, &size);
    start = clock();
    insertion_sort(&array, &size);
    assert(check_order(&array, &size));
    end = clock();
    time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Insertion sort got %f seconds with %d elements\n", time, size);
    if(size < 30)
        print_array(&array, &size);
    free(array);

    array_copy(&array, &origin, &size);
    start = clock();
    quick_sort(&array, 0, size);
    assert(check_order(&array, &size));
    end = clock();
    time = ((double)(end - start))/CLOCKS_PER_SEC;
    printf("Quick sort got %f seconds with %d elements\n", time, size);
    if(size < 30)
        print_array(&array, &size);
    free(array);
    free(origin);
}

int main() {
    // for(long i = 1; i <= 10; i++)
    // {
    //     measure(100000*i/10);
    // }
    measure(20);
    return 0;
}
