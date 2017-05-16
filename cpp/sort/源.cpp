#include<stdio.h>
#include<vector>
#include <algorithm>
#include<time.h>

void seletionrank(std::vector<char> &vct)
{
	int min;
	//char temp;
	for (int i = 0; i < vct.size(); i++)
	{
		min = i;
		for (int j = i + 1; j < vct.size(); j++)
		{
			if (vct[j] < vct[min])
				min = j;
			
		}
		std::swap(vct[min], vct[i]);
	}


}

void insertionrank(std::vector<char> &vct)
{
	for (int i = 1; i < vct.size(); i++)
	{
		for (int j = i; j > 0 && (vct[j] < vct[j - 1]); j--)
			std::swap(vct[j], vct[j - 1]);
	}

}

void xersort(std::vector<char> &vct)
{
	int h = 1;
	while (h < vct.size() / 3)
		h = 3 * h + 1;
	while (h >= 1)
	{
		for (int i = h; i < vct.size(); i++)
		{
		
			for (int j = i; j >= h && (vct[j] < vct[j - h]); j -= h)
			{
				std::swap(vct[j], vct[j - h]);
			}
			
			
		}
		h = h / 3;
	}
}

void merage(std::vector<char> &a, std::vector<char> &aux, int lo, int mid, int hi)
{
	int i = lo;
	int j = mid + 1;
	
	for (int k = lo; k <= hi; k++)
		aux[k] = a[k];
	for (int k = lo; k <= hi; k++)
	{
		if (i > mid)
			a[k] = aux[j++];
		else if (j > hi)
			a[k] = aux[i++];
		else if (aux[j] < aux[i])
			a[k] = aux[j++];
		else
			a[k] = aux[i++];
	}


}

int meragesort(std::vector<char> &vct, std::vector<char> &aux, int lo, int hi)
{
	if (hi <= lo)
		return 0;
	int mid = lo + (hi - lo) / 2;
	meragesort(vct, aux, lo, mid);
	meragesort(vct, aux, mid + 1, hi);
	merage(vct, aux, lo, mid, hi);
	return 0;
}

void merage_sort(std::vector<char> &vct)
{
	std::vector<char> aux(vct.size());
	meragesort(vct, aux, 0, vct.size() - 1);
}

void meragebu(std::vector<char> &vct)
{
	std::vector<char> aux(vct.size());
	for (int sz = 1; sz < vct.size(); sz = sz + sz)
	{
		for (int lo = 0; lo < vct.size() - sz; lo += sz + sz)
		{
			merage(vct, aux, lo, lo + sz - 1, lo + sz + sz - 1 < vct.size() - 1 ? lo + sz + sz - 1 : vct.size() - 1);
		}
	}
}

int partition(std::vector<char> &vct, int lo, int hi)
{
	int i = lo;
	int j = hi;
	char v = vct[lo];
	while (1)
	{
		while (vct[++i] < v)
			if (i == hi)
				break;
		while (v < vct[--j])
			if (j == lo)
				break;
		if (i >= j)
			break;
		std::swap(vct[i], vct[j]);
	}
	std::swap(vct[lo], vct[j]);
	return j;
}

void qsort(std::vector<char> &vct, int lo, int hi)
{
	if (hi <= lo)
		return;
	int j = partition(vct, lo, hi);
	qsort(vct, lo, j - 1);
	qsort(vct, j + 1, hi);
}

void quicksort(std::vector<char> &vct)
{
	qsort(vct, 0, vct.size() - 1);
}

void qsortpp(std::vector<char> &vct, int M, int lo, int hi)
{
	if (hi <= lo + M)
	{
		insertionrank(vct);
		return;
	}
	int j = partition(vct, lo, hi);
	qsort(vct, lo, j - 1);
	qsort(vct, j + 1, hi);
}

void tridivsort(std::vector<char> &vct, int lo, int hi)
{
	if (hi <= lo)
		return;
	int lt = lo;
	int i = lo + 1;
	int gt = hi;
	char v = vct[lo];
	while (i <= gt)
	{
		if (vct[i] < v)
			std::swap(vct[lt++], vct[i++]);
		else if (vct[i] > v)
			std::swap(vct[i], vct[gt--]);
		else
			i++;
	}
	tridivsort(vct, lo, lt - 1);
	tridivsort(vct, gt + 1, hi);
}

void showtestc(std::vector<char> vct)
{
	printf("\n\n");
	for (int i = 0; i < vct.size(); i++)
	{
		printf("%c\t", vct[i]);
	}
	printf("\n\n");
}

void sink(std::vector<char> &vct, int k, int N)
{
	while (2 * k <= N)
	{
		int j = 2 * k;
		if (j < N && (vct[j] < vct[j + 1]))
			j++;
		if (!(vct[k] < vct[j]))
			break;
		std::swap(vct[k],vct[j]);
		k = j;
	}
};

void stacksort(std::vector<char> &vct)
{
	int N = vct.size() - 1;
	for (int k = N / 2; k >= 1; k--)
	{
		sink(vct, k, N);
	}
	while (N > 1)
	{
		std::swap(vct[1], vct[N--]);
		sink(vct, 1, N);
	}
}

class maxpqint
{
private:
	int* pq;
	int N = 0;
	bool less(int i, int j)
	{
		return pq[i] < pq[j];
	};
	void exch(int i, int j)
	{
		int t = pq[i];
		pq[i] = pq[j];
		pq[j] = t;
	};
	void swim(int k)
	{
		while (k > 1 && less(k / 2, k))
		{
			exch(k / 2, k);
			k = k / 2;
		}
	};
	void sink(int k)
	{
		while (2 * k <= N)
		{
			int j = 2 * k;
			if (j < N&&less(j, j + 1))
				j++;
			if (!less(k, j))
				break;
			exch(k, j);
			k = j;
		}
	};
public:
	maxpqint(int maxn)
	{
		pq = new int[maxn + 1];
		
	}
	bool isempty()
	{
		return N == 0;
	}
	int size()
	{
		return N;
	}
	void insert(int v)
	{
		pq[++N] = v;
		swim(N);
	}
	int delmax()
	{
		int max = pq[1];
		exch(1, N--);
		pq[N + 1] = NULL;
		sink(1);
		return max;
	}

};



int main(int argc, char* argv[])
{
	std::vector<char> vctest;
	std::vector<int> vitest;
	std::vector<double> vdtest;

	int n = 0;
	clock_t begin;
	char ctt;
	printf("data num:");
	scanf("%d", &n);
	getchar();
	printf("\n\ninput data\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%c", &ctt);
		vctest.push_back(ctt);
	}

	begin = clock();
	//seletionrank(vctest);
	//insertionrank(vctest);
	//xersort(vctest);
	//merage_sort(vctest);
	//meragebu(vctest);
	//quicksort(vctest);
	//tridivsort(vctest, 0, vctest.size() - 1);
	stacksort(vctest);
	printf("\nused time is %lf\n\n", (double)(clock() - begin) / CLOCKS_PER_SEC);

	showtestc(vctest);




	return 0;
}