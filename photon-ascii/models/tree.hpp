#pragma once

namespace pa {

void tree(Vec2 origin, int height, int width, int leaveHeight) {
    Vec3 color(137, 75, 4);

	//Stem
	for (int i = 0; i < height; i++) {
    	for (int w = 0; w < width; w++) {
        	setPixel({origin.xi() + w, origin.yi() - i}, color, '#', 0.8f);
    	}
	}
	//

	//Leaves
	Vec3 foliage(0, 112, 34);
	for (int y = 0; y < leaveHeight; y++) {
    	for (int x = 0; x < width * 3; x++) {
        	setPixel({origin.xi() - width + x, origin.yi() - height - y}, foliage, '@', 0.07f);
    	}
	}
	//
}

}
