#pragma once

#include <vector>
#include <string>
#include <assert.h>
#include <iostream>

struct Vertex {
	Vertex() = default;
	Vertex(float x_in, float y_in) 
		: 
		x(x_in), y(y_in) {}
	Vertex operator+(const Vertex& v_in) const {
		return Vertex(x + v_in.x, y + v_in.y);
	}
	Vertex operator-(const Vertex& v_in) const {
		return Vertex(x - v_in.x, y - v_in.y);
	}
	Vertex& operator+=(const Vertex& rhs) {
		x += rhs.x;
		y += rhs.y;

		return *this;
	}
	Vertex& operator-=(const Vertex& rhs) {
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}
	bool operator==(const Vertex& rhs) const {
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Vertex& rhs) const {
		return !(*this == rhs);
	}
	friend std::ostream& operator<<(std::ostream& os, const Vertex& vertex) {
		os << "(" << vertex.x << " ," << vertex.y << ")";
		return os;
	}
	friend std::istream& operator>>(std::istream& is, Vertex& vertex) {
		is >> vertex.x >> vertex.y;
		return is;
	}
public:
	float x = 0.0f;
	float y = 0.0f;
};

class Shape {
public:
	virtual Vertex GetCenter() const = 0;
	virtual double GetArea() const = 0;
	virtual explicit operator double() const = 0;
};

class Polygon : public Shape {
protected:
	Polygon(const std::string& name_in, const std::vector<Vertex>& vertices_in)
		:
		shapeName(name_in),
		vertices(vertices_in)
	{}
public:
	friend std::ostream& operator<<(std::ostream& os, const Polygon& shape);
	virtual inline std::string GetName() const { return shapeName; }
	virtual inline std::vector<Vertex> GetVertices() const { return vertices; }
	inline void SetVertices(const std::vector<Vertex>& verts) { vertices = verts; }
	virtual ~Polygon() = default;
	bool operator==(const Polygon& rhs) const;
protected:
	std::string shapeName;
	std::vector<Vertex> vertices;
};

class Triangle : public Polygon {
public:
	Triangle(const std::vector<Vertex>& vertices_in)
		:
		Polygon("Triangle", vertices_in)
	{
		assert(vertices_in.size() == 3);
	}
	virtual Vertex GetCenter() const override;
	virtual double GetArea() const override;
	virtual explicit operator double() const override;
	bool operator==(const Triangle& rhs) const;
	friend std::istream& operator>>(std::istream& is, Triangle& shape);
};

class Square : public Polygon {
public:
	Square(const Vertex& pos, float width)
		:
		pos(pos),
		width(width),
		Polygon("Square", FromWidth(pos, width))
	{}
	virtual Vertex GetCenter() const override;
	virtual explicit operator double() const override;
	virtual double GetArea() const override;
	friend std::istream& operator>>(std::istream& is, Square& shape);
	bool operator==(const Square& rhs) const;
private:
	static std::vector<Vertex> FromWidth(const Vertex& v, float width);
private:
	Vertex pos;
	float width;
};

class Rectangle : public Polygon {
public:
	Rectangle( const Vertex& pos, float width, float height )
		:
		pos(pos),
		width(width),
		height(height),
		Polygon("Rectangle", FromWidthAndHeight(pos, width, height))
	{}
	virtual Vertex GetCenter() const override;
	virtual explicit operator double() const override;
	virtual double GetArea() const override;
	friend std::istream& operator>>(std::istream& is, Rectangle& shape);
	bool operator==(const Rectangle& rhs) const;
private:
	static std::vector<Vertex> FromWidthAndHeight(const Vertex& v, float width, float height);
private:
	Vertex pos;
	float width;
	float height;
};