#include <iostream>  
#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <math.h>  
#include <ctype.h>  
#include <queue>  
#include <map>  
#include <algorithm>  

using namespace std;
const int INF = 0x3f3f3f3f;
int head[500], source, sink, cnt, flow, cost;
int d[500], pre[500], q[1000000], cur[500], vis[500], f[500];
struct node
{
	int u, v, cap, cost, next;
}edge[1000000];
void add(int u, int v, int cap, int cost)
{
	edge[cnt].v = v;
	edge[cnt].cap = cap;
	edge[cnt].cost = cost;
	edge[cnt].next = head[u];
	head[u] = cnt++;

	edge[cnt].v = u;
	edge[cnt].cap = 0;
	edge[cnt].cost = -cost;
	edge[cnt].next = head[v];
	head[v] = cnt++;
}
int spfa()
{
	memset(d, INF, sizeof(d));
	memset(vis, 0, sizeof(vis));
	int minflow = INF, f1 = 0, f2 = 0, i;
	q[f1++] = source;
	f[source] = INF;
	d[source] = 0;
	cur[source] = -1;
	while (f1 >= f2)
	{
		int u = q[f2++];
		vis[u] = 0;
		for (i = head[u]; i != -1; i = edge[i].next)
		{
			int v = edge[i].v;
			if (d[v]>d[u] + edge[i].cost&&edge[i].cap)
			{
				d[v] = d[u] + edge[i].cost;
				f[v] = min(f[u], edge[i].cap);
				cur[v] = i;
				if (!vis[v])
				{
					q[f1++] = v;
					vis[v] = 1;
				}
			}
		}
	}
	if (d[sink] == INF) return 0;
	flow += f[sink];
	cost += f[sink] * d[sink];
	for (i = cur[sink]; i != -1; i = cur[edge[i ^ 1].v])
	{
		edge[i].cap -= f[sink];
		edge[i ^ 1].cap += f[sink];
	}
	return 1;
}
void mcmf()
{
	flow = cost = 0;
	while (spfa());
	printf("%d\n", cost);
}
int main()
{
	int T, n, m, i, j, a, b, c;
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d%d", &n, &m);
		memset(head, -1, sizeof(head));
		cnt = 0;
		source = 0;
		sink = 2 * n + 1;
		flow = 0;
		cost = 0;
		for (i = 1; i <= n; i++)
		{
			add(source, i, 1, 0);
			add(i + n, sink, 1, 0);
		}
		while (m--)
		{
			scanf("%d%d%d", &a, &b, &c);
			add(a, b + n, 1, c);
		}
		mcmf();
	}
	return 0;
}

