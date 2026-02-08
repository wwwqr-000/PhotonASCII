#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>
#include <atomic>
#include <csignal>

//Dimensions of the screen and scene in char-count

//The dimensions of the screen displayed
//#define SCREEN_WIDTH 100
//#define SCREEN_HEIGHT 20
//

//The dimensions of the scene (The total space for structures, the world, the scene, whatever you want to call it)
//#define SCENE_WIDTH 100
//#define SCENE_HEIGHT 20
//

//

//The aspect ratio of the terminal (Default value 2.0f)
//#define TERMINAL_ASPECT 2.0f
//

//The command to clear the terminal on your OS (windows: cls, linux: clear)
//#define CLS_CMD "clear"
//

//Other defines
#define RGB_FLOAT_ROOF 255.0f
//

//Preloads
namespace pa {
	int ftoi(float);
}
//

#include "vec2.hpp"
#include "vec3.hpp"
#include "pixel.hpp"
#include "light.hpp"

//Global vars
//std::vector<Pixel> pixels;// in pixel.hpp
namespace pa {
	std::vector<Light> lights;
	std::atomic<bool> running(true);
	Vec2 screenOffset(0, 0);
}
//

#include "models/include.hpp"
#include "structure.hpp"

namespace pa {
	using Callback = void(*)();//Used to overwrite display method

	void start() { pixels.assign(SCENE_WIDTH * SCENE_WIDTH, Pixel()); }
	void cls() { system(CLS_CMD); }
	int ftoi(float f) { return static_cast<int>(std::round(f)); }
	void sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
	void hideCursor() { std::cout << "\033[?25l" << std::flush; }
	void showCursor() { std::cout << "\033[?25h" << std::flush; }
	void handleSigint(int) { showCursor(); running = false; }
	void setCursorHandler() { std::signal(SIGINT, handleSigint); }
	void displayDefault() {
		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				Pixel *p = getPixelAt(x + screenOffset.xi(), y + screenOffset.yi());
				if (!p) { continue; }

				traceColor(*p, lights);
				std::cout << "\033[" << y + 1 << ";" << x + 1 << "H"
                    << "\033[38;2;" << p->color().xi() << ";" << p->color().yi() << ";" << p->color().zi() << "m"
                    << p->c() << "\033[0m";
			}
		}
	}

	Callback displayCallback = displayDefault;
    void display() {
        displayCallback();
    }
}
