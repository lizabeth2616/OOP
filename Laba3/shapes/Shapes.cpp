#include "Shapes.h"
#include <iostream>
#include <algorithm>


std::ostream& operator<<(std::ostream& os, const Polygon& shape)
{
	os << shape.GetName() << ": " << " { ";
	for (auto& v : shape.vertices) {
		os << v;
	}
	os << "}";

	return os;
}

bool Polygon::operator==(const Polygon& rhs) const {
	if (GetVertices().size() != rhs.GetVertices().size())
	{
		return false;
	}

	auto size = GetVertices().size();
	for (int i = 0, j = 0; j < size; ++j)
	{
		if (i == size)
		{
			return true;
		}
		else if (vertices[i] == rhs.vertices[j])
		{
			++i;
			j = -1;
		}
	}
	return false;
}

Vertex Triangle::GetCenter() const {
	auto tri = GetVertices();

	float centerX = (tri[0].x + tri[1].x + tri[2].x) / 3.0f;
	float centerY = (tri[0].y + tri[1].y + tri[2].y) / 3.0f;

	return Vertex{ centerX, centerY };
}

bool Triangle::operator==(const Triangle& rhs) const
{
	for (int i = 0, j = 0; j < 3; ++j)
	{
		if (i == 3)
		{
			return true;
		}
		else if (vertices[i] == rhs.vertices[j])
		{
			++i;
			j = -1;
		}
	}
	return false;
}

double Triangle::GetArea() const
{
	auto verts = GetVertices();

	double area = 0.5 * abs((verts[0].x - verts[2].x) * (verts[1].y - verts[0].y)
		- (verts[0].x - verts[1].x) * (verts[2].y - verts[0].y));

	return area;
}

Triangle::operator double() const {
	return GetArea();
}

std::istream& operator>>(std::istream& is, Triangle& tri) {
	std::vector<Vertex> verts;

	is >> verts[0];
	is >> verts[1];
	is >> verts[2];

	tri.SetVertices(verts);

	return is;
}

Vertex Square::GetCenter() const {
	return Vertex{ pos.x + width * 0.5f, pos.y + width * 0.5f };
}

Square::operator double() const {
	return GetArea();
}

std::istream& operator>>(std::istream& is, Square& sqr) {
	is >> sqr.pos;
	is >> sqr.width;

	return is;
}

std::vector<Vertex> Square::FromWidth(const Vertex& v, float width) {
	std::vector<Vertex> verts;

	verts.push_back(v);
	verts.push_back({v.x + width, v.y});
	verts.push_back({v.x, v.y + width});
	verts.push_back({v.x + width, v.y + width});

	return verts;
}


Vertex Rectangle::GetCenter() const {
	return Vertex{ pos.x + width * 0.5f, pos.y + height * 0.5f};
}

Rectangle::operator double() const {
	return GetArea();
}

std::istream& operator>>(std::istream& is, Rectangle& shape) {
	is >> shape.pos;
	is >> shape.width;
	is >> shape.height;

	return is;
}

std::vector<Vertex> Rectangle::FromWidthAndHeight(const Vertex& v, float width, float height) {
	std::vector<Vertex> verts;

	verts.push_back(v);
	verts.push_back({ v.x + width, v.y });
	verts.push_back({ v.x, v.y + height });
	verts.push_back({ v.x + width, v.y + height });

	return verts;
}

bool Square::operator==(const Square& rhs) const
{
	return width == rhs.width && pos == rhs.pos;
}

double Square::GetArea() const
{
	return width * width;
}

double Rectangle::GetArea() const
{
	return width * height;
}


bool Rectangle::operator==(const Rectangle& rhs) const {

	return width == rhs.width && height == rhs.height && pos == rhs.pos;
}