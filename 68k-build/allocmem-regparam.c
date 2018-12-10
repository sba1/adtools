struct ExecBase *SysBase;

#define APTR void *
#define ULONG unsigned int
#define EXEC_BASE_NAME SysBase

//static __inline
APTR AllocMem(ULONG byteSize, ULONG requirements)
{
  return ((APTR ( __attribute__((aregparam("d0", "d1", "a6"))) *)(ULONG d0, ULONG d1, struct ExecBase *a6))
      (((char *) EXEC_BASE_NAME) - 198))(byteSize, requirements, EXEC_BASE_NAME);
}

#define MEMF_CLEAR 0x10000

// int _start()
// {
// 	void *m = AllocMem(1023, MEMF_CLEAR);
// 	if (!m) return 1;
// 
// //	m = AllocMem(1023, MEMF_CLEAR);
// //	if (!m) return 1;
// 	return 0;
// }
