#include"Framework.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Framework *scene = new Framework();
	scene->GameRun();

	delete scene;
	scene = nullptr;
	return 0;
}