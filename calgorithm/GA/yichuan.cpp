#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "afx.h"
const int infinity = 1000000000;
int I, J, K, L;
int w, p;
int *a, *b, *c, *d, *F, *G, *W, *Z;
int **s, **t, **u, **x, **y, **z;
int ***chromopopulation, ***chromopopu, ***chromopopul;
int *evaluation;
double pc, pm;
int maxgen, popsize;
FILE *fp;
CStdioFile f;

int random(int imin, int imax)
{
	int var_x, var_y, var_r;
	var_x = rand();
	var_y = var_x / (imax - imin + 1);
	var_r = var_x - (imax - imin + 1)*var_y;
	var_r = var_r + imin;
	return var_r;
}

int ***chromopop(int pop_size)
{
	int ***chromopop;
	chromopop = (int***)malloc((pop_size + 1)*sizeof(int**));
	return (chromopop);
}

void freechromopop(int *** chromopop,int pop_size,int segmentnum)
{
	int k, i;
	for (k = pop_size; k >= 1; i--)
	{
		for (i = segmentnum; i >= 1; i--) delete (int*)chromopop[k][i];
		delete (int**)chromopop[k];
	}
	delete chromopop;
}

int ** chromo(int segmentnum)
{
	int ** chromo;
	chromo = (int**)malloc((segmentnum + 1)*sizeof(int *));
	return (chromo);
}

void freechromo(int ** chromo, int segmentnum)
{
	int i;
	for (i = segmentnum; i >= 1; i--) free(chromo[i]);
	free(chromo);
}

void pseudofreechromo(int** chromosome, int segmentnum)
{
	int i;
	for (i = segmentnum; i >= 1; i--) free(chromosome[i]);
}

int** iMatrix(int row, int col)
{
	int i;
	int ** iMatrix;
	iMatrix = (int**)malloc((row + 1)*sizeof(int *));
	for (i = 0; i < row + 1; i++)
		iMatrix[i] = (int*)malloc((col + 1)*sizeof(int));
	return (iMatrix);
}

void freeiMatrix(int** iMatrix, int row)
{
	int i = row;
	while (i >= 0) free(iMatrix[i--]);
	free(iMatrix);
}

int * iVector(int num)
{
	int * iVector;
	iVector = (int*)malloc((num + 1)*sizeof(int));
	return (iVector);
}

int belong(int var, int imin, int imax)
{
	if (var >= imin && var <= imax) return 1;
	else return 0;
}

void feasibleprufer(int * PruferNum, int m, int n)
{
	int* degree;
	int i, k, sum1, sum2;
	degree = iVector(m + n);
	for (i = 1; i <= m + n; i++)
	{
		degree[i] = 0;
		for (k = 1; k <= m + n - 2; k++)
			if (PruferNum[k] == i)
				degree[i] = degree[i] + 1;
		degree[i] = degree[i] + 1;
	}
	sum1 = 0;
	for (i = 1; i <= m; i++)
		sum1 = sum1 + degree[i];
	sum2 = 0;
	for (i = m + 1; i <= m + n; i++)
		sum2 = sum2 + degree[i];
	while (sum1 != sum2)
	{
		if (sum1 > sum2)
		{
			for (k = 1; k = m + n - 2;k++)
				if (belong(PruferNum[k], 1, m))
				{
					PruferNum[k] = random(m + 1, m + n);
					break;
				}
			sum1 = sum1 - 1;
			sum2 = sum2 + 1;
		}
		else
		{
			for (k = 1; k <= m + n - 2;k++)
				if (belong(PruferNum[k], m + 1, m + n))
				{
					PruferNum[k] = random(1, m);
					break;
				}
			sum1 = sum1 + 1;
			sum2 = sum2 - 1;
		}
	}
	free(degree);
}

int * PruferNum(int m, int n)
{
	int* PruferNum;
	int i;
	PruferNum = iVector(m + n - 2);
	for (i = 1; i <= m + n - 2; i++)
		PruferNum[i] = random(1, m + n);
	feasibleprufer(PruferNum, m, n);
	return (PruferNum);
}

int smallest(int* PathBar, int m, int n)
{
	int i, minimum, k;
	minimum = infinity;
	for (i = 1; i <= m + n;i++)
		if (PathBar[i] < minimum)
		{
			minimum = PathBar[i];
			k = i;
		}
	return k;
}

int biggest(int* PathBar, int m, int n)
{
	int i, maximum, k;
	maximum = -infinity;
	for (i = 1; i <= m + n;i++)
		if (PathBar[i] > maximum)
		{
			maximum = PathBar[i];
			k = i;
		}
	return k;
}

int insameset(int var_x, int var_y, int m, int n)
{
	if (belong(var_x, 1, m) && belong(var_y, 1, m)) return 1;
	else if (belong(var_x, m + 1, m + n) && belong(var_y, m + 1, m + n)) return 1;
	else return 0;
}

int leftmost(int* Path, int m, int n, int var_x)
{
	int k, num;
	num = 0;
	for (k = 1; k <= m + n - 2;k++)
		if (Path[k] != 0 && insameset(Path[k], var_x, m, n) != 1)
		{
			num = k;
			break;
		}
	return num;
}

int rightmost(int* Path, int m, int n, int var_x)
{
	int k, num;
	num = 0;
	for (k = m + n - 2; k >= 1;k--)
		if (Path[k] != 0 && insameset(Path[k], var_x, m, n) != 1)
		{
			num = k;
			break;
		}
	return num;
}

int maxinset(int* value, int num)
{
	int i, k, maxnum;
	maxnum = value[1];
	k = 1;
	for (i = 2; i <= num; i++)
		if (maxnum < value[i])
		{
			maxnum = value[i];
			k = i;
		}
	return k;
}

