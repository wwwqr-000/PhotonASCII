#pragma once

namespace pa {

#define farg float x, float y
#define iarg int x, int y
#define xfres this->xf_ = 0.0f;
#define yfres this->yf_ = 0.0f;

class Vec2 {
	private:
		int xi_;
		int yi_;
		float xf_;
		float yf_;

	public:
		Vec2() {
			this->xi_ = 0;
			this->yi_ = 0;
			xfres
			yfres
		}

		Vec2(iarg) : xi_(x), yi_(y) {
			xfres
			yfres
		}

		Vec2(farg) : xf_(x), yf_(y) {
			this->xi_ = 0;
			this->yi_ = 0;
		}

		int &yi() { return this->yi_; }
		float &yf() { return this->yf_; }

		int &xi() { return this->xi_; }
		float &xf() { return this->xf_; }

		virtual void clear() {
			this->xi_ = 0;
			this->yi_ = 0;
			xfres
			yfres
		}

};

}
