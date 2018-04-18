/* A simple test for the so-called baserel features of an AmigaOS4 compiler. */

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
	bss[0] = 0x87654321;
}

__attribute__((baserel_restore))
void write_to_global_bss_with_restore(void )
{
	bss[1] = 0x12345678;
}

/******************************************************************************/

void write_to_global_data(void)
{
	data[0] = 0xDDDDDDDD;
}

__attribute__((baserel_restore))
void write_to_global_data_with_restore(void)
{
	data[1] = 0xEEEEEEEE;
}

/******************************************************************************/

__attribute__((baserel_restore))
void _start(void)
{
	init_mmu();

	write_to_global_bss();
	write_to_global_bss_with_restore();

	write_to_global_data();
	write_to_global_data_with_restore();
}

/******************************************************************************/

/* This simulates the data space that is usually allocated dynamically */
__attribute__((force_no_baserel)) static int all_data[100];

void __baserel_get_addr(void)
{
	int *d = all_data;
	asm volatile ("mr 2, %0" : : "r"(d));
}