int appear(int* Path, int m, int n, int var_x)
{
	int k, value;
	value = 0;
	for (k = 1; k <= m + n - 2;k++)
		if (Path[k] == var_x)
		{
			value = 1;
			break;
		}
	return value;
}

void putin(int* PathBar, int m, int n, int var_x)
{
	int i;
	for (i = 1; i <= m + n;i++)
		if (PathBar[i] == infinity)
		{
			PathBar[i] = var_x;
			break;
		}
}

void putincounter(int* PathBar, int m, int n, int var_x)
{
	int i;
	for (i = 1; i <= m + n;i++)
		if (PathBar[i] == -infinity)
		{
			PathBar[i] = var_x;
			break;
		}
}

void ShortestPath(int** distance, int** succession, int nodenum)
{
	int i, j, k;
	for (i = 1; i <= nodenum; i++)
		for (j = 1; j <= nodenum; j++)
			succession[i][j] = j;
	for (k = 1; k <= nodenum; k++)
		for (i = 1; i <= nodenum; i++)
			for (j = 1; j <= nodenum;j++)
				if (distance[i][j] > distance[i][k] + distance[k][j])
				{
					distance[i][j] = distance[i][k] + distance[k][j];
					succession[i][j] = succession[i][k];
				}
}

void decode(int* Path, int m, int n, int* var_a, int* var_b, int** var_x)
{
	int *PathBar, i, j, k, l, r, starting, terminal, temp, iteration, row, col;
	int **connexion, **distance, **succession, *degree;
	PathBar = iVector(m + n);
	for (i = 1; i <= m + n; i++)
	{
		PathBar[i] = i;
		for (k = 1; k <= m + n - 2;k++)
			if (Path[k] == PathBar[i])
			{
				PathBar[i] = infinity;
				break;
			}
	}
	connexion = iMatrix(m + n, m + n);
	for (i = 1; i <= m + n; i++)
		for (j = 1; j <= m + n; j++)
		{
			if (i == j) connexion[i][j] = 0;
			else connexion[i][j] = infinity;
		}
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++)
			var_x[i][j] = 0;
	distance = iMatrix(m + n, m + n);
	succession = iMatrix(m + n, m + n);
	for (iteration = 1; iteration <= m + n - 2; iteration++)
	{
		l = smallest(PathBar, m, n);
		r = leftmost(Path, m, n, PathBar[l]);
		if (belong(PathBar[l], l, m))
		{
			if (var_a[PathBar[l]] < var_b[Path[r] - m])
				var_x[PathBar[l]][Path[r] - m] = var_a[PathBar[l]];
			else
				var_x[PathBar[l]][Path[r] - m] = var_b[Path[r] - m];
			var_a[PathBar[l]] = var_a[PathBar[l]] - var_x[PathBar[l]][Path[r] - m];
			var_b[Path[r] - m] = var_b[Path[r] - m] - var_x[PathBar[l]][Path[r] - m];
			connexion[PathBar[l]][Path[r]] = 1;
			connexion[Path[r]][PathBar[l]] = 1;
		}
		else
		{
			if (var_a[Path[r]] < var_b[PathBar[l] - m]) var_x[Path[r]][PathBar[l] - m] = var_a[Path[r]];
			else var_x[Path[r]][PathBar[l] - m] = var_b[PathBar[l] - m];
			var_a[Path[r]] = var_a[Path[r]] - var_x[Path[r]][PathBar[l] - m];
			var_b[PathBar[l] - m] = var_b[PathBar[l] - m] - var_x[Path[r]][PathBar[l] - m];
			connexion[Path[r]][PathBar[l]] = l;
			connexion[PathBar[l]][Path[r]] = l;
		}
		PathBar[l] = infinity;
		temp = Path[r];
		Path[r] = 0;
		if (appear(Path, m, n, temp) == 0) putin(PathBar, m, n, temp);
	}
	for (i = 1; i <= m + n;i++)
		if (PathBar[i] != infinity)
		{
			l = PathBar[i];
			PathBar[i] = infinity;
			break;
		}
	for (i = 1; i <= m + n; i++)
	{
		r = PathBar[i];
		break;
	}
	if (belong(l, 1, m))//be caution the '1' and 'l'
	{
		if (var_a[l] < var_b[r - m]) var_x[l][r - m] = var_a[l];
		else var_x[l][r - m] = var_b[r - m];
		var_a[l] = var_a[l] - var_x[l][r - m];
		var_b[r - m] = var_b[r - m] - var_x[l][r - m];
		connexion[l][r] = 1;
		connexion[r][l] = 1;
	}
	else
	{
		if (var_a[r] < var_b[l - m]) var_x[r][l - m] = var_a[r];
		else var_x[r][l - m] = var_b[l - m];
		var_a[r] = var_a[r] - var_x[r][l - m];
		connexion[r][l] = 1;
		connexion[l][r] = 1;
	}
	for (;;)
	{
		for (i = 1; i <= m + n; i++)
			for (j = 1; j <= m + n; j++)
				distance[i][j] = connexion[i][j];
		ShortestPath(distance, succession, m + n);
		l = maxinset(var_a, m);
		if (var_a[l] != 0)
		{
			r = maxinset(var_b, n);
			if (var_a[l] < var_b[r]) var_x[l][r] = var_a[l];
			else var_x[l][r] = var_b[r];
			var_a[l] = var_a[l] - var_x[l][r];
			var_b[r] = var_b[r] - var_x[l][r];
			starting = l;
			terminal = m + r;
			r = succession[starting][terminal];
			for (;;)
			{
				if (var_x[l][r - m] == 0)
				{
					connexion[l][r] = infinity;
					connexion[r][l] = infinity;
					break;
				}
				else
				{
					if (r == terminal) break;
					l = r;
					r = succession[r][terminal];
					if (var_x[r][l - m] == 0)
					{
						connexion[r][l] = infinity;
						connexion[l][r] = infinity;
						break;
					}
					else
					{
						l = r;
						r = succession[r][terminal];
					}
				}
			}
			connexion[starting][terminal] = 1;
			connexion[terminal][starting] = 1;
		}
		else break;
	}
	for (i = 1; i <= m + n; i++)
		for (j = 1; j <= m + n; j++)
			if (connexion[i][j] == infinity)
				connexion[i][j] = 0;
	degree = iVector(m + n);
	for (k = 1; k <= m + n - 2; k++)
	{
		for (i = 1; i <= m + n; i++)
		{
			degree[i] = 0;
			for (j = 1; j <= m + n; j++)
				degree[i] += connexion[i][j];
			if (degree[i] == 1)
			{
				row = i;
				for (j = i; j <= m + n;j++)
					if (connexion[row][j] == 1)
					{
						col = j;
						break;
					}
				connexion[row][col] = 0;
				connexion[col][row] = 0;
				break;
			}
		}
		Path[k] = col;
	}
	freeiMatrix(connexion, m + n);
	freeiMatrix(distance, m + n);
	freeiMatrix(succession, m + n);
	free(PathBar);
	free(degree);
}

