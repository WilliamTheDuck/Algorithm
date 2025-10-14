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

/* ================== INSERTION SORT ================== */
/*  + for(forward)-while(start at i, backward)
    + O(n^2)
*/
void InsertionSort(recordtype a[], int n)
{
    int i, j;
    for (i = 1; i <= n-1; i++)
    {
        j = i;
        // Keep swapping if the current key < the previous key 
        // In order to bring current record to appropriate position
        while (j > 0 && a[j].key < a[j-1].key)
        {
            swap(&a[j], &a[j-1]);
            j--;
        }
    }
}

/* ================== MAIN ================== */
int main()
{
    recordtype a[MAX];
    int n;

    printf("Thuat toan Insertion_Sort\n\n");
    Read_Data(a, &n);

    printf("Du lieu truoc khi sap xep:\n");
    Print_Data(a, n);

    InsertionSort(a, n);
    printf("Du lieu sau khi sap xep:\n");
    Print_Data(a, n);

    return 0;
}