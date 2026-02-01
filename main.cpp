#include "photon-ascii/self.hpp"

void create() {
    pa::pixels.assign(SCENE_WIDTH * SCENE_HEIGHT, pa::Pixel());

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
    pa::lights.push_back(pa::Light({5, 15}, 100, 0.8f, {234, 191, 0}));
    pa::lights.push_back(pa::Light({90, 15}, 70, 0.8f, {255, 255, 255}));

    for (int i = 0; i < 5; i++) {
        for (int e = 0; e < 15; e++) {
            pa::setPixel({10 + (i * 10), 18 - e}, {255, i * e, e * i}, '#', 0.18f);
        }
    }

    pa::tree(pa::Vec2(70, 18), 10, 4, 6);
    pa::lights.push_back(pa::Light({5, 12}, 60, 1.0f, {0, 255, 0}));
}

int main() {
	pa::cls();//You don't have to trigger this cls if you're using a tick-loop for frames, pa::display doesn't need it to update
	pa::hideCursor();
    pa::setCursorHandler();//When ctrl-c is triggered, show cursor again

    create();
    worldGen();

    int tickCount = 0;
    int v = 1;

    while (pa::running) {
        pa::display();
        pa::sleep(8);
        if (tickCount >= 120) {
        	tickCount = 0;
            v = v == 1 ? -1 : 1;
        }

        pa::lights[2].pos().xi() += v;
        tickCount += 1;
	}

	pa::showCursor();
	std::cout << "\n";
	return 0;
}
