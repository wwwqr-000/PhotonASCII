#pragma once

class Pixel {
	private:
		Vec2 pos_;
		Vec3 color_;//True color (After light calc)
		Vec3 baseColor_;//Original color
		char c_;
		float opacity_;

	public:
		Pixel() : pos_(0, 0), color_(0, 0, 0), baseColor_(0, 0, 0), c_(' '), opacity_(0.0f) {}

		Pixel(Vec2 pos, Vec3 color, char c, float opacity = 0.0f) : pos_(pos), color_(color), c_(c), baseColor_(color), opacity_(opacity) {}

		Vec2 &pos() { return this->pos_; }
		Vec3 &color() { return this->color_; }
		Vec3 &baseColor() { return this->baseColor_; }
		char &c() { return this->c_; }
		float &opacity() { return this->opacity_; }
};

std::vector<Pixel> pixels;

Pixel* getPixelAt(int x, int y) {
    if (x < 0 || y < 0 || x >= SCENE_WIDTH || y >= SCENE_HEIGHT) { return nullptr; }
    return &pixels[y * SCENE_WIDTH + x];
}

void setPixel(Vec2 pos, Vec3 color, char c, float opacity = 0.0f) {
	Pixel *p = getPixelAt(pos.xi(), pos.yi());
	if (!p) { return; }

	p->color() = color;
	p->baseColor() = color;
	p->c() = c;
	p->opacity() = opacity;
}
