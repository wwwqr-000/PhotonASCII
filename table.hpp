void table(Vec2 pos, Vec2 dimensions, int overhang) {
    Vec3 color(157, 84, 0);
    const char filler = '#';

    int x0 = pos.xi();
    int y0 = pos.yi();

    int w = dimensions.xi();
    int h = dimensions.yi();

    //Top
    for (int x = 0; x < w; x++) {
        setPixel({x0 + x, y0}, color, filler, 1.0f);
    }
	//

    //Legs
    int leftLegX  = x0 + overhang;
    int rightLegX = x0 + w - overhang - 1;

    for (int y = 1; y <= h; y++) {
        setPixel({leftLegX, y0 + y}, color, filler, 1.0f);
        setPixel({rightLegX, y0 + y}, color, filler, 1.0f);
    }
	//
}
