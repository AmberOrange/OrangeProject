#include "MainThread.hpp"

int main(int argc, char *argv[])
{
	MainThread mainThread;
	if (!mainThread.init())
		return -1;

	mainThread.run();

	return 0;
}