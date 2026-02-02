#include "../../photon-ascii/self.hpp"

void create() {
    for (int y = 0; y < SCENE_HEIGHT; y++) {
        for (int x = 0; x < SCENE_WIDTH; x++) {
            pa::Pixel* p = pa::getPixelAt(x, y);
            if (!p) { continue; }
			//Vec3 color(2 * x, y * 2, 255);
			pa::Vec3 color(255, 255, 255);

			if (y == 19) {
				color = pa::Vec3(0, 255, 0);
			}

            p->pos() = pa::Vec2(x, y);
            p->baseColor() = color;
            p->color() = color;
            p->c() = '@';
        }
    }
}

void worldGen() {//You can use {} instead of Vec2 or Vec3, etc
    //Trees
	pa::tree(pa::Vec2(30, 18), 5, 2, 3);
	pa::tree(pa::Vec2(40, 18), 6, 3, 4);
    pa::tree(pa::Vec2(55, 18), 2, 1, 2);
    pa::tree(pa::Vec2(20, 18), 1, 1, 2);
    pa::tree(pa::Vec2(70, 18), 10, 4, 6);
	//

    //Lights
	pa::lights.push_back(pa::Light({42, 0}, -1, 0.5f, {255, 255, 255}));
	//

    //Tables
    pa::table({7, 16}, {8, 2}, 2);
	//

    //Candles
    pa::candle({10, 15}, {255, 0, 0}, 0);
    pa::candle({32, 16}, {112, 0, 156}, 1);
	pa::candle({94, 13}, {255, 255, 255}, 0);
	//

	/*
    //Second worldGen
    pa::lights.push_back(pa::Light({42, 1}, 200, 1.0f, {255, 255, 255}));
    pa::tree(pa::Vec2(55, 18), 8, 4, 5);

    pa::Vec3 purple(133, 10, 181);

    for (int i = 0; i < 10; i++) {
            pa::setPixel({30 + i, 10}, purple, '#', 0.22f);
    }
    //
    */
}

int main() {
	pa::start();
	pa::cls();//You don't have to trigger this cls if you're using a tick-loop for frames, pa::display doesn't need it to update
	pa::hideCursor();
	pa::setCursorHandler();//When ctrl-c is triggered, show cursor again

	create();
	worldGen();
	pa::display();

	pa::showCursor();
	std::cout << "\n";
	return 0;
}
