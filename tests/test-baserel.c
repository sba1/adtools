/* A simple test for the so-called baserel features of an AmigaOS4 compiler.
 *
 * It shall produce following output
 *
 * ```stdout
 * .data
 * 3722304989
 * 4008636142
 * .bss
 * 2271560481
 * 305419896
 * ```
 */

#include "common.h"

/******************************************************************************/

int bss[10];
int data[10] =
{
	1,2,3,4,5,6,7,8,9,10
};

/******************************************************************************/

void write_to_global_bss(void)
{
	bss[0] = 2271560481; /* 0x87654321; */
}

__attribute__((baserel_restore))
void write_to_global_bss_with_restore(void )
{
	bss[1] = 305419896; /* 0x12345678; */
}

/******************************************************************************/

void write_to_global_data(void)
{
	data[0] = 3722304989; /* 0xDDDDDDDD; */
}

__attribute__((baserel_restore))
void write_to_global_data_with_restore(void)
{
	data[1] = 4008636142; /* 0xEEEEEEEE; */
}

/******************************************************************************/

/* This simulates the data space that is usually allocated dynamically */
__attribute__((force_no_baserel)) int all_data[100];

/******************************************************************************/

__attribute__((baserel_restore))
void _start(void)
{
	init_mmu();

	write_to_global_bss();
	write_to_global_bss_with_restore();

	write_to_global_data();
	write_to_global_data_with_restore();

	/* That's part of the .data section. It is always first, regardless of how we
	 * arrange the global data */
	puts(".data\n");
	putuint(all_data[0]);
	putchar('\n');
	putuint(all_data[1]);
	putchar('\n');

	/* That's part of the .bss section */
	puts(".bss\n");
	putuint(all_data[10]);
	putchar('\n');
	putuint(all_data[11]);
	putchar('\n');
}

/******************************************************************************/

void __baserel_get_addr(void)
{
	int *d = all_data;
	asm volatile ("mr 2, %0" : : "r"(d));
}
