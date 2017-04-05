//#include "stdafx.h"
//#include "plan.h"
#include "MinimumCostMaximumFlow.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

MinimumCostMaximumFlow::MinimumCostMaximumFlow(){}

MinimumCostMaximumFlow::~MinimumCostMaximumFlow(){}

int **MinimumCostMaximumFlow::iMatrix(int row, int col)
{
	int i;
	int ** iMatrix;
	iMatrix = (int**)malloc(row*sizeof(int*));
	for (i = 0; i < row; i++)
		iMatrix[i] = (int*)malloc(col*sizeof(int));
	return (iMatrix);

}

void MinimumCostMaximumFlow::freeiMatrux(int** iMatrix, int row)
{
	int i = row - 1;
	while (i >= 0)
		free(iMatrix[i--]);
	free(iMatrix);
}

double MinimumCostMaximumFlow::Min(double a, double b)
{
	double value;
	if (a < b) value = a;
	else value = b;
	return value;
}

double ** MinimumCostMaximumFlow::dMatrix(int row, int col)
{
	int i;
	double ** dMatrix;
	dMatrix = (double**)malloc(row*sizeof(double *));
	for (i = 0; i < row; i++)
		dMatrix[i] = (double *)malloc(col*sizeof(double));
	return (dMatrix);
}

void MinimumCostMaximumFlow::freedMatrix(double** dMatrix, int row)
{
	int i = row - 1;
	while (i >= 0) free(dMatrix[i--]);
	free(dMatrix);
}

void MinimumCostMaximumFlow::FreeAll()
{
	freedMatrix(C, n);
	freedMatrix(B, n);
	freedMatrix(W, n);
	freedMatrix(F, n);
	freedMatrix(U, n);
	freedMatrix(Capacity, n);
	freedMatrix(Cost, n);
	freeiMatrux(S, n);
	freeiMatrux(sign, n);

}

void MinimumCostMaximumFlow::inputdata()
{
	char mys[100];
	int i, j;
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	n = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	s = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	t = atoi(mys);
	C = dMatrix(n, n);
	B = dMatrix(n, n);
	W = dMatrix(n, n);
	F = dMatrix(n, n);
	U = dMatrix(n, n);
	S = iMatrix(n, n);

	Capacity = dMatrix(n, n);
	Cost = dMatrix(n, n);
	sign = iMatrix(n, n);

	fscanf(fp, "%s", mys);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			fscanf(fp, "%s", mys);
			if (strcmp(mys, "¡Þ") == 0)
				C[i][j] = infinity;
			else C[i][j] = atof(mys);
		}
	fscanf(fp, "%s", mys);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
		{
			fscanf(fp, "%s", mys);
			if (strcmp(mys, "¡Þ") == 0)
				B[i][j] = infinity;
			else B[i][j] = atof(mys);
		}
}

//new input

void MinimumCostMaximumFlow::inputdata2(char** topo, int linenum)
{
	int linknum, cusnum;
	int i, j;
	int x, y, width, cost;
	int textsign;

	sscanf(topo[0], "%d %d %d", &n, &linknum, &cusnum);

	C = dMatrix(n+2, n+2);
	B = dMatrix(n+2, n+2);
	W = dMatrix(n+2, n+2);
	F = dMatrix(n+2, n+2);
	U = dMatrix(n+2, n+2);
	S = iMatrix(n+2, n+2);

	Capacity = dMatrix(n+2, n+2);
	Cost = dMatrix(n+2, n+2);
	sign = iMatrix(n+2, n+2);

	s = n;
	t = n + 1;//begin at zero

	for (i = 0; i < n + 2; i++)
	{
		for (j = 0; i < n + 2; j++)
		{
			C[i][j] = 0;
			B[i][j] = infinity;
		}
		C[i][i] = infinity;
		B[i][i] = 0;
	}
	for (int i = 4; i < linknum; i++)
	{
		sscanf(topo[i], "%d %d %d %d", &x, &y, &width, &cost);
		C[x][y] = width;
		C[y][x] = width;
		B[x][y] = cost;
		B[y][x] = cost;
	}

	for (int i = linenum - cusnum, j = 0; i < linenum; i++, j++)
	{
		sscanf(topo[i], "%*d %d", &textsign);
		sscanf(topo[i], "%*d %*d %d", &C[n + 1][textsign]);
		C[textsign][n + 1] = C[n + 1][textsign];
		B[n + 1][textsign] = 0;	
		B[textsign][n + 1] = 0;
	}
	//change the B[n][] and C[n][] for test(this design the chromosome means the source link) set the point C to infinity B to 0 
}

