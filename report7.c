#include <stdio.h>

void printScores(int[], int, char[]);
void bucketSort(int *, int);

int main()
{
    const int SIZE = 5; //定数として配列のサイズを宣言
    int scores[SIZE] = {0, 60, 70, 100, 90};
    //処理コード
    printScores(scores, SIZE, "scores");
    bucketSort(scores, SIZE);
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

void bucketSort(int *array, int size)
{
    int bucket[101];
    int i;
    for (i = 0; i <= 100; i++)
    {
        bucket[i] = 0;
    }

    for (i = 0; i < size; i++)
    {
        bucket[*(array + i)]++;
    }
    i = 0;
    int bucketNum = 100;
    while (i < size)
    {
        if (bucket[bucketNum] > 0)
        {
            *(array + i) = bucketNum;
            i++;
            bucket[bucketNum]--;
        }
        else
        {
            bucketNum--;
        }
    }
}