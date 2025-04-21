#include "Shapes.h"
#include "Array.h"
#include <algorithm>

Array::Array(const std::initializer_list<Shape*>& shapes)
{
	m_capacity = shapes.size();
	m_size = shapes.size();
	m_shapes = new Shape*[m_capacity];

	std::copy_n(shapes.begin(), m_size, begin());
}

Array::Array(const Array& other)
{
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	delete[] m_shapes;

	m_shapes = new Shape*[m_capacity];
	std::copy(other.begin(), other.end(), begin());
}

Array& Array::operator=(const Array& other)
{
	if (this != &other) {
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		delete[] m_shapes;

		m_shapes = new Shape * [m_capacity];
		std::copy(other.begin(), other.end(), begin());
	}

	return *this;
}

Array::Array(Array&& other) noexcept
{
	m_size = other.m_size;
	m_capacity = other.m_capacity;
	delete[] m_shapes;

	m_shapes = other.m_shapes;
	other.m_shapes = nullptr;
}

Array& Array::operator=(Array&& other) noexcept
{
	if (this != &other) {
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		delete[] m_shapes;

		m_shapes = other.m_shapes;
		other.m_shapes = nullptr;
	}
	return *this;
}

Array::~Array()
{
	delete[] m_shapes;
}

void Array::push_back(const Shape* shape)
{
	if (m_size < m_capacity) {
		memcpy(m_shapes[m_size++], shape, sizeof(Shape));
	}
	else {
		m_capacity *= 2;
		auto new_buf = new Shape*[m_capacity];
		std::copy(begin(), end(), new_buf);
		delete[] m_shapes;
		m_shapes = new_buf;

		memcpy(m_shapes[m_size++], shape, sizeof(Shape));
	}
}

void Array::pop_back()
{
	m_shapes[m_size--]->~Shape();
}

void Array::erase(size_t index)
{
	if (index >= 0 && index <= m_size) {
		std::swap(m_shapes[m_size], m_shapes[index]);
		pop_back();
	}
}

const Shape* Array::operator[](int index) const
{
	if (index >= 0 && index <= m_size) {
		return this->m_shapes[index];
	}
	return nullptr;
}

Shape* Array::operator[](int index)
{
	if (index >= 0 && index <= m_size) {
		return this->m_shapes[index];
	}
	return nullptr;
}

bool Array::empty() const
{
	return m_size == 0;
}

size_t Array::size() const
{
	return m_size;
}

size_t Array::capacity() const
{
	return m_capacity;
}

void Array::reserve(size_t new_capacity)
{
	m_capacity = new_capacity;
	if (!m_shapes) {
		m_shapes = new Shape*[m_capacity];
	} 
	else {
		auto new_buf = new Shape*[m_capacity];
		std::copy(begin(), end(), new_buf);
		delete[] m_shapes;
		m_shapes = new_buf;
	}
}

Shape** Array::data() const
{
	return m_shapes;
}

Shape** Array::begin() const
{
	return m_shapes;
}

Shape** Array::end() const
{
	return m_shapes + m_size;
}