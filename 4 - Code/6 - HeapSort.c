#include <stdio.h>

#define MAX 200

/* ================== INIT ================== */
typedef int keytype;
typedef float othertype;
typedef struct
{
    keytype key;
    othertype otherfields;
} recordtype;

void swap(recordtype* x, recordtype* y)
{
    recordtype tmp = *y;
    *y = *x;
    *x = tmp;
}

/* ================== READ & PRINT ================== */
void Read_Data(recordtype a[], int* n)
{
    FILE* f = fopen("D:\\LOCAL_GITHUB_REPOSITORIES\\Algorithm\\3 - Input Files\\sorting.txt", "r");
    int i = 0;
    if (f == NULL)
        return;
    while (!feof(f))
    {
        fscanf(f, "%d%f", &a[i].key, &a[i].otherfields);
        i++;
    }
    fclose(f);
    *n = i;
}
void Print_Data(recordtype a[], int n)
{
    // // Print descendingly
    // for (int i = 0; i < n; i++)
    //     printf("%3d%5d%8.2f\n",i+1,a[i].key,a[i].otherfields);
    // Print ascendingly
    for (int i = n-1; i >= 0; i--)
        printf("%3d%5d%8.2f\n",i+1,a[i].key,a[i].otherfields);
}

/* ================== HEAP SORT ================== */
void PushDown(recordtype a[], int first, int last) // O(logn)
{
    int r = first;
    while (r <= (last-1)/2)
    {
        if (last == 2*r + 1)
        {
            if (a[r].key > a[last].key)
                swap(&a[r], &a[last]);
            r = last;
        }
        else if (a[r].key > a[2*r+1].key && a[2*r+1].key <= a[2*r+2].key)
        {
            swap(&a[r], &a[2*r+1]);
            r = 2*r + 1;
        }
        else if (a[r].key > a[2*r+2].key && a[2*r+2].key < a[2*r+1].key)
        {
            swap(&a[r], &a[2*r+2]);
            r = 2*r + 2;
        }
        else
        {
            r = last;
        }
    }
}
void HeapSort(recordtype a[], int n) // O(nlogn)
{
    int i;
    for (i = (n-2)/2; i >= 0; i--)
        PushDown(a, i, n-1);
    for (i = n-1; i >=2; i--)
    {
        swap(&a[0], &a[i]);
        PushDown(a, 0, i-1);
    }
    swap(&a[0], &a[1]);
}

/* ================== MAIN ================== */
int main()
{
    recordtype a[MAX];
    int n;

    printf("Thuat toan Heap_Sort\n\n");
    Read_Data(a, &n);

    printf("Du lieu truoc khi sap xep:\n");
    Print_Data(a, n);

    HeapSort(a, n);
    printf("Du lieu sau khi sap xep:\n");
    Print_Data(a, n);

    return 0;
}