#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>
#include <atomic>
#include <csignal>

//Dimensions of the screen/ canvas in char-count
#define SCENE_WIDTH 100
#define SCENE_HEIGHT 20
//

//The aspect ratio of the terminal (Default value 2.0f)
#define TERMINAL_ASPECT 2.0f
//

//The command to clear the terminal on your OS (windows: cls, linux: clear)
#define CLS_CMD "clear"
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
}
//

#include "models/include.hpp"
#include "structure.hpp"
namespace pa {
	void start() { pixels.assign(SCENE_WIDTH * SCENE_HEIGHT, Pixel()); }
	void cls() { system(CLS_CMD); }
	int ftoi(float f) { return static_cast<int>(std::round(f)); }
	void sleep(int ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }
	void hideCursor() { std::cout << "\033[?25l" << std::flush; }
	void showCursor() { std::cout << "\033[?25h" << std::flush; }
	void handleSigint(int) { showCursor(); running = false; }
	void setCursorHandler() { std::signal(SIGINT, handleSigint); }
	void display() {
		for (Pixel &p : pixels) {
    		traceColor(p, lights);
    		std::cout << "\033[" << p.pos().yi() + 1 << ";" << p.pos().xi() + 1 << "H"
              		<< "\033[38;2;" << p.color().xi() << ";" << p.color().yi() << ";" << p.color().zi() << "m"
              		<< p.c() << "\033[0m";
		}
	}
}