void decodecounter(int* Path, int m, int n, int* var_a, int* var_b, int** var_x)
{
	int *PathBar, i, j, k, l, r, starting, terminal, temp, iteration, row, col;
	int **connexion, **distance, **succession, *degree;
	PathBar = iVector(m + n);
	for (i = 1; i <= m + n; i++)
	{
		PathBar[i] = i;
		for (k = 1; k <= m + n - 2; k++)
			if (Path[k]==PathBar[i])
			{
				PathBar[i] = -infinity;
				break;
			}
	}
	connexion = iMatrix(m + n, m + n);
	for (i = 1; i <= m + n; i++)
		for (j = 1; j <= m + n; j++)
		{
			if (i == j) connexion[i][j] = 0;
			else connexion[i][j] = infinity;
		}
	for (i = 1; i <= m; i++)
		for (j = 1; j <= n; j++)
			var_x[i][j] = 0;
	distance = iMatrix(m + n, m + n);
	succession = iMatrix(m + n, m + n);
	for (iteration = 1; iteration <= m + n - 2; iteration++)
	{
		l = biggest(PathBar, m, n);;
		r = rightmost(Path, m, n, PathBar[l]);
		if (belong(PathBar[l], 1, m))
		{
			if (var_a[PathBar[l]] < var_b[Path[r] - m]) var_x[PathBar[l]][Path[r] - m] = var_a[PathBar[l]];
			else var_x[PathBar[l]][Path[r] - m] = var_b[Path[r] - m];
			var_a[PathBar[l]] = var_a[PathBar[l]] - var_x[PathBar[l]][Path[r] - m];
			var_b[PathBar[r] - m] = var_b[Path[r] - m] - var_x[PathBar[l]][Path[r] - m];
			connexion[PathBar[l]][Path[r]] = 1;
			connexion[Path[r]][PathBar[l]] = 1;
		}
		else
		{
			if (var_a[Path[r]] < var_b[PathBar[l] - m]) var_x[Path[r]][PathBar[l] - m] = var_a[Path[r]];
			else var_x[Path[r]][PathBar[l] - m] = var_b[Path[l] - m];
			var_a[Path[r]] = var_a[Path[r]] - var_x[Path[r]][PathBar[l] - m];
			var_b[PathBar[l] - m] = var_b[PathBar[l] - m] - var_x[Path[r]][PathBar[l] - m];
			connexion[Path[r]][PathBar[l]] = 1;
			connexion[PathBar[l]][Path[r]] = 1;

		}
		PathBar[l] = -infinity;
		temp = Path[r];
		Path[r] = 0;
		if (appear(Path, m, n, temp) == 0) putincounter(PathBar, m, n, temp);
	}
	for (i = 1; i <= m + n;i++)
		if (PathBar[i] != -infinity)
		{
			l = PathBar[i];
			PathBar[i] = -infinity;
			break;
		}
	for (i = 1; i <= m + n;i++)
		if (PathBar[i] != -infinity)
		{
			r = PathBar[i];
			break;
		}
	if (belong(l, 1, m))
	{
		if (var_a[l] < var_b[r - m]) var_x[l][r - m] = var_a[l];
		else var_x[l][r - m] = var_b[r - m];
		var_a[l] = var_a[l] - var_x[l][r - m];
		var_b[r - m] = var_b[r - m] - var_x[l][r - m];
		connexion[l][r] = 1;
		connexion[r][l] = 1;
	}
	else
	{
		if (var_a[r] < var_b[l - m]) var_x[r][l - m] = var_a[r];
		else var_x[r][l - m] = var_b[l - m];
		var_a[r] = var_a[r] - var_x[r][l - m];
		var_b[l - m] = var_b[l - m] - var_x[r][l - m];
		connexion[r][l] = 1;
		connexion[l][r] = 1;
	}
	for (;;)
	{
		for (i = 1; i <= m + n; i++)
			for (j = 1; j <= m + n; j++)
				distance[i][j] = connexion[i][j];
		ShortestPath(distance, succession, m + n);
		l = maxinset(var_a, m);
		if (var_a[l] != 0)
		{
			r = maxinset(var_b, n);
			if (var_a[l] < var_b[r]) var_x[l][r] = var_a[l];
			else var_x[l][r] = var_b[r];
			var_a[l] = var_a[l] - var_x[l][r];
			var_b[r] = var_b[r] - var_x[l][r];
			starting = l;
			terminal = m + r;
			r = succession[starting][terminal];
			for (;;)
			{
				if (var_x[l][r - m] == 0)
				{
					connexion[l][r] = infinity;
					connexion[r][l] = infinity;
					break;
				}
				else
				{
					if (r == terminal) break;
					l = r;
					r = succession[r][terminal];
					if (var_x[r][l - m] == 0)
					{
						connexion[r][l] = infinity;
						connexion[l][r] = infinity;
						break;
					}
					else
					{
						l = r;
						r = succession[r][terminal];
					}
				}
			}
			connexion[starting][terminal] = 1;
			connexion[terminal][starting] = 1;
		}
		else break;
	}
	for (i = 1; i <= m + n; i++)
		for (j = 1; j <= m + n; j++)
			if (connexion[i][j] == infinity)
				connexion[i][j] = 0;
	degree = iVector(m + n);
	for (k = m + n - 2; k >= 1; k--)
	{
		for (i = m + n; i >= 1; i--)
		{
			degree[i] = 0;
			for (j = 1; j <= m + n; j++)
				degree[i] += connexion[i][j];
			if (degree[i] == 1)
			{
				row = i;
				for (j = 1; j <= m + n;j++)
					if (connexion[row][j] == 1)
					{
						col = j;
						break;
					}
				connexion[row][col] = 0;
				connexion[col][row] = 0;
				break;
			}
		}
		Path[k] = col;
	}
	freeiMatrix(connexion, m + n);
	freeiMatrix(distance, m + n);
	freeiMatrix(succession, m + n);
	free(PathBar);
	free(degree);
}

