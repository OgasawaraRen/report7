#include <stdio.h>

void printScores(int[], int, char[]);

int main()
{
    const int SIZE = 5; //定数として配列のサイズを宣言
    int scores[SIZE] = {0, 60, 70, 100, 90};
    //処理コード
    printScores(scores, SIZE, "scores");
    //printScores(scores, SIZE, "results");
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
