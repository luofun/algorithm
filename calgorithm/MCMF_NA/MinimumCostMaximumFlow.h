#if !defined(AFX_MINMUMCOSTMAXIMUMFLOW_H_846226A7_7866_4871_869A_3F60FAA53DB8__INCLUED_)
#define AFX_MINMUMCOSTMAXIMUMFLOW_H_846226A7_7866_4871_869A_3F60FAA53DB8__INCLUED_
#if _MSC_VER > 1000
#pragma once
#endif
#include "stdlib.h"
#include "stdio.h"
#include "malloc.h"
#include "string.h"
#include "math.h"
const int infinity = 1000000000;
class MinimumCostMaximumFlow
{
public:
	int n, s, t, m;
	double **C, **B, **W, **F, **U, **Capacity, **Cost;
	int **S, **sign;
	double MinValue;
	FILE *fp;
public:
	MinimumCostMaximumFlow();
	virtual ~MinimumCostMaximumFlow();
	int ** iMatrix(int row,int col);
	void freeiMatrux(int ** iMatrix, int row);
	double Min(double a, double b);
	double ** dMatrix(int row,int col);
	void freedMatrix(double ** dMatrix, int row);
	void FreeAll();
	void inputdata();
	void output();
	void InitializeFW();
	void InitializeUS(double **x);
	void SearchByMaxCapPath();
	void ConstructCapCosMat();
	double add(double x, double y);
	int NegativeCycleFound();
	void NegativeCycleAjust();
	void MaxFlow();
	void MinCostMaxFlow();
	void SetFilePointer(FILE *z);
	void inputdata2(char** topo, int linenum);


};
#endif





