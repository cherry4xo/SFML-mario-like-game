#include "main.h"

int main(int argc, char* argv[])
{
	Lesson::TApplication app;
	app.Init();
	app.Run();
	app.End();

	return 0;
}