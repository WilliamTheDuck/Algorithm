#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#define MAX 200

/* ================== INIT ================== */
typedef struct
{
    char TenDV[20];
    float GT, TL, DG;
    int PA;
} DoVat;

void swap(DoVat* x, DoVat* y)
{
    DoVat tmp = *x;
    *x = *y;
    *y = tmp;
}
void BubbleSort(DoVat* dsdv, int n)
{
    for (int i = 0; i <= n-2; i++)
        for (int j = n-1; j >= i+1; j--)
            if (dsdv[j].DG < dsdv[j-1].DG)
                swap(&dsdv[j], &dsdv[j-1]);
}

/* ================== READ & PRINT ================== */
DoVat* ReadFromFile(char s[], int* n, float* W)
{
    DoVat* dsdv;
    FILE* f = fopen(s, "r");

    fscanf(f,"%f", W); // Doc TL Balo
    dsdv = (DoVat*) malloc(sizeof(DoVat));
    
    int i = 0;
    while (!feof(f))
    {
        fscanf(f,"%f%f%19[^\n]", &dsdv[i].GT, &dsdv[i].TL, &dsdv[i].TenDV);
        dsdv[i].DG = dsdv[i].GT / dsdv[i].TL;
        dsdv[i].PA = 0;
        i++;
        dsdv = (DoVat*) realloc(dsdv, sizeof(DoVat) * (i+1));
    }
    *n = i;
    fclose(f);
    return dsdv;
}
void InDSDV(DoVat* dsdv, int n, float W)
{
    float TTL = 0.00, TGT = 0.00;
    printf("\nPhuong an Cai Ba lo 3 dung thuat toan NHANH CAN nhu sau:\n");
    printf("|---|--------------------|---------|---------|---------|-----------|\n");
	printf("|STT|     Ten Do Vat     |T. Luong | Gia Tri | Don gia | Phuong an |\n");
	printf("|---|--------------------|---------|---------|---------|-----------|\n");

    for (int i = 0; i < n; i++){
        printf("|%2d |%-20s|%9.2f|%9.2f|%9.2f|%6d     |\n",
		i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG, dsdv[i].PA);
		TTL += dsdv[i].PA * dsdv[i].TL;
		TGT += dsdv[i].PA * dsdv[i].GT;
    }
    printf("|---|--------------------|---------|---------|---------|-----------|\n");	
    printf("Phuong an (theo thu tu DG giam dan): X(");
	for(int i=0; i<n-1; i++){
		printf("%d,", dsdv[i].PA);
	}	
	printf("%d)\n", dsdv[n-1].PA);
	printf("Trong luong cua ba lo = %-9.2f\n",W);
	printf("Tong trong luong = %-9.2f\n",TTL);
	printf("Tong gia tri = %-9.2f\n",TGT);
}

/* ================== KNAPSACK_3 - BRANCH&BOUND ================== */
void init_root(float W, float* V, float* CT, float* GLNTT, float* TGT, float DG_Max)
{
    *TGT = 0.00;
    *V = W;
    *CT = *V * DG_Max;
    *GLNTT = 0.00;
}
void update_GLNTT(float TGT, float* GLNTT, int x[], DoVat* dsdv, int n)
{
    int i;
    if (*GLNTT < TGT)
    {
        *GLNTT = TGT;
        for (i = 0; i < n; i++)
            dsdv[i].PA = x[i];
    }
}
void NhanhCan(int i, float* TGT, float* CT, float* V, float* GLNTT, int x[], DoVat* dsdv, int n)
{
    int j, yk; // j: so vat dc chon, yk: so do vat max co the dc chon
    yk = (*V >= dsdv[i].TL) ? 1 : 0;

    // Xet tat ca kha nang co the phan nhanh theo so luong do vat
    // Cac kha nang trong khoang [0; yk], bat dau o j = yk de phan nhanh
    for (j = yk; j >= 0; j--)
    {
        // ung voi 1 j la 1 node
        // 3 dai luong
        *TGT += j * dsdv[i].GT;
        *V -= j * dsdv[i].TL;
        *CT = *TGT + *V * dsdv[i+1].DG; //dsdv[i+1].DG : do vat ke tiep cua do vat i

        // Truong Hop chua cat tia (ko phan nhanh)
        if (*CT > *GLNTT)
        {
            x[i] = j;
            // Neu da xet het DoVat hoac Balo day
            if ((i == n-1) || (*V == 0))
                update_GLNTT(*TGT, GLNTT, x, dsdv, n);
            else
                NhanhCan(i+1, TGT, CT, V, GLNTT, x, dsdv, n); // Xet nut con cua nut i

        }
    }
    // Backtracking (quay lui)
        x[i] = 0;
        *TGT -= j * dsdv[i].GT; // Tra lai TGT cua nut cha
        *V += j * dsdv[i].TL; // tra lai TTL cua nut cha
    
}

/* ================== MAIN ================== */
int main()
{
    float W, CT, TGT, V, GLNTT;
    int n;
    DoVat* dsdv = ReadFromFile("D:\\CODE C\\InputAlgo\\CaiBalo3.txt", &n, &W);

    int x[n]; // Phuong An tot nhat tam thoi

    BubbleSort(dsdv, n);
    init_root(W, &V, &CT, &GLNTT, &TGT, dsdv[0].DG);
    NhanhCan(0, &TGT, &CT, &V, &GLNTT, x, dsdv, n);
    InDSDV(dsdv, n, W);

    free(dsdv);
    return 0;
}




