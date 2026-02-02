#include "../../photon-ascii/self.hpp"

void create() {
    for (int y = 0; y < SCENE_HEIGHT; y++) {
        for (int x = 0; x < SCENE_WIDTH; x++) {
            pa::Pixel* p = pa::getPixelAt(x, y);
            if (!p) { continue; }
            pa::Vec3 color(255, 255, 255);

            p->pos() = pa::Vec2(x, y);
            p->baseColor() = color;
            p->color() = color;
            p->c() = '@';
        }
    }
}

void loadScene() {
//	pa::lights.push_back(pa::Light({SCENE_WIDTH / 2, 0}, -1, 0.6f, {255, 255, 255}));//Sun

	pa::line({10, 4}, {70, 40}, {255, 0, 0}, '#', 0.2f);
	pa::line({9, 4}, {69, 40}, {0, 0, 255}, '#', 0.2f);
	pa::line({50, 7}, {50, 17}, {0, 255, 0}, '#', 0.4f);
	pa::line({60, 10}, {60, 13}, {0, 255, 255}, '#', 0.4f);

	//Barrel
	int startX = 87;
    int startY = 10;
    int width = 2;
	pa::Vec3 grey(62, 62, 62);

    pa::line({startX, startY}, {startX + width, startY}, grey, '#', 1.0f);
    pa::line({startX, startY + 2}, {startX + width, startY + 2}, grey, '#', 1.0f);
    pa::line({startX + width + 1, startY}, {startX + width + 1, startY + 2}, grey, '#', 1.0f);
    //
	pa::lights.push_back(pa::Light({startX + width, startY + 1}, -1, 1.5f, {255, 255, 255}));
}

int main() {
	pa::start();
	pa::hideCursor();
	pa::cls();
	pa::setCursorHandler();

	create();
	loadScene();

	pa::display();

	pa::showCursor();
	std::cout << "\n";
	return 0;
}
