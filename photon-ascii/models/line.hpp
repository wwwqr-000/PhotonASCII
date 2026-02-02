#pragma once

namespace pa {

void line(Vec2 from, Vec2 to, Vec3 color, char c = '@', float opacity = 0.0f) {
	int x0 = from.xi();
	int y0 = from.yi();
	int x1 = to.xi();
	int y1 = to.yi();

	int dx = std::abs(x1 - x0);
	int dy = std::abs(y1 - y0);

	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;

	int err = dx - dy;

	while (true) {
		setPixel(Vec2(x0, y0), color, c, opacity);

		if (x0 == x1 && y0 == y1) { break; }
		int e2 = err * 2;

		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}

		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}

}

}
