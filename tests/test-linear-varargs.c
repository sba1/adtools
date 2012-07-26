#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <amiga_compiler.h>

void test_array(int c, int *ptr)
{
	int i;
	for (i=0;i<c;i++)
		printf("%d\n",ptr[i]);
}

VARARGS68K
void testvarg_test(int arg, ...)
{
    __builtin_va_list ap;
    int *ptr;

   va_startlinear(ap, arg);
   ptr = va_getlinearva(ap, int *);
   test_array(arg,ptr);
}

int main(void)
{
	testvarg_test(5,10,20,30,40,50);
	return 0;
}
