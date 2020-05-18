#include <math.h>
#include <stdio.h>

int get_int()
{
//function for integer reading
    long a;
    char c;
    while ((scanf("%ld%c", &a, &c) != 2 || c != '\n')||(a!=(long)(int)a)
    ||(a < 0))
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

float get_float(float min, float max)
{
//function for float reading
    double a;
    char c;
    while ((scanf("%lf%c", &a, &c) != 2 || c != '\n')||(!compare(a, (double)(float)a))
            ||(max > min &&((a > max)||(a < min))))
    {
        printf("Incorrect, please try again:");
        while(c !='\n' && getchar() != '\n');
    }
//returns a float from console
    return a;
}

int main() {
    int k;
    float x, y, *arr = NULL;

    // user input
    printf("Print k here:");
    k = get_int();
    printf("Print X here:");
    x = get_float(1, 0);
    printf("Print Y here:");
    y = get_float(1, 0);

    // initializing array
    arr = (float *) calloc(sizeof(float), k);

    // reading array
    for (int i = 0; i < k; i++) {
        arr[i] = get_float(1, 0);
    }
    float min_res = 1, sum = 0;
    int first_pos = k - 1, last_pos = 0, counter = 0;

    // finding the greatest negative value and the first and the last positive values
    for (int i = 0; i < k; i++)
    {
        if(arr[i] < 0 && (arr[i] > min_res || min_res > 0))
            min_res = arr[i];
        if(first_pos == k - 1 && arr[i] > 0)
            first_pos = i + 1;
        if(arr[i] > 0)
        {
            counter++;
            last_pos = i - 1;
        }
    }

    // counting of the mean value
    for(int i = first_pos; i <= last_pos; i++)
    {
        sum += arr[i];
    }
    float mean = 0;
    if(counter > 1 && (last_pos >= first_pos))
        mean = sum/(last_pos - first_pos + 1);

    // output
    if(min_res < 0)
        printf("The greatest negative number is %e \n", min_res);
    else
        printf("There is no negative numbers in array! \n");
    if(counter > 1)
        printf("The mean value between the first and the last positive elements of array is: %e \n", mean);
    else
        if(counter == 1)
            printf("There is only one positive number in array! \n");
        else
        printf("Thee is no positive numbers in array! \n");
}


