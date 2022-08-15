#pragma once

#include <iostream>

struct Point3D {
	int x, y, z;
};

std::istream& operator>>(std::istream& stream, Point3D& point) {
	stream >> point.x >> point.y >> point.z;
	return stream;
}

struct Triangle3D {
	Point3D x, y, z;
	bool intersects(const Triangle3D& rhs) const {
		return false;
	}
};

std::istream& operator>>(std::istream& stream, Triangle3D& triangle) {
	stream >> triangle.x >> triangle.y >> triangle.z;
	return stream;
}
