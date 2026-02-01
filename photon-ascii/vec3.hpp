#pragma once

namespace pa {

class Vec3 : public Vec2 {
	private:
		int zi_;
		float zf_;

	public:
		Vec3() : Vec2() {
			this->zi_ = 0;
			this->zf_ = 0.0f;
		}

		Vec3(int xi, int yi, int zi) : Vec2(xi, yi), zi_(zi) {
			this->zf_ = 0.0f;
		}

		Vec3(float xf, float yf, float zf) : Vec2(xf, yf), zf_(zf) {
			this->zi_ = 0;
		}

		int &zi() { return this->zi_; }
		float &zf() { return this->zf_; }

		void clear() override {
			Vec2::clear();

			this->zi_ = 0;
			this->zf_ = 0.0f;
		}

};

}
