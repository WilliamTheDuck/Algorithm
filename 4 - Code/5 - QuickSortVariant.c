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
    for (int i = 0; i < n; i++)
        printf("%3d%5d%8.2f\n",i+1,a[i].key,a[i].otherfields);
}

/* ================== QUICK SORT ================== */
int FindPivot(recordtype a[], int i, int j) // O(n)
{
    keytype firstkey;
    int k;
    k = i + 1;
    firstkey = a[i].key;

    // Skip duplicate keys
    while ((k <= j) && (a[k].key == firstkey))
        k++;

    // Pick smaller key
    if (k > j)
        return -1;
    else 
    {
        if (a[k].key <= firstkey) 
            return k;
        else
            return i;
    }
}
int Partition(recordtype a[], int i, int j, keytype pivot) // O(n)
{
    int L, R;
    L = i;
    R = j;

    // Keep partitioning if L <= R
    while (L <= R)
    {
        // Move L to the right & R to the left (Notice that L <= p)
        while (a[L].key <= pivot) 
            L++;
        while (a[R].key > pivot)
            R--;
        if (L < R)  
            swap(&a[L], &a[R]);
    }
    return L; // Return partition point
}
void QuickSort(recordtype a[], int i, int j) // O(nlogn)
{
    keytype pivot;
    int pivotindex, k; // k = partition point

    // Find pivot -> Partition, return partition point -> Recurse Quick Sort for 2 sub arrays
    pivotindex = FindPivot(a, i, j);
    if (pivotindex != -1)
    {
        pivot = a[pivotindex].key;
        k = Partition(a, i, j, pivot);
        QuickSort(a, i, k-1);
        QuickSort(a, k, j);
    }
}

/* ================== MAIN ================== */
int main()
{
    recordtype a[MAX];
    int n;

    printf("Thuat toan Quick_Sort\n\n");
    Read_Data(a, &n);

    printf("Du lieu truoc khi sap xep:\n");
    Print_Data(a, n);

    int i = 0, j = n - 1;
    QuickSort(a, i, j);
    printf("Du lieu sau khi sap xep:\n");
    Print_Data(a, n);

    return 0;
}