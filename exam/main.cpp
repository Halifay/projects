#include <math.h>
#include <stdio.h>

int main(void) {
    // ввод данных и формирвоание матрицы
    int height, width;
    printf("введите высоту и ширину матрицы\n");
    scanf("%d %d", &height, &width);
    int **matrix = (int **) calloc(sizeof(int *), height);
    for(int i = 0; i < height; i ++)
        matrix[i] = (int *) calloc(sizeof(int), width);

    // считывание матрицы и подсчет значений
    printf("введите элементы матрицы построчно\n");
    int sum = 0, count = 0;
    for(int i = 0; i < height; i ++)
        for(int j = 0; j < width; j ++)
        {    scanf("%d", &matrix[i][j]);
            if(j < i && matrix[i][j]%2 == 0)
            {
                sum += matrix[i][j];
                count ++;
            }
        }

    // вывод матрицы
    for(int i = 0; i < height; i ++) {
        for (int j = 0; j < width; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // вывод среднего арифметического
    if(count == 0)
        printf("нет четных чисел ниже главной диагонали");
    else
        printf("%f", (float)sum/(float)count);
    return 0;
}


