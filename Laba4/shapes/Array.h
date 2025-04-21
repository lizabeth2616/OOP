#pragma once
#include "Shapes.h"
#include <initializer_list>

template<class T>
class Array {
public:
	Array() = default;
	Array(size_t size)
	{
		m_capacity = size;
		m_size = size;
		m_data = std::make_shared<T[]>(m_capacity);
	}
	Array(const std::initializer_list<T>& list)
	{
		m_capacity = list.size();
		m_size = list.size();
		m_data = std::make_shared<T[]>(m_capacity);

		std::copy_n(list.begin(), m_size, begin());
	}
	void push_back(const T& shape)
	{
		if (m_size >= m_capacity) {
			m_capacity *= 2;
			auto new_buf = std::make_shared<T[]>(m_capacity);
			for (size_t i = 0; i < m_size; i++) {
				new_buf[i] = m_data[i];
			}
			m_data = std::move(new_buf);
		}
		m_data[m_size++] = shape;
	}
	void pop_back()
	{
		m_size--;
	}
	void erase(size_t index)
	{
		if (index >= 0 && index <= m_size) {
			std::swap(m_data[m_size], m_data[index]);
			pop_back();
		}
	}
	const T& operator[](int index) const
	{
		if (index <= 0 || index >= m_size) {
			throw std::out_of_range("Index out of range.");
		}
		return this->m_data[index];
	}
	T& operator[](int index)
	{
		if (index <= 0 || index >= m_size) {
			throw std::out_of_range("Index out of range.");
		}
		return this->m_data[index];
	}
	bool empty() const
	{
		return m_size == 0;
	}
	size_t size() const
	{
		return m_size;
	}
	size_t capacity() const
	{
		return m_capacity;
	}
	void reserve(size_t new_capacity)
	{
		m_capacity = new_capacity;
		if (!m_data) {
			m_data = std::make_shared<T[]>(m_capacity);
		}
		else {
			auto new_buf = std::make_shared<T[]>(m_capacity);
			for (size_t i = 0; i < m_size; i++) {
				new_buf[i] = m_data[i];
			}
			m_data = std::move(new_buf);
		}
	}
	T* data() const
	{
		return m_data.get();
	}
	T* begin() const
	{
		return data();
	}
	T* end() const
	{
		return m_data.get() + m_size;
	}
private:
	size_t m_size = 0;
	size_t m_capacity = 0;
	std::shared_ptr<T[]> m_data = nullptr;
};