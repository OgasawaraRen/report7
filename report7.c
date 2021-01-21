#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printScores(int[], int, char[]);
void quickSort(int *, int, int);
int getPivot(int *, int, int);
int findPivotValOrHigher(int *, int, int, int);
int findPivotValOrLower(int *, int, int, int);
void swap(int *, int, int);

int main()
{
    const int SIZE = 5; //定数として配列のサイズを宣言
    int scores[SIZE] = {0, 60, 70, 100, 90};
    //処理コード
    srand((unsigned int)time(NULL));
    printScores(scores, SIZE, "scores");
    quickSort(scores, 0, SIZE - 1);
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

void swap(int *array, int a, int b)
{
    int tmp = *(array + a);
    *(array + a) = *(array + b);
    *(array + b) = tmp;
}

int getPivot(int *array, int min, int max)
{
    //配列から要素をランダムに3つ選び、その中央値を返す
    int vals[3];
    vals[0] = *(array + ((rand() % (max - min + 1)) + min));
    vals[1] = *(array + ((rand() % (max - min + 1)) + min));
    vals[2] = *(array + ((rand() % (max - min + 1)) + min));

    int i;
    for (i = 1; i < 3; i++)
    {
        if (vals[0] < vals[i])
        {
            swap(vals, 0, i);
        }
    }
    if (vals[1] < vals[2])
    {
        swap(vals, 1, 2);
    }
    return vals[1];
}

int findPivotValOrHigher(int *array, int leftEnd, int right, int pivot)
{
    //start:right  end:左端
    int index = right;

    int *p;
    for (p = array + right; p >= array; p--)
    {
        if (pivot <= *p) //ピボット以上の値を見つけたらその位置を返す
        {
            return index;
        }
        index--;
    }
    return -1;
}

int findPivotValOrLower(int *array, int left, int rightEnd, int pivot)
{
    //start:left  end:右端
    int index = left;
    int *p;
    for (p = array + left; p <= array + rightEnd; p++)
    {
        if (pivot >= *p) //ピボット以下の値を見つけたらその位置を返す
        {
            return index;
        }
        index++;
    }
    return -1;
}

void quickSort(int *array, int left, int right)
{
    if (left == right || left > right)
    {
        return;
    }

    int pivot = getPivot(array, left, right);
    int moveLeft = left;
    int moveRight = right;
    int swapCount = 0;

    while (1)
    {
        int beforeSwapLeft = -1;
        int beforeSwapRight = -1;

        beforeSwapLeft = findPivotValOrLower(array, moveLeft, right, pivot);   //pivot以下を左から探す
        beforeSwapRight = findPivotValOrHigher(array, left, moveRight, pivot); //pivot以上を右から探す

        if (beforeSwapLeft < beforeSwapRight)
        {
            //位置を保存
            moveLeft = beforeSwapLeft + 1;
            moveRight = beforeSwapRight - 1;

            swap(array, beforeSwapLeft, beforeSwapRight);
            swapCount++;
        }
        else
        {
            if (swapCount != 0)
            {
                quickSort(array, left, beforeSwapRight);
                quickSort(array, beforeSwapLeft, right);
            }
            return;
        }
    }
}
