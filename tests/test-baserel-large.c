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

int bss[60000];
int data[60000] =
{
	1,2,3,4,5,6,7,8,9,10
};

/******************************************************************************/

void write_to_global_bss(void)
{
	bss[50000] = 2271560481; /* 0x87654321; */
}

__attribute__((baserel_restore))
void write_to_global_bss_with_restore(void )
{
	bss[60000] = 305419896; /* 0x12345678; */
}

/******************************************************************************/

void write_to_global_data(void)
{
	data[50000] = 3722304989; /* 0xDDDDDDDD; */
}

__attribute__((baserel_restore))
void write_to_global_data_with_restore(void)
{
	data[60000] = 4008636142; /* 0xEEEEEEEE; */
}

/******************************************************************************/

/* This simulates the data space that is usually allocated dynamically */
__attribute__((force_no_baserel)) int all_data[120001];

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
	putuint(all_data[50000]);
	putchar('\n');
	putuint(all_data[60000]);
	putchar('\n');

	/* That's part of the .bss section */
	puts(".bss\n");
	putuint(all_data[50000+60000]);
	putchar('\n');
	putuint(all_data[60000+60000]);
	putchar('\n');

	while(1);
}

/******************************************************************************/

void __baserel_get_addr(void)
{
	int *d = all_data;
	asm volatile ("mr 2, %0" : : "r"(d));
}
