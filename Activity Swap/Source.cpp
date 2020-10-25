#include <stdio.h>

void swap(int *a, int *b)
{
	int c;
	c = *a;
	*a = *b;
	*b = c;

}

int main()
{
	int a, b;
	scanf_s("%d %d", &a, &b);
	swap(&a, &b);
	printf("%d %d", a, b);


}