int* ZeroOneVariable(int totalnum, int oneuppernum, int* capacity, int totaldemand)
{
	int* variable;
	int i, count, minimum, minino, totalcapacity, maximum, maxino;
	variable = iVector(totalnum);
	for (;;)
	{
		count = 0;
		for (i = 1; i <= totalnum; i++)
		{
			variable[i] = random(0, 1);
			if (variable[i] == 1) count = count + 1;
		}
		while (count > oneuppernum)
		{
			minimum = infinity;
			for (i = 1; i <= totalnum;i++)
				if (variable[i] == 1 && capacity[i] < minimum)
				{
					minimum = capacity[i];
					minino = i;
				}
			variable[minino] = 0;
			count = count - 1;
		}
		totalcapacity = 0;
		for (i = 1; i <= totalnum; i++)
			if (variable[i] == 1) totalcapacity += capacity[i];
		if (totalcapacity < totaldemand)
		{
			minimum = infinity;
			minino = 0;
			for (i = 1; i <= totalnum;i++)
				if (variable[i] == 1 && capacity[i] < minimum)
				{
					minimum = capacity[i];
					minino = i;
				}
			if (minino != 0)
			{
				variable[minino] = 0;
				totalcapacity -= capacity[minino];
			}
			maximum = -infinity;
			maxino = 0;
			for (i = 1; i <= totalnum;i++)
				if (variable[i] == 0 && capacity[i] > maximum)
				{
					maximum = capacity[i];
					maxino = i;
				}
			if (maxino != 0)
			{
				variable[maxino] = 1;
				totalcapacity += capacity[maxino];
			}
			if (totalcapacity >= totaldemand) break;
		}
		else break;
	}
	return variable;
}

void feasiblecapacity(int* variable, int totalnum, int oneuppernum, int*capacity, int totaldemand)
{
	int i, count, minimum, minino, totalcapacity, maximum, maxino;
	int first;
	first = 1;
	for (;;)
	{
		count = 0;
		for (i = 1; i <= totalnum; i++)
		{
			if (first == 0) variable[i] = random(0, 1);
			if (variable[i] == 1) count = count + 1;
		}
		while (count > oneuppernum)
		{
			minimum = infinity;
			for (i = 1; i <= totalnum;i++)
				if (variable[i] == 1 && capacity[i] < minimum)
				{
					minimum = capacity[i];
					minino = i;
				}
			variable[minino] = 0;
			count = count - 1;
		}
		totalcapacity = 0;
		for (i = 1; i <= totalnum; i++)
			if (variable[i] == 1) totalcapacity += capacity[i];
		if (totalcapacity < totaldemand)
		{
			minimum = infinity;
			minino = 0;
			for (i = 0; i <= totalnum;i++)
				if (variable[i] == 1 && capacity[i] < minimum)
				{
					minimum = capacity[i];
					minino = i;
				}
			if (minino != 0)
			{
				variable[minino] = 0;
				totalcapacity -= capacity[minino];
			}
			maximum = -infinity;
			maxino = 0;
			for (i = 1; i <= totalnum;i++)
				if (variable[i] == 0 && capacity[i] > maximum)
				{
					maximum = capacity[i];
					maxino = i;
				}
			if (maxino != 0)
			{
				variable[maxino] = 1;
				totalcapacity += capacity[maxino];
			}
			if (totalcapacity >= totaldemand) break;
		}
		else break;
		first = 0;
	}
}

