#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printScores(int[], int, char[]);
void bogoSort(int *, int);
void shuffle(int *, int);
int orderCheck(int *, int);

int main()
{
    const int SIZE = 5; //定数として配列のサイズを宣言
    int scores[SIZE] = {0, 60, 70, 100, 90};
    //処理コード
    srand((unsigned int)time(NULL));
    printScores(scores, SIZE, "scores");
    bogoSort(scores, SIZE);
    printScores(scores, SIZE, "results");
    return 0;
}

void printScores(int scores[], int size, char name[])
{
    int i;

    printf("%s =", name);
    for (i = 0; i < size; i++)
    {
        printf(" %d", scores[i]);
    }
    printf("\n");
}

void shuffle(int *array, int size)
{
    int i;
    for (i = size - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}

int orderCheck(int *array, int size)
{
    int i;
    for (i = 0; i < size - 1; i++)
    {
        if (!(array[i] >= array[i + 1]))
        {
            return 0;
        }
    }

    return 1;
}

void bogoSort(int *array, int size)
{
    while (!orderCheck(array, size))
    {
        shuffle(array, size);
    }
}