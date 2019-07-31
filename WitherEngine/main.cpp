#include "Engine/App.h"

int main()
{
	we::App demo;
	demo.CreateWindow(1280, 720, "demo app");
	demo.Run();

	return 0;
}