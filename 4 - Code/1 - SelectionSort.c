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
    recordtype tmp = *x;
    *x = *y;
    *y = tmp;
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

/* ================== SELECTION SORT ================== */
/*  + for(forward)-for(forward)
    + O(n^2)
*/
void SelectionSort(recordtype a[], int n)
{
    // Declare lowindex & lowkey 
    int lowindex;
    keytype lowkey;
    // 1st-loop loops from start -> the key previous the last key
    for (int i = 0; i <= n-2; i++)
    {
        lowkey = a[i].key;
        lowindex = i;
        // 2nd-loop loops from the 1st-loop index (i) -> the last key
        // Find and mark the smallest key in this step
        for (int j = i + 1; j <= n-1; j++)
        {
            if (a[j].key < lowkey)
            {
                lowkey = a[j].key;
                lowindex = j;
            }
        }
        // Swap the current (j) with the smallest key
        swap(&a[i], &a[lowindex]);
    }
}

/* ================== MAIN ================== */
int main()
{
    recordtype a[MAX];
    int n;

    printf("Thuat toan Selection_Sort\n\n");
    Read_Data(a, &n);

    printf("Du lieu truoc khi sap xep:\n");
    Print_Data(a, n);

    SelectionSort(a, n);
    printf("Du lieu sau khi sap xep:\n");
    Print_Data(a, n);

    return 0;
}