#include <stdio.h>

int main() {
	printf("int		%d bytes \n",sizeof(int));
	printf("short		%d bytes\n", sizeof(short));
	printf("long		%d bytes\n", sizeof(long));
	printf("long long	%d bytes\n", sizeof(long long));
	printf("unsigned int	%d bytes\n", sizeof(unsigned int));
	printf("char		%d bytes\n", sizeof(char));
	printf("float		%d bytes\n", sizeof(float));
	printf("double		%d bytes\n", sizeof(double));
	printf("long double	%d bytes\n", sizeof(long double));
	return 0;
}