void MinimumCostMaximumFlow::output()
{
	int i, j;

	MinValue = 0;
	fprintf(fp, "	The minmum cost maximum flow in transportation network is found as follow:\n");
	fprintf(fp, "arc low\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i != j && C[i][j] > 0)
			{
				fprintf(fp, " (%d,%d) %lf\n", i, j, F[i][j]);
				MinValue = MinValue + B[i][j] * F[i][j];
			}
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "	The cost found for minimum cost maximum is %lf\n", MinValue);
	FreeAll();

}

void MinimumCostMaximumFlow::InitializeFW()
{
	int i, j;
	for (i = 0; i < n;i++)
	{
		for (j = 0; j < n; j++)
		{
			F[i][j] = 0;
			W[i][j] = C[i][j];
		}
	}
}

void MinimumCostMaximumFlow::InitializeUS(double **x)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			U[i][j] = x[i][j];
			S[i][j] = j;
		}
	}
}

void MinimumCostMaximumFlow::SearchByMaxCapPath()
{
	int i, j, k;
	int l, r;
	double seta;

	for (;;)
	{
		InitializeUS(W);

		for (k = 0; k < n; k++)
		{
			for (i = 0; i < n; i++)
			{
				for (j = 0; j < n; j++)
				{
					if (U[i][j] < Min(U[i][k], U[k][j]))
					{
						U[i][j] = Min(U[i][k], U[k][j]);
						S[i][j] = S[i][k];
					}
				}
			}
		}
		if (U[s][t] == 0) break;
		else
		{
			seta = U[s][t];
			l = s;
			r = S[s][t];
			for (;;)
			{
				W[l][r] = W[l][r] - seta;
				W[r][l] = W[r][l] + seta;
				F[l][r] = F[l][r] + seta - Min(seta, F[r][l]);
				F[r][l] = F[r][l] - Min(seta, F[r][l]);
				if (r == t) break;
				else
				{
					l = r;
					r = S[r][t];
				}
			}
		}
	}
}

