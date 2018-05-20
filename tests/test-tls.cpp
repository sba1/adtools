#include <thread>

#include <proto/dos.h>

#include <stdio.h>


class Test
{
  int testVar;
public:
  Test()
  {
    IDOS->Printf("Construct Test\n");
    testVar = 1;
  }

  ~Test()
  {
    IDOS->Printf("Destruct Test\n");
  }

  void test()
  {
    IDOS->Printf("test()\n");
  }
};

thread_local Test test;

static void call_from_thread()
{
  IDOS->Printf("Inside thread\n");
  test.test();
}

int main(void)
{
  IDOS->Printf("Inside main()\n");

  test.test();

  std::thread t1(call_from_thread);

  t1.join();

  IDOS->Printf("Exit main()\n");

  return 0;
}
