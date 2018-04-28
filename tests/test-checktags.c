void TestTags(int type, ...) __attribute__((checktags));

struct S1;
struct S2;

enum {TA_Dummy = 0x12340000};

enum {TA_S1 __attribute__((tagtype(struct S1 *))) = TA_Dummy + 0x0D};

#pragma amigaos tagtype(struct S2 *)
static const int TA_S2 = TA_Dummy + 0x0E;

extern struct S1 *s1;
extern struct S2 *s2;

int main(void)
{
	TestTags(0, TA_S1, s2, TA_S2, s1);
	return 0;
}
