#pragma once

namespace pa {

class Structure {
	private:
		std::vector<Pixel> ownPixels_;//Pixels from structure itself
		std::vector<Pixel> originalPixels_;//Pixels from before the placement of the structure
		Vec2 pos_;//Start pos of the structure
		Vec2 prevPos_;//The pos of the structure, when pos_ is changed, this one is one behind
		bool drawnBefore_;

	public:
		Structure() : pos_(0, 0), prevPos_(0, 0), drawnBefore_(false) {}
		Structure(std::vector<Pixel> pixels, Vec2 pos) : ownPixels_(pixels), pos_(pos), prevPos_(pos), drawnBefore_(false) {}

		std::vector<Pixel> &ownPixels() { return this->ownPixels_; }
		std::vector<Pixel> &originalPixels() { return this->originalPixels_; }
		Vec2 &pos() { return this->pos_; }
		Vec2 &prevPos() { return this->prevPos_; }
		bool &drawnBefore() { return this->drawnBefore_; }

};

void getPixelsFromStructurePos(std::vector<Pixel> &pixels, Structure &structure) {
	for (Pixel &sp : structure.ownPixels()) {
		Pixel *p = getPixelAt(sp.pos().xi() + structure.pos().xi(), sp.pos().yi() + structure.pos().yi());
		if (!p) { continue; }

		pixels.push_back(*p);
	}
}

void updateStructure(Structure &structure) {//Used to set and update the structure
	if ((structure.pos().xi() != structure.prevPos().xi()) || (structure.pos().yi() != structure.prevPos().yi())) {
		//Update structure pixels based on pos. Old offset seen pixels get's restored, and then origin pixels is-
		// updated with the pixels that get asphalted soon after by the updated ownPixels's pos
	}
	else if (!structure.drawnBefore()) {
		//Set the originalPixels before drawing the own pixels, offset is the same here. Draw the structure for-
		// the first time here

		//Fill originalPixels
		structure.originalPixels().clear();
		getPixelsFromStructurePos(structure.originalPixels(), structure);
		//

		//Set structure
		for (Pixel &sp : structure.ownPixels()) {
			setPixel({sp.pos().xi() + structure.pos().xi(), sp.pos().yi() + structure.pos().yi()}, sp.color(), sp.c(), sp.opacity());
		}
		//

		structure.drawnBefore() = true;
	}
}

std::vector<Structure> structures;

}