void generatechromo(int** chromosome, int var_I, int var_J, int var_K, int var_L, int var_p, int var_w, int* var_a, int* var_b, int* var_c, int* var_d, int** var_x, int** var_y, int** var_z, int*var_W, int* var_Z)
{
	int i, j, k, l, demand;
	int *aa, *bb;
	demand = 0;
	for (i = 1; i <= var_I; i++)
		demand += var_a[i];
	chromosome[1] = ZeroOneVariable(var_J, var_p, var_b, demand);
	chromosome[2] = ZeroOneVariable(var_K, var_w, var_c, demand);
	chromosome[3] = PruferNum(var_I, var_J);
	aa = iVector(var_I);
	bb = iVector(var_J);
	for (i = 1; i <= var_I; i++)
		aa[i] = var_a[i];
	for (j = 1; j <= var_J; j++)
	{
		if (chromosome[1][j] == 1)
		{
			bb[j] = var_b[j];
			var_W[j] = 1;
		}
		else
		{
			bb[j] = 0;
			var_W[j] = 0;
		}
	}
	decode(chromosome[3], var_I, var_J, aa, bb, var_x);
	free(aa);
	free(bb);
	chromosome[4] = PruferNum(var_J, var_K);
	aa = iVector(var_J);
	bb = iVector(var_K);
	for (j = 1; j <= var_J; j++)
	{
		aa[j] = 0;
		for (i = 1; i <= var_I; i++)
			aa[j] += var_x[i][j];
	}
	for (k = 1; k <= var_K; k++)
	{
		if (chromosome[2][k] == 1)
		{
			bb[k] = var_c[k];
			var_Z[k] = 1;
		}
		else
		{
			bb[k] = 0;
			var_Z[k] = 0;
		}
	}
	decodecounter(chromosome[4], var_J, var_K, aa, bb, var_y);
	free(aa);
	free(bb);
	chromosome[5] = PruferNum(var_K, var_L);
	aa = iVector(var_K);
	bb = iVector(var_L);
	for (k = 1; k <= var_K; k++)
	{
		aa[k] = 0;
		for (j = 1; j <= var_J; j++)
			aa[k] += var_y[j][k];
	}
	for (l = 1; l = var_L; l++)
		bb[l] = var_d[l];
	decode(chromosome[5], var_K, var_L, aa, bb, var_z);
	free(aa);
	free(bb);
}

void decodechromo(int** chromosome, int var_I, int var_J, int var_K, int var_L, int var_p, int var_w, int* var_a, int* var_b, int* var_c, int* var_d, int** var_x, int** var_y, int** var_z, int* var_W, int* var_Z)
{
	int i, j, k, l, demand;
	int *aa, *bb;
	demand = 0;
	for (i = 1; i <= var_I; i++)
		demand += var_a[i];
	aa = iVector(var_I);
	bb = iVector(var_J);
	for (i = 1; i <= var_I; i++)
		aa[i] = var_a[i];
	for (j = 1; j <= var_J; j++)
	{
		if (chromosome[1][j] == 1)
		{
			bb[j] = var_b[j];
			var_W[j] = 1;
		}
		else
		{
			bb[j] = 0;
			var_W[j] = 0;
		}
	}
	decode(chromosome[3], var_I, var_J, aa, bb, var_x);
	free(aa);
	free(bb);
	aa = iVector(var_J);
	bb = iVector(var_K);
	for (j = 1; j <= var_J; j++)
	{
		aa[j] = 0;
		for (i = 1; i <= var_I; i++)
			aa[j] += var_x[i][j];
	}
	for (k = 1; k <= var_K; k++)
	{
		if (chromosome[2][k] == 1)
		{
			bb[k] = var_c[k];
			var_Z[k] = 1;
		}
		else
		{
			bb[k] = 0;
			var_Z[k] = 0;
		}
	}
	decodecounter(chromosome[4], var_J, var_K, aa, bb, var_y);
	free(aa);
	free(bb);
	aa = iVector(var_K);
	bb = iVector(var_L);
	for (k = 1; k <= var_K; k++)
	{
		aa[k] = 0;
		for (j = 1; j <= var_J; j++)
			aa[k] += var_y[j][k];
	}
	for (l = 1; l <= var_L; l++)
		bb[l] = var_d[l];
	decode(chromosome[5], var_K, var_L, aa, bb, var_z);
	free(aa);
	free(bb);
}

void exchange(int* parent1, int* parent2, int* child1, int* child2, int num)
{
	int j, cutpoint;
	cutpoint = random(2, num);
	for (j = 1; j <= num; j++)
	{
		if (j < cutpoint) child1[j] = parent1[j];
		else child1[j] = parent2[j];
		if (j < cutpoint) child2[j] = parent2[j];
		else child2[j] = parent1[j];
	}
}

void crossover(int** chromoparent1, int** chromoparent2, int** chromochild1, int** chromochild2, int var_I, int var_J, int var_K, int var_L, int var_p, int var_w, int* var_a, int* var_b, int* var_c, int* var_d)
{
	int i, totaldemand;
	totaldemand = 0;
	for (i = 1; i < I; i++)
		totaldemand += var_a[i];
	chromochild1[1] = iVector(var_J);
	chromochild1[2] = iVector(var_K);
	chromochild1[3] = iVector(var_I + var_J - 2);
	chromochild1[4] = iVector(var_J + var_K - 2);
	chromochild1[5] = iVector(var_K + var_L - 2);
	chromochild2[1] = iVector(var_J);
	chromochild2[2] = iVector(var_K);
	chromochild2[3] = iVector(var_I + var_J - 2);
	chromochild2[4] = iVector(var_J + var_K - 2);
	chromochild2[5] = iVector(var_K + var_L - 2);
	exchange(chromoparent1[1], chromoparent2[1], chromochild1[1], chromochild2[1], var_J);
	feasiblecapacity(chromochild1[1], var_J, var_p, var_b, totaldemand);
	feasiblecapacity(chromochild2[1], var_J, var_p, var_b, totaldemand);
	exchange(chromoparent1[2], chromoparent2[2], chromochild1[2], chromochild2[2], var_K);
	feasiblecapacity(chromochild1[2], var_K, var_w, var_c, totaldemand);
	feasiblecapacity(chromochild2[2], var_K, var_w, var_c, totaldemand);
	exchange(chromoparent1[3], chromoparent2[3], chromochild1[3], chromochild2[3], var_I + var_J - 2);
	feasibleprufer(chromochild1[3], var_I, var_J);
	feasibleprufer(chromochild2[3], var_I, var_J);
	exchange(chromoparent1[4], chromoparent2[4], chromochild1[4], chromochild2[4], var_J + var_K - 2);
	feasibleprufer(chromochild1[4], var_J, var_K);
	feasibleprufer(chromochild2[4], var_J, var_K);
	exchange(chromoparent1[5], chromoparent2[5], chromochild1[5], chromochild2[5], var_K + var_L - 2);
	feasibleprufer(chromochild1[5], var_K, var_L);
	feasibleprufer(chromochild2[5], var_K, var_L);
}

