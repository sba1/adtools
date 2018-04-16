/* A simple test for all essential features of an
 * AmigaOS4 compiler.
 * The test is non-working. You need to view the
 * assembler output or machine code to verify the
 * correctness.
 */

#include "common.h"

/******************************************************************************/

#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
#define va_startlinear(AP,ARG) va_start(AP,ARG)
#define va_getlinearva(AP,TYPE) ((TYPE)__builtin_getlinearva(AP))

__attribute__((linearvarargs))
void testvarg_test(int count, ...)
{
	__builtin_va_list ap;
	unsigned int *ptr;
	int i;

	putuint(count);
	putchar(' ');

	/* Access the varargs as an array */
	va_startlinear(ap, count);
	ptr = va_getlinearva(ap, unsigned int *);

	for (i=0; i < count; i++)
	{
		putuint(ptr[i]);
		putchar(' ');
	}

	putchar('\n');
}

/******************************************************************************/

struct Test
{
	void __attribute__((libcall)) (*test)(struct Test *,int);
};


/* Forward declaration */
extern struct Test *test;

static void test_function(struct Test *test_, int new_value)
{
	putuint(test == test_);
	putchar(' ');
	putuint(new_value);
	putchar('\n');
}

struct Test test_instance =
{
	test_function
};

struct Test *test = &test_instance;

/******************************************************************************/

void _start(void)
{
	init_mmu();

	test->test(100);
	testvarg_test(5,10,20,30,40,50);
}
