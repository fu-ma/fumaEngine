#include"GameScene.h"
#include"Json.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Framework *scene = new GameScene();
	Json *json = new Json();
	json = Json::GetInstance();
	scene->GameRun();
	json->Write();

	delete scene;
	scene = nullptr;
	return 0;
}