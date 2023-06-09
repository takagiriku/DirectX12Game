#include"GameMnager.h"
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	GameBase* Game = new GameMnager();

	Game->Run();

	delete Game;

	return 0;
}