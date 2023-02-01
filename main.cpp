#include"GameScene.h"
#include"Json.h"

//Windowsアプリでのエントリーポイント(main関数)
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