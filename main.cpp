#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <thread>
#include <atomic>
#include <csignal>

#define SCENE_WIDTH 100
#define SCENE_HEIGHT 20

//Preloads
int ftoi(float);
//

#include "vec2.hpp"
#include "vec3.hpp"
#include "pixel.hpp"
#include "light.hpp"

//Global vars
//std::vector<Pixel> pixels;// in pixel.hpp
std::vector<Light> lights;
std::atomic<bool> running(true);
//

#include "tree.hpp"
#include "table.hpp"
#include "candle.hpp"

#include "world-gen.hpp"

void create() {
    pixels.assign(SCENE_WIDTH * SCENE_HEIGHT, Pixel());

    for (int y = 0; y < SCENE_HEIGHT; y++) {
        for (int x = 0; x < SCENE_WIDTH; x++) {
            Pixel* p = getPixelAt(x, y);
            if (!p) { continue; }
			//Vec3 color(2 * x, y * 2, 255);
			Vec3 color(255, 255, 255);

			if (y == 19) {
				color = Vec3(0, 255, 0);
			}

            p->pos() = Vec2(x, y);
            p->baseColor() = color;
            p->color() = color;
            p->c() = '@';
        }
    }
}

void cls() {
	system("clear");
}

int ftoi(float f) {//Float to int
	return static_cast<int>(std::round(f));
}

void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void hideCursor() {
	std::cout << "\033[?25l" << std::flush;
}

void showCursor() {
	std::cout << "\033[?25h" << std::flush;
}

void handleSigint(int) {
	showCursor();
	running = false;
}

void display() {
	for (Pixel &p : pixels) {
    	traceColor(p, lights);
    	std::cout << "\033[" << p.pos().yi() + 1 << ";" << p.pos().xi() + 1 << "H"
              	<< "\033[38;2;" << p.color().xi() << ";" << p.color().yi() << ";" << p.color().zi() << "m"
              	<< p.c() << "\033[0m";
	}
}

int main() {
	cls();
	hideCursor();
	std::signal(SIGINT, handleSigint);//Handle ctrl-c (To set cursor back to default)

	create();
	worldGen();
	display();

	showCursor();
	std::cout << "\n";
	return 0;
}