void MinimumCostMaximumFlow::ConstructCapCosMat()
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				Capacity[i][j] = infinity;
				Cost[i][j] = 0;
			}
			else
			{
				if (C[i][j] > 0)
				{
					if (C[j][i] == 0)
					{
						Capacity[i][j] = C[i][j] - F[i][j];
						Capacity[j][i] = F[i][j];
						if (F[i][j] < C[i][j])
						{
							Cost[i][j] = B[i][j];
							sign[i][j] = 1;
						}
						else
						{
							Cost[i][j] = infinity;
							sign[i][j] = 0;
						}
						if (F[i][j] > 0)
						{
							Cost[j][i] = -B[i][j];
							sign[j][i] = -1;
						}
						else
						{
							Cost[j][i] = infinity;
							sign[j][i] = 0;
						}
					}
					else
					{
						if (F[i][j] == 0 && F[j][i] > 0)
						{
							Capacity[j][i] = C[j][i] - F[j][i];
							Capacity[i][j] = F[j][i];
							Cost[i][j] = B[j][i];
							sign[i][j] = -1;
							if (F[j][i] < C[j][i])
							{
								Cost[j][i] = B[j][i];
								sign[j][i] = 1;
							}
							else
							{
								Cost[j][i] = infinity;
								sign[j][i] = 0;
							}
						}
						if (F[i][j] > 0 && F[j][i] == 0)
						{
							Capacity[i][j] = C[i][j] - F[i][j];
							Capacity[j][i] = F[i][j];
							Cost[j][i] = -B[i][j];
							sign[j][i] = -1;
							if (F[i][j]<C[i][j])
							{
								Cost[i][j] = B[i][j];
								sign[i][j] = 1;
							}
							else
							{
								Cost[i][j] = infinity;
								sign[i][j] = 0;
							}
						}
						if (F[i][j] == 0 && F[j][i] == 0)
						{
							Capacity[i][j] = C[i][j];
							Cost[i][j] = B[i][j];
							sign[i][j] = 1;
							Capacity[j][i] = C[j][i];
							Cost[j][i] = B[j][i];
							sign[j][i] = 1;
						}
					}
				}
				else
				{
					if (C[j][i] == 0)
					{
						Capacity[i][j] = 0;
						Cost[i][j] = infinity;
						sign[i][j] = 0;
						Capacity[j][i] = 0;
						Cost[j][i] = infinity;
						sign[j][i] = 0;
					}
					else
					{
						Capacity[j][i] = C[j][i] - F[j][i];
						Capacity[i][j] = F[j][i];
						if (F[j][i] < C[j][i])
						{
							Cost[j][i] = B[j][i];
							sign[j][i] = 1;
						}
						else
						{
							Cost[j][i] = infinity;
							sign[j][i] = 0;
						}
						if (F[j][i] > 0)
						{
							Cost[i][j] = -B[j][i];
							sign[i][j] = -1;
						}
						else
						{
							Cost[i][j] = infinity;
							sign[i][j] = 0;
						}
					}
				}
			}
		}
	}
}

double MinimumCostMaximumFlow::add(double x, double y)
{
	double value;
	if ((x == infinity) || (y == infinity)) value = infinity;
	else value = x + y;
	return value;
}

int MinimumCostMaximumFlow::NegativeCycleFound()
{
	int i, j, k;
	int value;
	InitializeUS(Cost);
	m = 0;
	for (k = 0; k < n - 1; k++)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (U[i][j]>add(U[i][k],U[k][j]))
				{
					U[i][j] = add(U[i][k], U[k][j]);
					S[i][j] = S[i][k];
				}
		for (i = k + 1; i < n;i++)
			if (U[i][i] < 0)
			{
				m = i;
				value = 1;
				return value;
			}
	}
	value = 0;
	return value;
}

void MinimumCostMaximumFlow::NegativeCycleAjust()
{
	int l, r;
	double seta;
	l = m;
	seta = infinity;
	for (;;)
	{
		r = S[l][m];
		if (seta > Capacity[l][r]) seta = Capacity[l][r];
		l = r;
		if (l == m) break;
	}
	l = m;
	for (;;)
	{
		r = S[l][m];
		if (sign[l][r] == 1) F[l][r] = F[l][r] + seta;
		else F[r][l] = F[r][l] - seta;
		l = r;
		if (l == m) break;
	}
}

void MinimumCostMaximumFlow::MaxFlow()
{
	InitializeFW();
	SearchByMaxCapPath();
}

void MinimumCostMaximumFlow::MinCostMaxFlow()
{
	MaxFlow();
	for (;;)
	{
		ConstructCapCosMat();
		if (NegativeCycleFound() == 1) NegativeCycleAjust();
		else break;
	}
}

void MinimumCostMaximumFlow::SetFilePointer(FILE *z)
{
	fp = z;
}

void main()
{
	MinimumCostMaximumFlow t1;
	FILE *ftest;
	ftest = fopen("ex1.txt", "rt");
	if (ftest == NULL)
		printf("wrong");
	t1.SetFilePointer(ftest);
	t1.inputdata();
	fclose(ftest);
	ftest = fopen("extestout.txt","w");
	t1.SetFilePointer(ftest);
	t1.MinCostMaxFlow();
	t1.output();
	fclose(ftest);

}