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

std::vector<Structure> structures;

void getPixelsFromStructurePos(std::vector<Pixel> &pixels, Structure &structure) {
	for (Pixel &sp : structure.ownPixels()) {
		Pixel *p = getPixelAt(sp.pos().xi() + structure.pos().xi(), sp.pos().yi() + structure.pos().yi());
		if (!p) { continue; }

		pixels.push_back(*p);
	}
}

void setStructureInPixelVec(Structure &structure) {
	for (Pixel &p : structure.ownPixels()) {
		setPixel({p.pos().xi() + structure.pos().xi(), p.pos().yi() + structure.pos().yi()}, p.color(), p.c(), p.opacity());
	}
}

void updateStructures() {//Used to set and update the structures
	for (Structure &structure : structures) {
		if ((structure.pos().xi() != structure.prevPos().xi()) || (structure.pos().yi() != structure.prevPos().yi())) {
			//Update structure pixels based on pos. Old offset seen pixels get's restored, and then origin pixels is-
			// updated with the pixels that get asphalted soon after by the updated ownPixels's pos

			//Set the underlying pixels back to their previous pixels
			for (Pixel &op : structure.originalPixels()) {
				setPixel(op.pos(), op.color(), op.c(), op.opacity());
			}
			//

			//Set the original pixels based on the new location of the structure
			structure.originalPixels().clear();
			getPixelsFromStructurePos(structure.originalPixels(), structure);
			//

			structure.prevPos() = structure.pos();//They are the same now again

			//Set the structure on the new location
			setStructureInPixelVec(structure);
			//

		}
		else if (!structure.drawnBefore()) {
			//Set the originalPixels before drawing the own pixels, offset is the same here. Draw the structure for-
			// the first time here

			//Fill originalPixels
			structure.originalPixels().clear();
			getPixelsFromStructurePos(structure.originalPixels(), structure);
			//

			//Set structure
			setStructureInPixelVec(structure);
			//

			structure.drawnBefore() = true;
		}
	}
}

}
