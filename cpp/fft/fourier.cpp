#include<stdio.h>
#include<stdlib.h>  
#include<time.h>  
#include<math.h>  
#include<string.h>
#ifndef M_PI  
#define M_PI 3.14159265358979323846  
#endif  
#define SIZE 128 
#define VALUE_MAX 1000  
struct Complex_{
	double real;
	double imagin;
};
typedef struct Complex_ Complex;
void Add_Complex(Complex * src1, Complex *src2, Complex *dst){
	dst->imagin = src1->imagin + src2->imagin;
	dst->real = src1->real + src2->real;
}
void Sub_Complex(Complex * src1, Complex *src2, Complex *dst){
	dst->imagin = src1->imagin - src2->imagin;
	dst->real = src1->real - src2->real;
}
void Multy_Complex(Complex * src1, Complex *src2, Complex *dst){
	double r1 = 0.0, r2 = 0.0;
	double i1 = 0.0, i2 = 0.0;
	r1 = src1->real;
	r2 = src2->real;
	i1 = src1->imagin;
	i2 = src2->imagin;
	dst->imagin = r1*i2 + r2*i1;
	dst->real = r1*r2 - i1*i2;
}
void Copy_Complex(Complex * src, Complex *dst){
	dst->real = src->real;
	dst->imagin = src->imagin;
}
int isBase2(int size_n){
	int k = size_n;
	int z = 0;
	while (k /= 2) {
		z++;
	}
	k = z;
	if (size_n != (1 << k))
		return -1;
	else
		return k;
}
void Show_Complex(Complex * src, int size_n){
	if (size_n == 1){
		if (src->imagin >= 0.0)
			printf("%lf+%lfj  ", src->real, src->imagin);
		else
			printf("%lf%lfj  ", src->real, src->imagin);

	}
	else if (size_n>1){
		for (int i = 0; i<size_n; i++)
			if (src[i].imagin >= 0.0){
				printf("%lf+%lfj  ", src[i].real, src[i].imagin);
			}
			else
				printf("%lf%lfj  ", src[i].real, src[i].imagin);
	}
}
void getWN(double n, double size_n, Complex * dst){
	double x = 2.0*M_PI*n / size_n;
	dst->imagin = -sin(x);
	dst->real = cos(x);
}
void setInput(double * data, int  n){
 
	srand((int)time(0));
	for (int i = 0; i<SIZE; i++){
		data[i] = rand() % VALUE_MAX;
	
	}

}
void setInputSin(double *data, int n)
{
	double f1 = 100e6;
	double fs = 1e10;
	for (int i = 0; i < n; i++)
	{
		data[i] = sin(2 * M_PI*f1 / fs*i);
	}
}
void setComplexInput(Complex *data, int n)
{
	srand((int)time(NULL));
	for (int i = 0; i < n; i++)
	{
		data[i].imagin = rand() % VALUE_MAX;
		data[i].real = rand() % VALUE_MAX;
	}
}
void DFT(double * src, Complex * dst, int size){
	clock_t start, end;
	start = clock();

	for (int m = 0; m<size; m++){
		double real = 0.0;
		double imagin = 0.0;
		for (int n = 0; n<size; n++){
			double x = M_PI * 2 * m*n;
			real += src[n] * cos(x / size);
			imagin += src[n] * (-sin(x / size));

		}
		dst[m].imagin = imagin;
		dst[m].real = real;

	}
	end = clock();
	printf("DFT use time :%lf for Datasize of:%d\n", (double)(end - start) / CLOCKS_PER_SEC, size);

}
void IDFT(Complex *src, Complex *dst, int size){
	
	for (int m = 0; m<size; m++){
		double real = 0.0;
		double imagin = 0.0;
		for (int n = 0; n<size; n++){
			double x = M_PI * 2 * m*n / size;
			real += src[n].real*cos(x) - src[n].imagin*sin(x);
			imagin += src[n].real*sin(x) + src[n].imagin*cos(x);

		}
		real /= SIZE;
		imagin /= SIZE;
		if (dst != NULL){
			dst[m].real = real;
			dst[m].imagin = imagin;
		}
		if (imagin >= 0.0)
			printf("%lf+%lfj\n", real, imagin);
		else
			printf("%lf%lfj\n", real, imagin);
	}
	

}
int FFT_remap(double * src, int size_n){

	if (size_n == 1)
		return 0;
	double * temp = (double *)malloc(sizeof(double)*size_n);
	for (int i = 0; i<size_n; i++)
		if (i % 2 == 0)
			temp[i / 2] = src[i];
		else
			temp[(size_n + i) / 2] = src[i];
	for (int i = 0; i<size_n; i++)
		src[i] = temp[i];
	free(temp);
	FFT_remap(src, size_n / 2);
	FFT_remap(src + size_n / 2, size_n / 2);
	return 1;

}
int FFTReal_remap(double * src, int size_n){

	if (size_n == 1)
		return 0;
	double * temp = (double *)malloc(sizeof(double)*size_n);
	for (int i = 0; i<size_n; i++)
		if (i % 2 == 0)
			temp[i / 2] = src[i];
		else
			temp[(size_n + i) / 2] = src[i];
	for (int i = 0; i<size_n; i++)
		src[i] = temp[i];
	free(temp);
	FFTReal_remap(src, size_n / 2);
	FFTReal_remap(src + size_n / 2, size_n / 2);
	return 1;

}
int FFTComplex_remap(Complex * src, int size_n){

	if (size_n == 1)
		return 0;
	Complex * temp = (Complex *)malloc(sizeof(Complex)*size_n);
	for (int i = 0; i<size_n; i++)
		if (i % 2 == 0)
			Copy_Complex(&src[i], &(temp[i / 2]));
		else
			Copy_Complex(&(src[i]), &(temp[(size_n + i) / 2]));
	for (int i = 0; i<size_n; i++)
		Copy_Complex(&(temp[i]), &(src[i]));
	free(temp);
	FFTComplex_remap(src, size_n / 2);
	FFTComplex_remap(src + size_n / 2, size_n / 2);
	return 1;

}
void FFT(Complex * src, Complex * dst, int size_n){

	int k = size_n;
	int z = 0;
	while (k /= 2) {
		z++;
	}
	k = z;
	if (size_n != (1 << k))
		exit(0);
	Complex * src_com = (Complex*)malloc(sizeof(Complex)*size_n);
	if (src_com == NULL)
		exit(0);
	for (int i = 0; i<size_n; i++){
		Copy_Complex(&src[i], &src_com[i]);
	}
	FFTComplex_remap(src_com, size_n);
	for (int i = 0; i<k; i++){
		z = 0;
		for (int j = 0; j<size_n; j++){
			if ((j / (1 << i)) % 2 == 1){
				Complex wn;
				getWN(z, size_n, &wn);
				Multy_Complex(&src_com[j], &wn, &src_com[j]);
				z += 1 << (k - i - 1);
				Complex temp;
				int neighbour = j - (1 << (i));
				temp.real = src_com[neighbour].real;
				temp.imagin = src_com[neighbour].imagin;
				Add_Complex(&temp, &src_com[j], &src_com[neighbour]);
				Sub_Complex(&temp, &src_com[j], &src_com[j]);
			}
			else
				z = 0;
		}

	}


	for (int i = 0; i<size_n; i++){
		Copy_Complex(&src_com[i], &dst[i]);
	}
	free(src_com);


}
void RealFFT(double * src, Complex * dst, int size_n){


	int k = size_n;
	int z = 0;
	while (k /= 2) {
		z++;
	}
	k = z;
	if (size_n != (1 << k))
		exit(0);
	Complex * src_com = (Complex*)malloc(sizeof(Complex)*size_n);
	if (src_com == NULL)
		exit(0);
	for (int i = 0; i<size_n; i++){
		src_com[i].real = src[i];
		src_com[i].imagin = 0;
	}
	FFTComplex_remap(src_com, size_n);
	for (int i = 0; i<k; i++){
		z = 0;
		for (int j = 0; j<size_n; j++){
			if ((j / (1 << i)) % 2 == 1){
				Complex wn;
				getWN(z, size_n, &wn);
				Multy_Complex(&src_com[j], &wn, &src_com[j]);
				z += 1 << (k - i - 1);
				Complex temp;
				int neighbour = j - (1 << (i));
				temp.real = src_com[neighbour].real;
				temp.imagin = src_com[neighbour].imagin;
				Add_Complex(&temp, &src_com[j], &src_com[neighbour]);
				Sub_Complex(&temp, &src_com[j], &src_com[j]);
			}
			else
				z = 0;
		}

	}


	for (int i = 0; i<size_n; i++){
		Copy_Complex(&src_com[i], &dst[i]);
	}
	free(src_com);

}
void IFFT(Complex * src, Complex * dst, int size_n){
	for (int i = 0; i<size_n; i++)
		src[i].imagin = -src[i].imagin;
	FFTComplex_remap(src, size_n);
	int z, k;
	if ((z = isBase2(size_n)) != -1)
		k = isBase2(size_n);
	else
		exit(0);
	for (int i = 0; i<k; i++){
		z = 0;
		for (int j = 0; j<size_n; j++){
			if ((j / (1 << i)) % 2 == 1){
				Complex wn;
				getWN(z, size_n, &wn);
				Multy_Complex(&src[j], &wn, &src[j]);
				z += 1 << (k - i - 1);
				Complex temp;
				int neighbour = j - (1 << (i));
				Copy_Complex(&src[neighbour], &temp);
				Add_Complex(&temp, &src[j], &src[neighbour]);
				Sub_Complex(&temp, &src[j], &src[j]);
			}
			else
				z = 0;
		}

	}
	for (int i = 0; i<size_n; i++){
		dst[i].imagin = (1. / size_n)*src[i].imagin;
		dst[i].real = (1. / size_n)*src[i].real;
	}
}
double* PowerPeriodogram(Complex* data, int datasize)
{
	double* out;
	out = (double*)malloc(sizeof(double)*datasize);
	for (int i = 0; i < datasize; i++)
	{
		out[i] = sqrt(data[i].real * data[i].real + data[i].imagin*data[i].imagin);
	}
	return out;
}
double* ReadRealData(char* filename, int datasize)
{
	FILE *fp;
	double *nump;	
	int count = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("\n\ncant open the file \n");
		return NULL;
	}
	nump = (double*)malloc(sizeof(double)*datasize);
	for (int i = 0; (!feof(fp)) && (i < datasize); i++)
	{
		fscanf(fp, "%lf,", &nump[i]);
		count++;
	}
	for (int i = count; i < datasize; i++)
	{
		nump[i] = 0;
	}

	fclose(fp);
	return nump;	
}
Complex* ReadComplexData(char* filename, int datasize)
{
	FILE *fp;
	Complex* complexp;
	int count = 0;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("\n\ncant open the file \n");
		return NULL;
	}
	complexp = (Complex*)malloc(sizeof(Complex)*datasize);
	for (int i = 0; (!feof(fp)) && (i < datasize); i++)
	{
		fscanf(fp, "%lf%lf%*c ", &complexp[i].real, &complexp[i].imagin);
		count++;
	}
	for (int i = count; i < datasize; i++)
	{
		complexp[i].real = 0;
		complexp[i].imagin = 0;
	}

	fclose(fp);
	return complexp;
}
int WriteFourierData(char* filename1, char* filename2, int datasize, Complex* com)
{
	FILE *fp1, *fp2;
	if (strcmp(filename1, filename2) == 0)
	{
		printf("\n\nwrong input, two same filename\n");
		return 1;
	}
	fp1 = fopen(filename1, "wt");//real abs
	fp2 = fopen(filename2, "wt");//complex data
	for (int i = 0; i < datasize; i++)
	{
		fprintf(fp1, "%lf ", sqrt(com[i].imagin*com[i].imagin + com[i].real*com[i].real));
		if (com[i].imagin >= 0)
		{
			fprintf(fp2, "%lf+%lfi ", com[i].real, com[i].imagin);
		}
		else
		{
			fprintf(fp2, "%lf%lfi ", com[i].real, com[i].imagin);
		}
	}

	fclose(fp1);
	fclose(fp2);
	return 0;
}
int WriteTheRealData(char* filename, int datasize, double *data)
{
	FILE *fp;
	fp = fopen(filename, "wt");
	if (fp == NULL)
	{
		printf("\n\nerror!\n");
		return 1;
	}
	for (int i = 0; i < datasize; i++)
	{
		fprintf(fp, "%lf ", data[i]);
	}
	fclose(fp);
	return 0;
}
void FreeRealData(double *nump)
{
	free(nump);
}
void FreeComplexData(Complex *p)
{
	free(p);
}
double randnu(long *iseed)
{
	double z;
	*iseed = 2045 * (*iseed) + 1;
	*iseed = *iseed - (*iseed / 1048576) * 1048576;
	z = (double)((*iseed + 1) / 1048577.0);
	return(z);
}
void meavar(double u[], int *n, double *pum, double *puv)
{
	int i, k;
	*pum = 0.0;
	for (k = 0; k<*n; k++)
		*pum = *pum + u[k];
	*pum = *pum / (*n);
	*puv = 0.0;
	for (i = 0; i<*n; i++)
		*puv = *puv + pow((u[i] - *pum), 2);
	*puv = *puv + pow((u[i] - *pum), 2);
	*puv = *puv / (*n - 1.);
	return;
}
void mrandom(double u[], int *n, long *piseed, int itype, double p)
{
	int k, ns, ksection, ks, j;
	double a, v, umean, uvari;
	double *pum, *puv;
	pum = &umean;
	puv = &uvari;
	if (itype >6 || itype <1)
		return;
	for (k = 0; k<*n; k++)
		u[k] = randnu(piseed);
	if (itype == 2 || itype == 3)
	{
		meavar(u, n, pum, puv);
		/* to obtain a zero mean and P-power random sequence u[k]).*/
		a = 12.;
		if (itype == 2)
			p = sqrt(a);
		if (itype == 3)
			p = sqrt(p*a);
		for (k = 0; k<*n; k++)
			u[k] = (u[k] - umean)*p;

	}
	if (itype == 4 || itype == 5)
	{
		/* to generate the Gaussian randow sequence u[k],k=0,1,2,...,ns-1*/
		ksection = 12;
		ns = *n / ksection;
		ks = 0;
		if (itype == 4) p = 1;
		p = sqrt(p);
		for (k = 0; k<ns; k++)
		{
			v = 0.0;
			for (j = 0; j<ksection; j++)
				v += p*(u[j + ks] - .5);
			u[k] = v;
			ks = ks + ksection;
		}
		*n = ns;
	}
	meavar(u, n, pum, puv);
	printf("   The mean     of u[n]=%lf\n", umean);
	printf("   The variance of u[n]=%lf\n", uvari);
	return;
}
int main(int argc, const char * argv[]) {
	//double input[SIZE];
	//Complex dst[SIZE];
	/*setInput(input, SIZE);
	for (int i = 0; i < 128; i++)
		printf("\n%lf", input[i]);
	printf("\n\n");
	DFT(input, dst, SIZE);
	printf("\n\n");
	RealFFT(input, dst, SIZE);
	IDFT(dst, NULL, SIZE);
	WriteFourierData("t1.txt", "t2.txt", SIZE, dst);*/

	double* testsin = NULL;
	double* backtest = NULL;
	double* out = NULL;
	Complex* dst = NULL;
	dst = (Complex*)malloc(sizeof(Complex) * 1024);
	testsin = (double*)malloc(sizeof(double) * 1024);
	setInputSin(testsin, 1024);
	WriteTheRealData("sin.txt", 1024, testsin);
	backtest = ReadRealData("backsin.txt",1024);
	RealFFT(backtest, dst, 1024);
	out = PowerPeriodogram(dst, 1024);
	WriteTheRealData("backmat.txt", 1024, out);

	FreeRealData(out);
	FreeRealData(backtest);
	FreeRealData(testsin);
	free(dst);

	printf("\nfinish\n\n");
	getchar();
}