void Inversion(int* parent, int* child, int num)
{
	int j, l, r, temp;
	l = random(l, num);
	for (;;)
	{
		r = random(l, num);
		if (r != 1) break;
	}
	if (l > r)
	{
		temp = l;
		l = r;
		r = temp;
	}
	for (j = 1; j <= num; j++)
	{
		if (j <= r && j >= l) child[j] = parent[l + r - j];
		else child[j] = parent[j];
	}
}

void InversionMutation(int** chromoparent, int** chromochild, int var_I, int var_J, int var_K, int var_L, int var_p, int var_w, int * var_a, int* var_b, int* var_c, int* var_d)
{
	int i, totaldemand;
	totaldemand = 0;
	for (i = 1; i <= var_I; i++)
		totaldemand += var_a[i];
	chromochild[1] = iVector(var_J);
	chromochild[2] = iVector(var_K);
	chromochild[3] = iVector(var_I + var_J - 2);
	chromochild[4] = iVector(var_J + var_K - 2);
	chromochild[5] = iVector(var_K + var_L - 2);
	Inversion(chromoparent[1], chromochild[1], var_J);
	feasiblecapacity(chromochild[1], var_J, var_p, var_b, totaldemand);
	Inversion(chromoparent[2], chromochild[2], var_K);
	feasiblecapacity(chromochild[2], var_K, var_w, var_c, totaldemand);
	Inversion(chromoparent[3], chromochild[3], var_I + var_J - 2);
	Inversion(chromoparent[4], chromochild[4], var_J + var_K - 2);
	Inversion(chromoparent[5], chromochild[5], var_K + var_L - 2);
}

void Displacement(int* parent, int* child, int num)
{
	int j, l, r, temp;
	int position;
	int *aa, *bb;
	l = random(1, num);
	for (;;)
	{
		r = random(1, num);
		if (abs(r - 1) != num - 1) break;
	}
	if (l > r)
	{
		temp = l;
		l = r;
		r = temp;
	}
	aa = iVector(r - l + 1);
	bb = iVector(num - r + l - 1);
	for (j = 1; j <= num; j++)
	{
		if (j <= r && j >= l) aa[j - l + 1] = parent[j];
		else if (j < l) bb[j] = parent[j];
		else bb[j - r + l - 1] = parent[j];
	}
	position = random(1, num - r + l - 1);
	for (j = 1; j <= num; j++)
	{
		if (j < position) child[j] = bb[j];
		else if (j < position + r - l) child[j] = aa[j - position + 1];
		else child[j] = bb[j - r + l - 1];
	}
	free(aa);
	free(bb);
}

void DisplacementMutation(int** chromoparent, int** chromochild, int var_I, int var_J, int var_K, int var_L, int var_p, int var_w, int* var_a, int* var_b, int* var_c, int* var_d)
{
	int i, totaldemand;
	totaldemand = 0;
	for (i = 1; i <= var_I; i++)
		totaldemand += var_a[i];
	chromochild[1] = iVector(var_J);
	chromochild[2] = iVector(var_K);
	chromochild[3] = iVector(var_I + var_J - 2);
	chromochild[4] = iVector(var_J + var_K - 2);
	chromochild[5] = iVector(var_K + var_L - 2);
	Displacement(chromoparent[1], chromochild[1], var_J);
	feasiblecapacity(chromochild[1], var_J, var_p, var_b, totaldemand);
	Displacement(chromoparent[2], chromochild[2], var_K);
	feasiblecapacity(chromochild[2], var_K, var_w, var_c, totaldemand);
	Displacement(chromoparent[3], chromochild[3], var_I + var_J - 2);
	Displacement(chromoparent[4], chromochild[4], var_J + var_K - 2);
	Displacement(chromoparent[5], chromochild[5], var_K + var_L - 2);;
}

int fitnessvalue(int** var_s, int** var_t, int** var_u, int** var_x, int** var_y, int** var_z, int* var_F, int* var_G, int* var_W, int* var_Z, int var_I, int var_J, int var_K, int var_L)
{
	int i, j, k, l;
	int sum;
	sum = 0;
	for (i = 1; i <= var_I; i++)
		for (j = 1; j <= var_J; j++)
			sum += var_s[i][j] * var_x[i][j];
	for (j = 1; j <= var_J; j++)
		for (k = 1; k <= var_K; k++)
			sum += var_t[j][k] * var_y[j][k];
	for (k = 1; k <= var_K; k++)
		for (l = 1; l <= var_L; l++)
			sum += var_u[k][l] * var_z[k][l];
	for (j = 1; j <= var_J; j++)
		sum += var_F[j] * var_W[j];
	for (k = 1; k <= var_K; k++)
		sum += var_G[k] * var_Z[k];
	return sum;
}

int equalvector(int* var_a, int* var_b, int num)
{
	int i, sign;
	sign = 1;
	for (i = 1; i <= num;i++)
		if (var_a[i] != var_b[i])
		{
			sign = 0;
			break;
		}
	return sign;
}

