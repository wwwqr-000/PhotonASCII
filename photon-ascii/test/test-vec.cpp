#include <iostream>

#include "../vec2.hpp"
#include "../vec3.hpp"

int main() {
	Vec2 v(10, 50);
	v.xf() = 5.7f;
	v.yf() = 2.3f;
	std::cout << "Integer: " << v.xi() << " " << v.yi() << "\n";
	std::cout << "Float: " << v.xf() << " " << v.yf() << "\n";

	Vec3 v3(10, 20, 30);
	//v3.clear();
	v3.zi() = 6;

	std::cout << v3.xi() << " " << v3.yi() << " " << v3.zi() << "\n\n";

	std::cout << "Test\n";
	return 0;
}
