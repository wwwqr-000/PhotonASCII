void worldGen() {
    //Trees
	tree(Vec2(30, 18), 5, 2, 3);
	tree(Vec2(40, 18), 6, 3, 4);
    tree(Vec2(55, 18), 2, 1, 2);
    tree(Vec2(20, 18), 1, 1, 2);
    tree(Vec2(70, 18), 10, 4, 6);
	//

    //Lights
	lights.push_back(Light({42, 0}, -1, 0.5f, {255, 255, 255}));
	//

    //Tables
    table({7, 16}, {8, 2}, 2);
	//

    //Candles
    candle({10, 15}, {255, 0, 0}, 0);
    candle({32, 16}, {112, 0, 156}, 1);
	candle({94, 13}, {255, 255, 255}, 0);
	//

	/*
	//Second worldGen
	lights.push_back(Light({42, 1}, 200, 1.0f, {255, 255, 255}));
	tree(Vec2(55, 18), 8, 4, 5);

	Vec3 purple(133, 10, 181);

	for (int i = 0; i < 10; i++) {
		setPixel({30 + i, 10}, purple, '#', 0.22f);
	}
	//
	*/
}