int equalchromo(int** chromosome1, int** chromosome2, int var_I, int var_J, int var_K, int var_L)
{
	int value;
	value = equalvector(chromosome1[1], chromosome2[1], var_J);
	value = value*equalvector(chromosome1[2], chromosome2[2], var_K);
	value = value*equalvector(chromosome1[3], chromosome2[3], var_I + var_J - 2);
	value = value*equalvector(chromosome1[4], chromosome2[4], var_J + var_K - 2);
	value = value*equalvector(chromosome1[5], chromosome2[5], var_K + var_L - 2);
	return value;
}

int inchromopopu(int*** chromopop, int num, int** chromosome, int var_I, int var_J, int var_K, int var_L)
{
	int i, index;
	index = 0;
	for (i = 1; i < num; i++)
		index += equalchromo(chromopop[i], chromosome, var_I, var_J, var_K, var_L);
	if (index != 0) return 1;
	else return 0;
}

void copychromo(int** chromosome1, int** chromosome2, int var_I, int var_J, int var_K, int var_L)
{
	int i;
	chromosome2[1] = iVector(var_J);
	chromosome2[2] = iVector(var_K);
	chromosome2[3] = iVector(var_I + var_J - 2);
	chromosome2[4] = iVector(var_J + var_K - 2);
	chromosome2[5] = iVector(var_K + var_L - 2);
	for (i = 1; i <= var_J; i++)
		chromosome2[1][i] = chromosome1[1][i];
	for (i = 1; i <= var_K; i++)
		chromosome2[2][i] = chromosome1[2][i];
	for (i = 1; i <= var_I + var_J - 2; i++)
		chromosome2[3][i] = chromosome1[3][i];
	for (i = 1; i <= var_J + var_K - 2; i++)
		chromosome2[4][i] = chromosome1[4][i];
	for (i = 1; i <= var_K + var_L - 2; i++)
		chromosome2[5][i] = chromosome1[5][i];
}

