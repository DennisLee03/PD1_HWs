#include <stdio.h>
int main()
{
	int a, b, N;
	int ans;
	scanf("%d,%d,%d", &a, &b, &N);
	ans = b * ( 1 << a ) + ( a | b ) - N/( 1 << b )	* ( a ^ b ) - ( a & b );
	printf("%d\n", ans);
	return 0;
}
