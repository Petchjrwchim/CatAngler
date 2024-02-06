#include <iostream>
#include "SDL.h"
#include "Engine.h"
#include "Timer.h"

using namespace std;

int main(int argc, char* args[]) {

	Engine::GetInstance()->init();

	while (Engine::GetInstance()->IsRunning()) {
		Engine::GetInstance()->event();
		Engine::GetInstance()->update();
		Engine::GetInstance()->render();
		Timer::GetInstance()->Tick();

	}

	Engine::GetInstance()->clean();
	return 0;
}
