#include "../../photon-ascii/self.hpp"

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
	pa::lights.push_back(pa::Light({SCENE_WIDTH / 2, 0}, -1, 0.2f, {255, 255, 255}));//Sun
	pa::lights.push_back(pa::Light({0, SCENE_HEIGHT / 2}, -1, 0.2f, {255, 255, 255}));
	pa::lights.push_back(pa::Light({SCENE_WIDTH, SCENE_HEIGHT / 2}, -1, 0.2f, {255, 255, 255}));

	pa::Vec3 floorColor(69, 50, 0);
	pa::Vec3 wallColor(116, 56, 16);
	pa::Vec3 roofColor(51, 51, 51);

	pa::line({30, 19}, {70, 19}, floorColor, '#', 1.0f);//Floor
	pa::line({30, 18}, {30, 10}, wallColor, '#', 1.0f);//Wall left
	pa::line({70, 18}, {70, 10}, wallColor, '#', 1.0f);//Wall right

	pa::line({25, 10}, {50, 3}, roofColor, '#', 1.0f);//Roof left
	pa::line({75, 10}, {50, 3}, roofColor, '#', 1.0f);//Roof right

	pa::table({49, 16}, {8, 2}, 2);
}

void createLampStructure(pa::Vec2 pos) {
	std::vector<pa::Pixel> pixels;
	pa::Vec3 color(33, 197, 0);//Lamp frame color
	pa::Vec3 lColor(255, 234, 113);//Lamp light color
	float frameDensity = 0.5;

	for (int i = 0; i < 3; i++) {
		pixels.emplace_back(pa::Pixel({0, i}, color, '#', frameDensity));
		pixels.emplace_back(pa::Pixel({-1 + i, 3}, color, '#', frameDensity));
	}

	pixels.emplace_back(pa::Pixel({-2, 3}, color, '#', frameDensity));
	pixels.emplace_back(pa::Pixel({2, 3}, color, '#', frameDensity));

	pixels.emplace_back(pa::Pixel({-3, 3}, color, '#', frameDensity));
    pixels.emplace_back(pa::Pixel({3, 3}, color, '#', frameDensity));

	pixels.emplace_back(pa::Pixel({-3, 4}, color, '#', frameDensity));
	pixels.emplace_back(pa::Pixel({3, 4}, color, '#', frameDensity));

	pa::lights.push_back(pa::Light({0 + pos.xi(), 4 + pos.yi()}, 30, 1.5f, lColor));

	pa::structures.push_back(pa::Structure(pixels, pos));
}

int main() {
	pa::start();
	pa::hideCursor();
	pa::cls();
	pa::setCursorHandler();

	create();
	loadScene();

	createLampStructure({50, 4});
	pa::updateStructures();
	pa::display();

	pa::showCursor();
	std::cout << "\n";
	return 0;
}
