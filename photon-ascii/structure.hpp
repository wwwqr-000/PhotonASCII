#pragma once

namespace pa {

class Structure {
	private:
		std::vector<Pixel> ownPixels_;//Pixels from structure itself
		std::vector<Pixel> originalPixels_;//Pixels from before the placement of the structure
		Vec2 pos_;//Start pos of the structure
		Vec2 prevPos_;//The pos of the structure, when pos_ is changed, this one is one behind

	public:
		Structure() : pos_(0, 0), prevPos_(-1, -1) {}
		Structure(std::vector<Pixel> pixels, Vec2 pos) : ownPixels_(pixels), pos_(pos), prevPos_(-1, -1) {}

		std::vector<Pixel> &ownPixels() { return this->ownPixels_; }
		std::vector<Pixel> &originalPixels() { return this->originalPixels_; }
		Vec2 &pos() { return this->pos_; }
		Vec2 &prevPos() { return this->prevPos_; }

};

std::vector<Pixel> getOriginPixelsAtStructure(Structure &structure) {//Get pixels from the location of own pixels
    std::vector<Pixel> originPixels;

    for (Pixel& sp : structure.ownPixels()) {
        Pixel* p = getPixelAt(structure.pos().xi() + sp.pos().xi(), structure.pos().yi() + sp.pos().yi());
        if (!p) { continue; }

        originPixels.push_back(*p);
    }

    return originPixels;
}

void updateStructure(Structure &structure) {//Used to set and update the structure
	//W.I.P
}

std::vector<Structure> structures;

}
