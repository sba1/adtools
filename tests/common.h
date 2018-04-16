typedef unsigned int u32;

#define MAS0 624
#define MAS1 625
#define MAS2 626
#define MAS3 627
#define MAS4 628
#define MAS6 630
#define MAS7 944

#define mtspr(sp, va) \
	do \
	{ \
	        asm volatile (" mtspr %[spr], %[val] " : : [spr] "i" (sp), [val] "r" (va) ); \
	} \
	while(0)


#define isync() \
	do \
	{ \
		asm volatile ("isync" : : : "memory"); \
	} \
	while(0)

#define tlbwe() \
	do \
	{ \
		asm volatile ( "tlbwe" : : : "memory" ); \
	} \
	while(0)

/**
 * Initialize the tls for our default mapping.
 */
static void init_mmu(void)
{
	/* Map 0x0 to physical 0x0 */
	mtspr(MAS0, (1 << (63 - 35)) /* Select TLB1 */ | (0 << (63 - 47) /* Select entry 0 */));
	mtspr(MAS1, (1 << (63 - 32)) | (0<<(63-51)) | (0x0 << (63 - 47)) | (11 << (63 - 55)) /* Size 4GB */ );
	mtspr(MAS2, (0x0 << (63 - 51)) | (1 << (63 - 62)) /* Guarded */ | (1 << (63 - 59)) /* Write through */);
	mtspr(MAS3, (0x0 << (63 - 51)) | 0x3f); /* Real page number lower order bits */
	mtspr(MAS7, 0x0); /* Real page number higher order bits */
	isync();
	tlbwe();

	/* Map 0xfe00_0000 to physical 0xf_e000_0000 which is the default CCSR. Use
	 *  qemu-system-ppc -M ppce500,dumpdtb=dump.dtb && dtc -I dtb -O dts dump.dtb | less
	 * to obtain the base address.
	 */
	mtspr(MAS0, (1 << (63 - 35)) /* Select TLB1 */ | (1 << (63 - 47) /* Select entry 1 */));
	mtspr(MAS1, (1 << (63 - 32)) | (0<<(63-51)) | (0x0 << (63 - 47)) | (/*11*/5 << (63 - 55)) /* Size 1MB */ );
	mtspr(MAS2, (0xfe000 << (63 - 51)) | (1 << (63 - 62)) /* Guarded */ | (1 << (63 - 59)) /* Write through */);
	mtspr(MAS3, (0xe0000 << (63 - 51)) | 0x3f); /* Real page number lower order bits */
	mtspr(MAS7, 0xf); /* Real page number higher order bits */
	isync();
	tlbwe();
}

/**
 * Put the given character to the (emulated) serial output.
 */
static void putchar(char c)
{
	static const unsigned int base = 0xfe000000 + 0x4500;
	((char*)base)[0] = c;
}

static void puts(const char *str)
{
	unsigned char c;
	while ((c = *str++))
	{
		putchar(c);
	}
}
