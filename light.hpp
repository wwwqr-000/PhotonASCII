#pragma once


#define TERMINAL_ASPECT 2.0f

class Light {
	private:
		Vec2 pos_;
		int range_;//Any positive integer works. 0 is no range, dark/ off. -1 is infinite range
		float brightness_;//0.0f is off, 1.0f is default brightness, more than 1.0f is brighter
		Vec3 color_;//Rgb

	public:
		Light() : pos_(0, 0), range_(0), brightness_(0), color_(0, 0, 0) {}

		Light(Vec2 pos, int range, float brightness, Vec3 color) : pos_(pos), range_(range), brightness_(brightness), color_(color) {}

		Vec2 &pos() { return this->pos_; }
		int &range() { return this->range_; }
		float &brightness() { return this->brightness_; }
		Vec3 &color() { return this->color_; }
};

float calcLightIntens(Vec2 &pixelPos, Light &light) {
    float b = light.brightness();

    float dx = pixelPos.xi() - light.pos().xi();
    float dy = (pixelPos.yi() - light.pos().yi()) * TERMINAL_ASPECT;

    float dist = std::sqrt(dx*dx + dy*dy);

    float effectiveRange = light.range();
    float falloff = 1.0f - (dist / effectiveRange);
    falloff = std::clamp(falloff, 0.0f, 1.0f);

    return falloff * b;
}

bool traceLight(Vec2 from, Vec2 to, float &transmission, Vec3 &filter) {//Bresenham + Lambert-Beer
	transmission = 1.0f;
	filter = Vec3(255, 255, 255);//Lambert-Beer filter

	int x0 = from.xi();
    int y0 = from.yi();
    int x1 = to.xi();
    int y1 = to.yi();

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int err = dx - dy;

    while (!(x0 == x1 && y0 == y1)) {
        int e2 = err * 2;

        if (e2 > -dy) { err -= dy; x0 += sx; }
        if (e2 <  dx) { err += dx; y0 += sy; }

		if (x0 == x1 && y0 == y1) { break; }//Pixel that is in direct contact with light is visable

        Pixel* p = getPixelAt(x0,y0);
        if (!p) { continue; }

		float op = p->opacity();
		transmission *= (1.0f - op);

		if (op > 0.0f) {
			filter.xi() = ftoi(filter.xi() * ((1.0f - op) + (p->baseColor().xi()/255.0f) * op));
    		filter.yi() = ftoi(filter.yi() * ((1.0f - op) + (p->baseColor().yi()/255.0f) * op));
    		filter.zi() = ftoi(filter.zi() * ((1.0f - op) + (p->baseColor().zi()/255.0f) * op));
		}

        if (transmission <= 0.001f) { return false; }
    }

    return true;
}

void traceColor(Pixel &p, std::vector<Light> &lights) {
	Vec3 result(0, 0, 0);
    Vec3 &bc = p.baseColor();
    float rgbMax = 255.0f;

	for (Light &light : lights) {
    	float transmission;
		Vec3 filter;

    	if (!traceLight(light.pos(), p.pos(), transmission, filter)) { continue; }
    	float i = calcLightIntens(p.pos(), light) * transmission;

		float lr = light.color().xi() * (filter.xi() / 255.0f);
		float lg = light.color().yi() * (filter.yi() / 255.0f);
		float lb = light.color().zi() * (filter.zi() / 255.0f);

    	result.xi() += ftoi(bc.xi() * (lr / 255.0f) * i);
    	result.yi() += ftoi(bc.yi() * (lg / 255.0f) * i);
    	result.zi() += ftoi(bc.zi() * (lb / 255.0f) * i);
	}

	p.color().xi() = std::min(255, result.xi());
	p.color().yi() = std::min(255, result.yi());
	p.color().zi() = std::min(255, result.zi());
}
