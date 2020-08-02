#include "engine/App.h"

int main()
{
    we::App app;
    app.CreateWindow(1280, 720, "Test Application");
    app.Run();

	return 0;
}