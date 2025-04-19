#include "Eleven.h"
#include <algorithm>
#include <math.h>

Eleven::Eleven(const Eleven& other) noexcept {
	*this = other;
}

Eleven& Eleven::operator=(const Eleven& other) noexcept {
	if (this != &other) {
		delete[] ptr;
		len = other.len;

		ptr = new unsigned char[other.len];

		std::copy_n(other.ptr, other.len, ptr);
	}

	return *this;
}

Eleven::Eleven(Eleven&& other) noexcept {
	*this = std::move(other);
}

Eleven& Eleven::operator=(Eleven&& other) noexcept {
	if (this != &other) {
		delete[] ptr;

		len = other.len;
		ptr = other.ptr;

		other.len = 0;
		other.ptr = nullptr;
	}

	return *this;
}


Eleven Eleven::add(const Eleven& lhs, const Eleven& rhs)  {
	size_t sum = 0;

	for (long long i = lhs.len - 1; i >= 0; i--) {
		size_t thresh = 0;
		thresh += lhs.ptr[i] == 'A' ? 10 : lhs.ptr[i] - '0';

		sum += thresh * pow(11, i);
	}

	for (long long i = rhs.len - 1; i >= 0; i--) {
		size_t thresh = 0;
		thresh += rhs.ptr[i] == 'A' ? 10 : rhs.ptr[i] - '0';

		sum += thresh * pow(11, i);
	}

	size_t result_length = 0;

	size_t sum_cpy = sum;
	while (sum_cpy) {
		++result_length;
		sum_cpy /= 11;
	}

	Eleven result{ result_length, 0u };

	for (size_t i = 0; i < result_length; i++) {
		result.ptr[i] = sum % 11 == 10 ? 'A' : (sum % 11) + '0';
		sum /= 11;
	}

	return result;
}

Eleven Eleven::subtract(const Eleven& lhs, const Eleven& rhs)  {
	long long diff = 0;

	for (long long i = lhs.len - 1; i >= 0; i--) {
		size_t thresh = 0;
		thresh += lhs.ptr[i] == 'A' ? 10 : lhs.ptr[i] - '0';

		diff += thresh * pow(11, i);
	}

	for (long long i = rhs.len - 1; i >= 0; i--) {
		size_t thresh = 0;
		thresh += rhs.ptr[i] == 'A' ? 10 : rhs.ptr[i] - '0';

		diff -= thresh * pow(11, i);
	}


	if (diff < 0) {
		return Eleven();
	}

	size_t result_length = 0;

	long long diff_cpy = diff;
	while (diff_cpy) {
		++result_length;
		diff_cpy /= 11;
	}

	Eleven result{ result_length, 0u };

	for (size_t i = 0; i < result_length; i++) {
		result.ptr[i] = diff % 11 == 10 ? 'A' : (diff % 11) + '0';
		diff /= 11;
	}

	return result;
}

bool Eleven::greater_than(const Eleven& lhs, const Eleven& rhs) noexcept
{
	if (lhs.len > rhs.len) {
		return true;
	}
	else if (lhs.len == rhs.len) {
		for (long long i = lhs.len - 1; i >= 0; i--) {
			if (lhs.ptr[i] != 'A' && rhs.ptr[i] == 'A')
				return false;
			if (lhs.ptr[i] > rhs.ptr[i])
				return true;
		}
	}

	return false;
}

bool Eleven::less_than(const Eleven& lhs, const Eleven& rhs) noexcept
{
	return !greater_than(lhs, rhs) && !equal(lhs, rhs);
}

bool Eleven::equal(const Eleven& lhs, const Eleven& rhs) noexcept
{
	if (lhs.len == rhs.len) {
		for (long long i = lhs.len - 1; i >= 0; i--) {
			if (lhs.ptr[i] != rhs.ptr[i])
				return false;
		}
		return true;
	}

	return false;
}

Eleven::~Eleven() noexcept
{
	delete[] ptr;
	len = 0;
}