#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define max 50 

/* ================== INIT ================== */
void init_triagle(int matrix[][max])
{
	for (int i = 0; i < max; i++)
		for (int j = 0; j <= i; j++)
			matrix[i][j] = 0;
}

/* ================== READ & PRINT ================== */
void read_data(int a[][max], int* n)
{
	FILE* f = fopen("D:\\CODE C\\InputAlgo\\TamGiacSo.txt", "r");
	if (f == NULL)	
	{
		printf("Cannot open file");
		return;
	}

	int i = 0, j;
	while(!feof(f))
	{
		for (j = 0; j <= i; j++)
		{
			fscanf(f, "%d", &a[i][j]);
		}
		i++;
	}
	*n = i;
	fclose(f);
}
void print_data(int a[][max], int n)
{
	printf("Tam giac so:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
}

/* ================== idx_max && idx_max_last_row ================== */
int idx_max(int F[][max], int i, int j)
{
	// 1. Column 0 (2 ways)
	if (j == 0)
		return F[i-1][0] > F[i-1][1] ? 0 : 1;
	// 2. Diagonal (1 way)
	if (j == i)
		return i-1;
	// 3. Inside diagonal (2 ways)
	if (j == i-1)
		return F[i-1][i-2] > F[i-1][i-1] ? i-2 : i-1;
	// 4. In the betweens/normal(3 ways) -> Pick max in three columns -> Check in pairs
	if (F[i-1][j-1] > F[i-1][j] && F[i-1][j-1] > F[i-1][j+1])
		return j-1;
	if (F[i-1][j] > F[i-1][j-1] && F[i-1][j] > F[i-1][j+1])
		return j;
	if (F[i-1][j+1] > F[i-1][j-1] && F[i-1][j+1] > F[i-1][j])
		return j+1;
}
int idx_max_last_row(int F[], int n)
{
	int maxtotal = F[0];
	int maxidx = 0;
	for (int k = 0; k < n; k++)
		if (F[k] > maxtotal)
		{
			maxtotal = F[k];
			maxidx = k;
		}
	return maxidx;
}

/* ================== MAKE TABLE ================== */
void make_table(int a[][max], int n, int F[][max])
{
	// 2 first rows
	F[0][0] = a[0][0];
	F[1][0] = F[0][0] + a[1][0];
	F[1][1] = F[0][0] + a[1][1];
	// Rows from third row to n-th row
	for (int i = 2; i < n; i++)
		for (int j = 0; j <= i; j++)
		{
			// i-th row = above row + present value
			F[i][j] = F[i-1][idx_max(F, i, j)] + a[i][j]; 
		}
}

/* ================== SEARCH TABLE ================== */
void search_table(int a[][max], int n, int F[][max], int PA[])
{
	int i;
	// Start at last row, column that is max
	int j = idx_max_last_row(F[n-1], n-1);
	PA[n-1] = a[n-1][j];

	// Trace back to the top
	for (i = n-1; i >= 1; i--)
	{
		j = idx_max(F, i, j);
		PA[i-1] = a[i-1][j]; // Trace back the row above
	}
}

/* ================== ANSWER ================== */
int GiaPA(int PA[], int n)
{
	int price = 0;
	for (int i = 0; i < n; i++)
		price += PA[i];
	return price;
}
void print_table(int F[][max], int n)
{
	printf("Bang F:\n");
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <= i; j++)
			printf("%5d", F[i][j]);
		printf("\n");
	}
}
void print_PA(int PA[], int n)
{
	printf("PA is path: \n");
	printf("%d", PA[0]);
	for (int i = 1; i < n; i++)
		printf(" => %d", PA[i]);
	printf("\nPrice of the answer = %d\n", GiaPA(PA, n));
}

/* ================== MAIN ================== */
int main()
{
	printf("Bai toan TAM GIAC SO dung thuat toan QUY HOACH DONG\n");
	int a[max][max], n;
	init_triagle(a);
	read_data(a, &n);
	print_data(a, n);

	int F[max][max], PA[max];
	init_triagle(F);
	make_table(a, n, F);
	print_table(F, n);

	search_table(a, n, F, PA);
	print_PA(PA, n);

	return 0;
}