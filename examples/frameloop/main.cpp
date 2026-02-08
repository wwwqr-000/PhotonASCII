#include "../../photon-ascii/self.hpp"

//Unset the scene dimensions
#undef SCENE_WIDTH
#undef SCENE_HEIGHT
//

//Set the scene dimensions again
#define SCENE_WIDTH 1000
#define SCENE_HEIGHT 200
//

void create() {
	pa::Vec3 color(255, 255, 255);

    for (int y = 0; y < SCENE_HEIGHT; y++) {
        for (int x = 0; x < SCENE_WIDTH; x++) {
            pa::Pixel* p = pa::getPixelAt(x, y);
            if (!p) { continue; }

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

void createTestStructure(pa::Vec2 pos) {
	std::vector<pa::Pixel> pixels;
	pa::Vec3 color(0, 255, 255);

	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 1; x++) {
			pixels.emplace_back(pa::Pixel({x, y}, color, '#', 0.4f));
		}
	}

	pa::structures.push_back(pa::Structure(pixels, pos));
}

void display() {//Overwriting the default display method is possible, shown here.
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            pa::Pixel *p = pa::getPixelAt(x + pa::screenOffset.xi(), y + pa::screenOffset.yi());
            if (!p) { continue; }
           	pa::traceColor(*p, pa::lights);
            std::cout << "\033[" << y + 1 << ";" << x + 1 << "H"
                << "\033[38;2;" << p->color().xi() << ";" << p->color().yi() << ";" << p->color().zi() << "m"
                << p->c() << "\033[0m";
        }
	}
}

int main() {
	pa::start();
	pa::hideCursor();
	pa::cls();
	pa::setCursorHandler();

	create();
	loadScene();

	createTestStructure({45, 19});

	int tickCount = 0;
    int v = 1;

	pa::displayCallback = display;//Overwriting the default display method (This is how you do it)

    while (pa::running) {
		pa::updateStructures();
        pa::display();
        pa::sleep(75);
        if (tickCount >= 20) {
        	tickCount = 0;
            v = v == 1 ? -1 : 1;
        }

        pa::structures[0].pos().xi() += v;
		if (tickCount % 2 == 0) {
			pa::structures[0].pos().yi() -= v;
		}

		if (tickCount % 10 == 0) {
			pa::screenOffset.xi() += 1;//Change the screen offset so the perspective on the scene changes.
		}
        tickCount += 1;
	}

	pa::showCursor();
	std::cout << "\n";
	return 0;
}
