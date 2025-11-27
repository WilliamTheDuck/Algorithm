#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MAX 100
typedef struct
{
    char TenDV[50];
    
    int TL, GT, SL, PA;
} DoVat;
typedef int bang[MAX][MAX];
void read(DoVat ds[], int* W, int* n)
{
    FILE* f= fopen("D:\\CODE C\\InputAlgo\\CaiBalo2.txt","r");
    fscanf(f,"%d",W);
    if (f==NULL)exit(1);
    int i =0;
    while(!feof(f))
    {
        fscanf(f,"%d%d%d%[^\n]", &ds[i].TL, &ds[i].GT, &ds[i].SL, &ds[i].TenDV);
        i++;
    }
    *n = i;
    fclose(f);
}
void print(DoVat ds[], int n, int W)
{
    int i,TTL=0,TGT=0;
    printf("\nPhuong An Cai Balo dung Quy Hoach Dong:\n");
    printf("|---|------------------|----------|---------|------------|-----------|\n");
    printf("|STT|     Ten Do Vat   | T Luong  | Gia Tri |  So luong  | Phuong an |\n");
    printf("|---|------------------|----------|---------|------------|-----------|\n");
    for(i=0;i<n;i++)
    {
        printf("|%2d |%-18s|%5d     |%5d    |%7d     |%6d     |\n",                 
		i+1,ds[i].TenDV,ds[i].TL,ds[i].GT, ds[i].SL, ds[i].PA);
		TTL += ds[i].PA * ds[i].TL;
		TGT += ds[i].PA * ds[i].GT;
	}
    printf("|---|------------------|----------|---------|------------|-----------|\n");	
	printf("Trong luong cua ba lo = %-9d\n",W);
	printf("Tong trong luong = %-9d\n",TTL);
	printf("Tong gia tri = %-9d\n",TGT);
}

void taoBang(DoVat ds[], int n, int W, bang F, bang X)
{
    int xk, yk, k;
    int FMax, XMax, V;

    for(V=0; V<=W; V++)
    {
        X[0][V] = V/ds[0].TL;
        F[0][V] = X[0][V]*ds[0].GT;
    }
    for (k=1;k<n;k++)
    {
        for (V=0;V<=W;V++)
        {
            // Chon Fmax trong cac F
            FMax = F[k-1][V];
            XMax = 0;
            yk = V/ds[k].TL;
            if (yk > ds[k].SL) yk = ds[k].SL;
            // xk:0->yk (yk la so luong toi da)
            for (xk=1;xk<=yk;xk++)
            {
                // cong thuc truy hoi
                // F = TGT (tinh qua tung DoVat)
                // F(max) = F[dong tren][TL còn lại] + gtr ô hiện tại
                // TL còn lại ,cập nhật :V = V - xk*GT
                if (F[k-1][V - xk*ds[k].TL] + xk*ds[k].GT > FMax)
                {
                    FMax = F[k-1][V - xk*ds[k].TL] + xk*ds[k].GT;
                    XMax= xk;
                }
            }
            // Gan gtr cho ô
            F[k][V] = FMax;
            X[k][V] = XMax;
        }
    }
}
void inBangF(int n, int W, bang F)
{
    int k,V;
    printf("Bang F:\n");
    for (k=0;k<n;k++)
    {
        for (V=0;V<=W;V++)
            printf("%4d",F[k][V]);
        printf("\n");
    }
}
void inBangX(int n, int W, bang X)
{
    int k,V;
    printf("Bang X:\n");
    for (k=0;k<n;k++)
    {
        for (V=0;V<=W;V++)
            printf("%4d",X[k][V]);
        printf("\n");
    }
}
void traBang(DoVat ds[], int n, int W, bang X)
{
    int k, V;
    // Truy ngược từ dòng cuối, cột cuối
    // Thêm vào PA
    V = W;
    for (k=n-1;k>=0;k--)
    {
        ds[k].PA = X[k][V];
        V -= X[k][V] * ds[k].TL; //giam TL V: W->ko thể bỏ thêm thêm đồ
    }
}

int main()
{
    int W,n;

    DoVat ds[MAX];
    read(ds, &W, &n);

    bang F, X;
    
    taoBang(ds,n,W,F,X);
    inBangF(n,W,F);
    inBangX(n,W,X);
    
    traBang(ds,n,W,X);
    print(ds,n,W);
}