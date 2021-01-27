#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printScores(int[], int, char[]);

void quickSort(int *, int, int);
int getPivot(int *, int, int);
int findPivotValOrHigher(int *, int, int, int);
int findPivotValOrLower(int *, int, int, int);
void swap(int *, int, int);

void bogoSort(int *, int);
void shuffle(int *, int);
int orderCheck(int *, int);

void bucketSort(int *, int);

void compare(int *, int);
void copyArray(int *, int *, int);

int main()
{
    const int SIZE_A = 6; //定数として配列のサイズを宣言
    int scoresA[SIZE_A] = {100, 60, 70, 100, 90, 80};
    //処理コード
    printf("CPU時間を計測...\n\n");

    srand((unsigned int)time(NULL));
    printScores(scoresA, SIZE_A, "scoresA");
    compare(scoresA, SIZE_A);

    printf("\n");
    const int SIZE_B = 5;
    int scoresB[SIZE_B] = {10, 10, 20, 20, 30};
    printScores(scoresB, SIZE_B, "scoresB");
    compare(scoresB, SIZE_B);

    printf("\n");
    const int SIZE_C = 5;
    int scoresC[SIZE_C] = {5, 4, 3, 2, 1};
    printScores(scoresC, SIZE_C, "scoresC");
    compare(scoresC, SIZE_C);
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

void copyArray(int *baseArray, int *copyArray, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        copyArray[i] = baseArray[i];
    }
}

void compare(int *array, int size)
{
    //ソートにかかるCPU時間を計測

    int scores[size];
    int i;
    copyArray(array, scores, size);

    time_t start, end;
    double aveTime, sumTime = 0;
    int loopNum = 100;
    for (i = 0; i < loopNum; i++)
    {
        start = clock();
        quickSort(scores, 0, size - 1);
        end = clock();
        sumTime += (double)(end - start);
        copyArray(array, scores, size);
    }
    aveTime = sumTime / loopNum;
    sumTime = 0;

    printf("・クイックソート:%.3lf\n", aveTime);

    for (i = 0; i < loopNum; i++)
    {
        start = clock();
        bogoSort(scores, size);
        end = clock();
        sumTime += (double)(end - start);
        copyArray(array, scores, size);
    }
    aveTime = sumTime / loopNum;
    sumTime = 0;

    printf("・ボゴソート　　:%.3lf\n", aveTime);

    for (i = 0; i < loopNum; i++)
    {
        start = clock();
        bucketSort(scores, size);
        end = clock();
        sumTime += (double)(end - start);
        copyArray(array, scores, size);
    }
    aveTime = sumTime / loopNum;
    sumTime = 0;

    printf("・バケットソート:%.3lf\n", aveTime);
}

//クイックソート
void swap(int *array, int a, int b)
{
    int tmp = array[a];
    array[a] = array[b];
    array[b] = tmp;
}

int getPivot(int *array, int min, int max)
{
    //配列から要素をランダムに3つ選び、その中央値を返す
    int vals[3];
    vals[0] = array[(rand() % (max - min + 1)) + min];
    vals[1] = array[(rand() % (max - min + 1)) + min];
    vals[2] = array[(rand() % (max - min + 1)) + min];
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
    int i;
    for (i = right; i >= 0; i--)
    {
        if (pivot <= array[i]) //ピボット以上の値を見つけたらその位置を返す
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
    int i;
    for (i = left; i <= rightEnd; i++)
    {
        if (pivot >= array[i]) //ピボット以下の値を見つけたらその位置を返す
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

//ボゴソート
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

//バケットソート
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
        bucket[array[i]]++;
    }
    i = 0;
    int bucketNum = 100;
    while (i < size)
    {
        if (bucket[bucketNum] > 0)
        {
            array[i] = bucketNum;
            i++;
            bucket[bucketNum]--;
        }
        else
        {
            bucketNum--;
        }
    }
}