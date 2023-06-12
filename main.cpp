#include"Framework.h"

//Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Framework *scene = new Framework();
	scene->GameRun();

	delete scene;
	scene = nullptr;
	return 0;
}