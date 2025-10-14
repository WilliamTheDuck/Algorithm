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

/* ================== BUBBLE SORT ================== */
/*  + for(forward)-for(backward)
    + O(n^2)
*/
void BubbleSort(recordtype a[], int n)
{
    for (int i = 0; i <= n-2; i++)
        for (int j = n-1; j >= i+1; j--)
            if (a[j].key < a[j-1].key)
                swap(&a[j], &a[j-1]);
}

/* ================== MAIN ================== */
int main()
{
    recordtype a[MAX];
    int n;

    printf("Thuat toan Bubble_Sort\n\n");
    Read_Data(a, &n);

    printf("Du lieu truoc khi sap xep:\n");
    Print_Data(a, n);

    BubbleSort(a, n);
    printf("Du lieu sau khi sap xep:\n");
    Print_Data(a, n);

    return 0;
}