void inpudata()
{
	char mys[100];
	int i, j, k, l;
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	pc = atof(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	pm = atof(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	maxgen = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	popsize = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	I = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	J = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	K = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	L = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	p = atoi(mys);
	fscanf(fp, "%s", mys);
	fscanf(fp, "%s", mys);
	w = atoi(mys);
	s = iMatrix(I, J);
	t = iMatrix(J, K);
	u = iMatrix(K, L);
	x = iMatrix(I, J);
	y = iMatrix(J, K);
	z = iMatrix(K, L);
	a = iVector(I);
	b = iVector(J);
	c = iVector(K);
	d = iVector(L);
	F = iVector(J);
	G = iVector(K);
	W = iVector(J);
	Z = iVector(K);
	fscanf(fp, "%s", mys);
	for (i = 1; i <= I; i++)
	{
		fscanf(fp, "%s", mys);
		a[i] = atoi(mys);
	}
	fscanf(fp, "%s", mys);
	for (i = 1; i <= J; i++)
	{
		fscanf(fp, "%s", mys);
		b[i] = atoi(mys);
	}
	fscanf(fp, "%s", mys);
	for (i = 1; i <= J; i++)
	{
		fscanf(fp, "%s", mys);
		F[i] = atoi(mys);
	}
	fscanf(fp, "%s", mys);
	for (i = 1; i <= K; i++)
	{
		fscanf(fp, "%s", mys);
		c[i] = atoi(mys);
	}
	fscanf(fp, "%s", mys);
	for (i = 1; i <= K; i++)
	{
		fscanf(fp, "%s", mys);
		G[i] = atoi(mys);
	}
	fscanf(fp, "%s", mys);
	for (i = 1; i <= L; i++)
	{
		fscanf(fp, "%s", mys);
		d[i] = atoi(mys);
	}
	fscanf(fp, "%s", mys);
	for (i = 1; i <= I; i++)
		for (j = 1; j <= J; j++)
		{
			fscanf(fp, "%s", mys);
			s[i][j] = atoi(mys);
		}
	fscanf(fp, "%s", mys);
	for (j = 1; j <= J; j++)
		for (k = 1; k <= K; k++)
		{
			fscanf(fp, "%s", mys);
			t[j][k] = atoi(mys);
		}
	fscanf(fp, "%s", mys);
	for (k = 1; k <= k; k++)
		for (l = 1; l <= L; l++)
		{
			fscanf(fp, "%s", mys);
			u[k][l] = atoi(mys);
		}
}

void Selection(int popsize, int lamda)
{
	int i, iteration, scope;
	scope = popsize + lamda;
	for (i = 1; i <= popsize;)
	{
		iteration = smallest(evaluation, scope, 0);
		if (i == 1)
		{
			if (belong(iteration, 1, popsize) == 1)
				copychromo(chromopopulation[iteration], chromopopul[i], I, J, K, L);
			else
				copychromo(chromopopu[iteration = popsize], chromopopul[i], I, J, K, L);
			i++;
		}
		else
		{
			if (belong(iteration, 1, popsize) == 1)
			{
				if (inchromopopu(chromopopul, i, chromopopulation[iteration], I, J, K, L) != 1)
				{
					copychromo(chromopopulation[iteration], chromopopul[i], I, J, K, L);
					i++;
				}
			}
			else
			{
				if (inchromopopu(chromopopul, i, chromopopu[iteration - popsize], I, J, K, L) != 1)
				{
					copychromo(chromopopu[iteration - popsize], chromopopul[i], I, J, K, L);
					i++;
				}
			}
		}
		evaluation[iteration] = infinity;
	}
	for (i = 1; i <= popsize; i++)
	{
		freechromo(chromopopulation[i], 5);
		chromopopulation[i] = chromo(5);
		copychromo(chromopopul[i], chromopopulation[i], I, J, K, L);
		freechromo(chromopopul[i], 5);
		chromopopul[i] = chromo(5);;
	}
	for (i = 1; i <= lamda; i++)
	{
		freechromo(chromopopu[i], 5);
		chromopopu[i] = chromo(5);
	}
	for (i = 1; i <= popsize; i++)
	{
		decodechromo(chromopopulation[i], I, J, K, L, p, w, a, b, c, d, x, y, z, W, Z);
		evaluation[i] = fitnessvalue(s, t, u, x, y, z, F, G, W, Z, I, J, K, L);
	}
}

int populationCrossover(int popsize, double probability)
{
	int i, iteration, first, second, lamda;
	for (i = 1, iteration = 1; i <= popsize; i++)
	{
		first = random(1, popsize);
		second = random(1, popsize);
		while (second == first)
			second = random(1, popsize);
		if (random(1, 100) <= 100 * probability)
		{
			crossover(chromopopulation[first], chromopopulation[second], chromopopu[iteration], chromopopu[iteration + 1], I, J, K, L, p, w, a, b, c, d);
			decodechromo(chromopopu[iteration], I, J, K, L, p, w, a, b, c, d, x, y, z, W, Z);
			evaluation[popsize + iteration] = fitnessvalue(s, t, u, x, y, z, F, G, W, Z, I, J, K, L);
			decodechromo(chromopopu[iteration + 1], I, J, K, L, p,w, a, b, c, d, x, y, z, W, Z);
			evaluation[popsize + iteration + 1] = fitnessvalue(s, t, u, x, y, z, F, G, W, Z, I, J, K, L);
			iteration += 2;
		}
	}
	lamda = iteration - 1;
	return lamda;
}

int populationMutation(int popsize, double probability)
{
	int i, iteration, first, lamda;
	for (i = 1, iteration = 1; i <= popsize; i++)
	{
		first = random(1, popsize);
		if (random(1, 100) <= 100 * probability)
		{
			if (random(0, 1) == 1)
				InversionMutation(chromopopulation[first], chromopopu[iteration], I, J, K, L, p, w, a, b, c, d);
			else
				DisplacementMutation(chromopopulation[first], chromopopu[iteration], I, J, K, L, p, w, a, b, c, d);
			decodechromo(chromopopu[iteration], I, J, K, L, p, w, a, b, c, d, x, y, z, W, Z);
			evaluation[popsize + iteration] = fitnessvalue(s, t, u, x, y, z, F, G, W, Z, I, J, K, L);
			iteration++;
		}
	}
	lamda = iteration - 1;
	return lamda;
}

void musco()
{
	int i, generation, lamda;
	evaluation = iVector(3 * popsize);
	chromopopulation = chromopop(popsize);
	chromopopu = chromopop(2 * popsize);
	chromopopul = chromopop(popsize);
	for (i = 1; i <= popsize; i++)
	{
		chromopopulation[i] = chromo(5);
		generatechromo(chromopopulation[i], I, J, K, L, p, w, a, b, c, d, x, y, z, W, Z);
		evaluation[i] = fitnessvalue(s, t, u, x, y, z, F, G, W, Z, I, J, K, L);
		chromopopul[i] = chromo(5);
	}
	for (i = 1; i <= 2 * popsize; i++)
		chromopopu[i] = chromo(5);
	for (generation = 1; generation <= maxgen; generation++)
	{
		lamda = populationCrossover(popsize, pc);
		Selection(popsize, lamda);
		lamda = populationMutation(popsize, pm);
		Selection(popsize, lamda);
		fprintf(fp, "%d\n", evaluation[1]);
	}
}

void output()
{
	int i, j, k, l;
	fprintf(fp, "	The found optimal solution to this probelm is as follows:\n");
	fprintf(fp, "the found optimal chromosome is:\n");
	for (j = 1; j <= J; j++)
		fprintf(fp, "%d	", chromopopulation[1][1][j]);
	fprintf(fp, "\n");
	for (k = 1; k <= K; k++)
		fprintf(fp, "%d	", chromopopulation[1][2][k]);
	fprintf(fp, "\n");
	for (j = 1; j <= I + J - 2; j++)
		fprintf(fp, "%d	", chromopopulation[1][3][j]);
	fprintf(fp, "\n");
	for (j = 1; j <= J + K - 2; j++)
		fprintf(fp, "%d	", chromopopulation[1][4][j]);
	fprintf(fp, "\n");
	for (j = 1; j <= K + L - 2; j++)
		fprintf(fp, "%d	", chromopopulation[1][5][j]);
	fprintf(fp,"\n");
	decodechromo(chromopopulation[1], I, J, K, L, p, w, a, b, c, d, x, y, z, W, Z);
	fprintf(fp, "the from-customer-to-plant production quantity matrix x[i][j]:\n");
	for (i = 1; i <= I; i++)
	{
		for (j = 1; j <= J; j++)
			fprintf(fp, "%d	", x[i][j]);
		fprintf(fp, "\n");
	}
	fprintf(fp, "the from-plant-to-DC transportation quantity matrix y[j][k]:\n");
	for (j = 1; j <= J; j++)
	{
		for (k = 1; k <= K; k++)
			fprintf(fp, "%d	", y[j][k]);
		fprintf(fp, "\n");
	}
	fprintf(fp, "the from-DC-to-customer transportation quantity matrix z[k][l]:\n");
	for (k = 1; k <= K; k++)
	{
		for (l = 1; l <= L; l++)
			fprintf(fp, "%d	", z[k][l]);
		fprintf(fp, "\n");
	}
	fprintf(fp, "the found optimal objective funtion value is %d\n", evaluation[1]);
	f.Close();
}