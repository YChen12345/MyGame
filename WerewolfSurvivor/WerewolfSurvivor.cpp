#include "GameManager.h"

int main(int argc, char* argv[]) {
	int stop = 0;
	int keystate_tab = 0;
	GamesEngineeringBase::Window canvas;
	canvas.create(1024, 768, "WerewolfSurvivor");
	GamesEngineeringBase::Timer time;
	gameSystem newgame(canvas,time);
	newgame.initgame();
	while (true)
	{
		time.dt();
		canvas.checkInput();
		newgame.keycontrol();
		if (stop == 0) {
			newgame.gameloop();
		}
		else
		{
			canvas.present();
		}
		if (canvas.keyPressed(VK_TAB)&&keystate_tab==0) {
			if (stop == 0) {
				stop = 1;
				std::cout<<"stopped" << std::endl;
			}
			else
			{
				stop = 0;
				std::cout << "continue" << std::endl;
			}		
			keystate_tab = 1;
		}
		if (!canvas.keyPressed(VK_TAB)) {
			keystate_tab = 0;
		}
		if (canvas.keyPressed(VK_ESCAPE)) {
			break;
		}
	}
	return 0;
}