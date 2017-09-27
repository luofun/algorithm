#include<stdio.h>
#include<math.h>

int main(int argc, char* argv[])
{
	double t;
	double err = 1e-15;
	printf("%lf", err);
	double c;
	printf("\ninput num:");
	scanf("%lf", &t);
	c = t;

	printf("\n\nthe sprt is:");

	while (abs(t - c / t) > err*t)
	{
		t = (c / t + t) / 2.0;


	}

	printf("%f\n\n", t);

	return 0;
}