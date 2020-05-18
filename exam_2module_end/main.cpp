#include <iostream>

void print_array(float **array, int size)
{
    for(int i = 0; i < size; i++)
        printf("%f ", (*array)[i]);
    printf("\n");
}

int main() {
    // int size, shift;
    // float *array, *shifted_array;
    // printf("type array size: ");
    // scanf("%d", &size);
    // printf("type elements of array divided by spaces or line breaks: ");
    // array = (float *) malloc(sizeof(float)*size);
    // for(int i = 0; i < size; i++)
    //     scanf("%f", &array[i]);
    // print_array(&array, size);
    // printf("type shift number: ");
    // scanf("%d", &shift);
    // shifted_array = (float *) malloc(sizeof(float)*size);
    // for(int i = 0; i < size; i ++)
    //     shifted_array[i] = array[(i + shift)%size];
    // print_array(&shifted_array, size);
    // free(array);
    // free(shifted_array);
    // return 0;


    // for(int l = 0, i = 0; i < 10 && l < 10; i++, l++)
    // {
    //     printf("%d ", i * l);
    // }

    int i = 0;
    // while(i < 10)
    // {
    //    printf("%d", i);
    //    i++;
    // }

    // do
    // {
    //     printf("%d", i);
    //     i++;
    //     if(i > 20)
    //         break;
    // }
    // while(10);

    int height = 5, width = 5;

    int **arr = (int **) malloc(sizeof(int*)*height);
    for(int j = 0; j < height; j++)
        arr[j] = (int *) malloc(sizeof(int)*width);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            arr[i][j] = i*width + j;
        printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    for(int i = 0; i < height; i++)
        free(arr[i]);
    free(arr);
}
