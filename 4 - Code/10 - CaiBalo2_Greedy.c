#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

/* ================== INIT ================== */
typedef struct {
	char TenDV[20];
	float TL, GT, DG;
	int SL, PA;
}DoVat;
void swap(DoVat *x, DoVat *y){
	DoVat Temp;
	Temp = *x;
	*x   = *y;
	*y   = Temp;
}
void BubbleSort(DoVat *dsdv, int n){
	int i,j;
	for(i=0; i<=n-2; i++)
	   for (j=n-1; j>=i+1; j--){
	   	 if (dsdv[j].DG>dsdv[j-1].DG) 
			swap(&dsdv[j],&dsdv[j-1]);
	  }   
}

/* ================== READ & PRINT ================== */
DoVat *ReadFromFile(float *W, int *n){
     FILE *f;
     f = fopen("D:\\CODE C\\InputAlgo\\CaiBalo2.txt", "r");
     fscanf(f, "%f",W); // Xac dinh trong luong Ba lo
	 DoVat *dsdv;
	 dsdv=(DoVat*)malloc(sizeof(DoVat));
	 int i=0;
 	 while (!feof(f)){
	   fscanf(f, "%f%f%d%[^\n]",&dsdv[i].TL, &dsdv[i].GT, &dsdv[i].SL, &dsdv[i].TenDV);
	   dsdv[i].DG=dsdv[i].GT/dsdv[i].TL;
	   dsdv[i].PA=0;
	   i++;
	   dsdv=(DoVat*)realloc(dsdv, sizeof(DoVat)*(i+1));  
	 }
	 *n=i;
     fclose(f);
     return dsdv;
}
void InDSDV(DoVat *dsdv, int n, float W){
	int i;
	float TongTL=0.0, TongGT=0.0;
	printf("\nPhuong an Cai Ba lo 1 dung thuat toan THAM AN nhu sau:\n");
	printf("\nTrong luong cua ba lo = %-9.2f\n",W);
	printf("|---|------------------|---------|---------|---------|----------|-----------|\n");
	printf("|STT|     Ten Do Vat   | T Luong | Gia Tri | Don Gia | So Luong | Phuong an |\n");
	printf("|---|------------------|---------|---------|---------|----------|-----------|\n");
	for(i=0;i<n;i++){
		printf("|%2d |%-18s|%9.2f|%9.2f|%9.2f| %9d|%6d     |\n",
		i+1,dsdv[i].TenDV,dsdv[i].TL,dsdv[i].GT,dsdv[i].DG,dsdv[i].SL,dsdv[i].PA);
		TongTL += dsdv[i].PA * dsdv[i].TL;
		TongGT += dsdv[i].PA * dsdv[i].GT;
	}	
	printf("|---|------------------|---------|---------|---------|----------|-----------|\n");	
	printf("Phuong an (theo thu tu DG giam dan): X(");
	for(i=0; i<n-1; i++){
		printf("%d,", dsdv[i].PA);
	}	
	printf("%d)", dsdv[n-1].PA);
	printf("\nTong trong luong = %-9.2f\n",TongTL);
	printf("Tong gia tri = %-9.2f\n",TongGT);
}

/* ================== KNAPSACK_2 - GREEDY ================== */
void Greedy(DoVat *dsdv,int n, float W){
  int i;
  for(i=0; i<n; i++) {
     dsdv[i].PA = fmin(W/dsdv[i].TL, dsdv[i].SL);
     W = W-dsdv[i].PA * dsdv[i].TL;
  }
}

/* ================== MAIN ================== */
int main(){
	int n;
	float W;
	DoVat *dsdv;
	
	dsdv=ReadFromFile(&W, &n);
    BubbleSort(dsdv,n);
	Greedy(dsdv,n,W);
	InDSDV(dsdv,n,W);
	
	free(dsdv);
	return 0;
}