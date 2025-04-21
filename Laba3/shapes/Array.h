#pragma once
#include "Shapes.h"
#include <initializer_list>

class Array {
public:
	Array() = default;
	Array(size_t capacity) : m_capacity(capacity) {}
	Array(const std::initializer_list<Shape*>& shapes);
	Array(const Array&);
	Array& operator=(const Array&);
	Array(Array&&) noexcept;
	Array& operator=(Array&&) noexcept;
	~Array();
	void push_back(const Shape* shape);
	void pop_back();
	void erase(size_t index);
	const Shape* operator[](int index) const;
	Shape* operator[](int index);
	bool empty() const;
	size_t size() const;
	size_t capacity() const;
	void reserve(size_t new_capacity);
	Shape** data() const;
	Shape** begin() const;
	Shape** end() const;
private:
	size_t m_size = 0;
	size_t m_capacity = 0;
	Shape** m_shapes = nullptr;
};