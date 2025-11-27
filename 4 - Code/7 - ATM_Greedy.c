#include <stdio.h>
#include <string.h>
#include <malloc.h>

/* ================== INIT ================== */
typedef struct
{
	char TenTien[25];
	int MG, PA; // Menh gia, Phuong an
} Tien;

/* ================== READ & PRINT ================== */
Tien* ReadFromFile(int* n)
{
	FILE* f = fopen("D:\\CODE C\\InputAlgo\\ATM.txt", "r");
	Tien* dslt = (Tien*) malloc(sizeof(Tien));
	
	int i = 0;
	while (!feof(f))
	{
		fscanf(f, "%d%[^\n]", &dslt[i].MG, &dslt[i].TenTien);
		dslt[i].PA = 0;
		i++;
		dslt = (Tien*) realloc(dslt, sizeof(Tien) * (i+1));
	}
	*n = i;
	fclose(f);
	return dslt;
}
void InDS(Tien* dslt, int n, int TienCanRut)
{
	int i;
	int TongTienTra = 0;
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("|%-3s|%-25s|%-9s|%-9s|%-10s|\n", "STT", "   Loai tien ",
	"Menh Gia", "So to","Thanh tien");
	printf("|---|-------------------------|---------|---------|----------|\n");
	for (i=0;i<n;i++)
	{
		if (dslt[i].PA != 0)
		{
			printf("|%-3d", i+1);
			printf("|%-25s", dslt[i].TenTien);
			printf("|%-9d",dslt[i].MG);
			printf("|%-9d",dslt[i].PA);
			printf("|%-10d|\n",dslt[i].MG*dslt[i].PA);
       		TongTienTra=TongTienTra+dslt[i].PA * dslt[i].MG;
		}
		else
		{
			continue;
		}
	}
	
	printf("|---|-------------------------|---------|---------|----------|\n");
	printf("So tien can rut= %9d\n", TienCanRut);
	printf("So tien da tra= %9d\n", TongTienTra);
	
}

/* ================== SORT ================== */
void swap(Tien* x, Tien* y)
{
	Tien tmp =  *y;
	*y = *x;
	*x = tmp;
}
void BubbleSort(Tien* dslt, int n)
{
	int i,j;
	for (i = 0; i < n-2;i++)
	{
		for (j = n-1; j >= i+1; j--)
			if (dslt[j].MG > dslt[j-1].MG)
				swap(&dslt[j], &dslt[j-1]);
	}
}

/* ================== GREEDY ================== */
void Greedy(Tien* dslt, int n, int TienCanRut)
{
	int i = 0;
	while (i<n && TienCanRut > 0)
	{
		dslt[i].PA = TienCanRut/dslt[i].MG;
		TienCanRut = TienCanRut-dslt[i].PA * dslt[i].MG;
		i++;
	}
}

/* ================== MAIN ================== */
int main()
{
	int n;
	int TienCanRut;
	printf("Nhap so tien can rut: ");
	scanf("%d", &TienCanRut);
	Tien* dslt;
	dslt = ReadFromFile(&n);
	
	BubbleSort(dslt, n);
	Greedy(dslt, n, TienCanRut);
	
	InDS(dslt, n, TienCanRut);
	
	free(dslt);
	return 0;	
}
