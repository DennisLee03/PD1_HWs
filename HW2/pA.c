#include <stdio.h>
int main()
{
	int n1, n2, d1, d2;
	int N, D;
	scanf("%d/%d+%d/%d", &n1, &d1, &n2, &d2);
	N = n1 * d2 + n2 * d1;
	D = d1 * d2;
	printf("%d/%d\n", N, D);
	return 0;
}
