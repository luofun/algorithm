#include<iostream>
#include<algorithm>
#include<string>
#include<sstream>
#include<set>
#include<vector>
#include<stack>
#include<map>
#include<queue>
#include<deque>
#include<cstdlib>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<ctime>
#include<functional>
#include <time.h>
#include "io.h"
using namespace std;

#define N 10000
#define INF 100000000

int Node = 0;

struct Edge
{
	int from, to, cap, flow, cost;
	Edge(int u, int v, int ca, int f, int co) :from(u), to(v), cap(ca), flow(f), cost(co){};
};

struct MCMF
{
	int n, m, s, t;
	vector<Edge> edges;
	vector<int> G[N];
	int inq[N];//是否在队列中
	int d[N];//距离
	int p[N];//上一条弧
	int a[N];//可改进量

	void init(int n)//初始化
	{
		this->n = n;
		for (int i = 0; i<n; i++)
			G[i].clear();
		edges.clear();
	}

	void addedge(int from, int to, int cap, int cost)//加边
	{
		edges.push_back(Edge(from, to, cap, 0, cost));
		edges.push_back(Edge(to, from, 0, 0, -cost));
		int m = edges.size();
		G[from].push_back(m - 2);
		G[to].push_back(m - 1);
	}

	bool SPFA(int s, int t, int &flow, int &cost)//寻找最小费用的增广路，使用引用同时修改原flow,cost
	{
		for (int i = 0; i<n; i++)
			d[i] = INF;
		memset(inq, 0, sizeof(inq));
		d[s] = 0; inq[s] = 1; p[s] = 0; a[s] = INF;
		queue<int> Q;
		Q.push(s);
		while (!Q.empty())
		{
			int u = Q.front();
			Q.pop();
			inq[u]--;
			for (int i = 0; i < G[u].size(); i++)
			{
				Edge& e = edges[G[u][i]];
				if (e.cap>e.flow && d[e.to]>d[u] + e.cost)//满足可增广且可变短
				{
					d[e.to] = d[u] + e.cost;
					p[e.to] = G[u][i];
					a[e.to] = min(a[u], e.cap - e.flow);
					if (!inq[e.to])
					{
						inq[e.to]++;
						Q.push(e.to);
					}
				}
			}
		}
		if (d[t] == INF) return false;//汇点不可达则退出
		flow += a[t];
		cost += d[t] * a[t];
		int u = t;
		while (u != s)//更新正向边和反向边
		{
			edges[p[u]].flow += a[t];
			edges[p[u] ^ 1].flow -= a[t];
			u = edges[p[u]].from;
		}
		return true;
	}

	int MincotMaxflow(int s, int t)
	{
		int flow = 0, cost = 0;
		while (SPFA(s, t, flow, cost));
		return cost;
	}

	void datainput(char** topo, int line_num)
	{
		int nodenum,linknum, cusnum;
		int x, y, width, cost;
		sscanf(topo[0], "%d %d %d", &nodenum, &linknum, &cusnum);
		nodenum = nodenum + 2;//plus the s and t
		//s to node(s=nodenum-2)
		int s2nnum;
		s2nnum = 1;
		addedge(nodenum - 2, 3, INF, 0);
		//node to node(begin at zero)
		for (int i = 4; i < linknum + 4; i++)
		{
			sscanf(topo[i], "%d %d %d %d", &x, &y, &width, &cost);
			addedge(x, y, width, cost);
		}
		//node to t(t=nodenum-1)
		for (int i = line_num - cusnum; i < line_num; i++)
		{
			sscanf(topo[i], "%*d %d %d", &y, &width);
			addedge(nodenum - 1, y, width, 0);
		}
		n = 2 + linknum * 2 + cusnum * 2;
		//n = n / 2;
		Node = nodenum;
		
	}
};


int main(int argc, char *argv[])
{
	MCMF mcmf;
	printf("sizeppp=%d\n", mcmf.edges.size());

	char *topo[MAX_EDGE_NUM];
	int line_num;
	clock_t start = clock();
	char *topo_file = argv[1];
	printf("file=%s\n", topo_file);

	line_num = read_file(topo, MAX_EDGE_NUM, topo_file);

	printf("line num is :%d \n", line_num);
	if (line_num == 0)
	{
		printf("Please input valid topo file.\n");
		return -1;
	}
	
	int mcmfcost;
	mcmf.datainput(topo, line_num);
	printf("sizeaaa=%d\n", mcmf.edges.size());
	mcmfcost = mcmf.MincotMaxflow(Node - 2, Node - 1);
	printf("cost=%d\n", mcmfcost);
	printf("time=%lf\n", (double)(clock() - start) / CLOCKS_PER_SEC);


	release_buff(topo, line_num);
	return 0;
}