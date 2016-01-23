#include <iostream>
#include <thread>

#include <proto/dos.h>

void call_from_thread() {
	IDOS->Delay(100);
	std::cout << "Hello, World" << std::endl;
	IDOS->Delay(100);
	std::cout << "Thread is about to finish" << std::endl;
}

int main() {
	std::thread t1(call_from_thread);
	std::cout << "Start join" << std::endl;
	t1.join();
	std::cout << "Join done" << std::endl;
	return 0;
}
