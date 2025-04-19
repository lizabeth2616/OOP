#pragma once

#include <type_traits>
#include <stdexcept>

class Eleven {
public:
	Eleven() = default;
	explicit Eleven(auto num) requires(std::is_unsigned_v<decltype(num)>) {
		auto num_cpy = num;

		while (num_cpy) {
			len++;
			num_cpy /= 11;
		}

		ptr = new unsigned char[len + 1]{};

		size_t i = 0;
		while (num) {
			size_t n = num % 11;
			ptr[i] = (n == 10u) ? 'A' : n + '0';
			num /= 11;
			i++;
		}
	}
	Eleven(const Eleven&) noexcept;
	Eleven& operator=(const Eleven&) noexcept;
	Eleven(Eleven&&) noexcept;
	Eleven& operator=(Eleven&&) noexcept;
	static Eleven add(const Eleven& lhs, const Eleven& rhs);
	static Eleven subtract(const Eleven& lhs, const Eleven& rhs);
	static bool greater_than(const Eleven& lhs, const Eleven& rhs) noexcept;
	static bool less_than(const Eleven& lhs, const Eleven& rhs) noexcept;
	static bool equal(const Eleven& lhs, const Eleven& rhs) noexcept;
	~Eleven() noexcept;
private:
	Eleven(size_t size, auto num) requires(std::is_unsigned_v<decltype(num)>) {
		len = size;
		ptr = new unsigned char[len];

		size_t i = 0;
		while (num) {
			if (i == len) {
				throw std::out_of_range("Too small size");
			}

			auto n = num % 11;
			ptr[i] = (n == 10) ? 'A' : n + '0';
			num /= 11;
			i++;
		}
	}
private:
	size_t len = 0;
	unsigned char* ptr = nullptr;
};