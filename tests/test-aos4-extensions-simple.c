/* A simple test for all essential features of an
 * AmigaOS4 compiler.
 * The test is non-working. You need to view the
 * assembler output or machine code to verify the
 * correctness.
 */
 
#define va_start(v,l)   __builtin_va_start(v,l)
#define va_end(v)       __builtin_va_end(v)
#define va_arg(v,l)     __builtin_va_arg(v,l)
#define va_startlinear(AP,ARG) va_start(AP,ARG)
#define va_getlinearva(AP,TYPE) ((TYPE)__builtin_getlinearva(AP))

int num;

__attribute__((linearvarargs))
void testvarg_test(int a, int arg, ...)
{
    __builtin_va_list ap;
    int *ptr;

   va_startlinear(ap, arg);
   ptr = va_getlinearva(ap, int *);
   num =*ptr;
}

struct Test
{
	void * __attribute__((libcall)) (*test)(struct Test*,int);
};

struct Test *test = 0;

void _start(void)
{
	test->test(100);
	testvarg_test(5,10,20,30,40,50);
}
