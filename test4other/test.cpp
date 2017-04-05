#include "stdio.h"
#include "string"
#pragma warning(disable:4996)
using namespace std;
int main(int argc, char *argv[])
{
	char *topo_file = argv[0];
	printf("%s\n",topo_file);
	int a, b, c;
	int d, e, f;
	char str[] = "123 456 789\n     0010                 \0";
	sscanf("12 34 56","%d %d %d",&a,&b,&c);
	printf("%d\n%d\n%d\n",a,b,c);
	sscanf(str,"%d%d%d",&d,&e,&f);
	printf("%d\n%d\n%d\n", d, e, f);
	FILE *fp;
	fp = fopen("a.txt", "rt");
	char temp1[100];
	char temp2[100];
	fscanf(fp, "%s%s", temp1, temp2);
	printf("%s\n%s\n",temp1,temp2);
	fscanf(fp,"%s%s", temp1, temp2);
	if (strcmp(temp1, "¡Þ") == 0)
		printf("1\n");
	if (strcmp(temp2, "¡Þ") == 0)
		printf("2\n");
	fclose(fp);
	return 0;
}