#ifdef _WIN32

// handles WinMain, so a user does not have to

#include "util/Windows.hpp"

#include <cstdlib>

extern int main(int argc, char** argv);

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	return main(__argc, __argv);
}

#endif
