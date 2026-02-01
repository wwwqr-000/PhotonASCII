#pragma once

namespace pa {
	void candle(Vec2 pos, Vec3 color, int offset) {
    	char c = '#';
		Vec2 lightPos(pos.xi() + offset, pos.yi() - 1);

    	setPixel(pos, {255, 255, 255}, c);//Base
    	setPixel(lightPos, color, c); //Flame
    	lights.push_back(Light(lightPos, 35, 1.0f, color));
	}
}
