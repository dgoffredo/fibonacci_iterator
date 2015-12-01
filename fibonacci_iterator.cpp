// fibonacci_iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/multiprecision/cpp_int.hpp>

namespace Test1 {

	template <typename Integer>
	class fibonacci_iterator :
		public std::iterator<std::bidirectional_iterator_tag, Integer>
	{
		Integer state[3]{ 0, 0, 1 };
	public:
		fibonacci_iterator() {}

		explicit fibonacci_iterator(unsigned n) {
			std::advance(*this, n);
		}

		fibonacci_iterator & operator= (const fibonacci_iterator & other) {
			std::copy(std::begin(other.state), std::end(other.state),
				std::begin(state));
		}

		fibonacci_iterator & operator++ () {
			state[0] = state[1] + state[2];
			std::rotate(state, state + 1, state + 3);
			return *this;
		}

		fibonacci_iterator operator++ (int) {
			fibonacci_iterator result(*this);
			++(*this);
			return result;
		}

		fibonacci_iterator & operator-- () {
			state[1] = state[2] - state[0];
			std::rotate(state, state + 2, state + 3);
			return *this;
		}

		fibonacci_iterator operator-- (int) {
			fibonacci_iterator result(*this);
			--(*this);
			return result;
		}

		const Integer & operator* () const {
			return state[2];
		}
	};

	template <typename Integer>
	bool operator== (const fibonacci_iterator<Integer> & left,
		const fibonacci_iterator<Integer> & right)
	{
		return *left == *right;
	}

	template <typename Integer>
	bool operator!= (const fibonacci_iterator<Integer> & left,
		const fibonacci_iterator<Integer> & right)
	{
		return !(left == right);
	}
} // namespace Test1

namespace Test2 {
	template <typename Integer>
	class fibonacci_iterator :
		public std::iterator<std::forward_iterator_tag, Integer>
	{
		Integer state[2]{ 0, 1 };
		bool whichOne = false;
	public:
		fibonacci_iterator() {}

		explicit fibonacci_iterator(unsigned n) {
			std::advance(*this, n);
		}

		fibonacci_iterator & operator= (const fibonacci_iterator & other) {
			state[0] = other.state[0];
			state[1] = other.state[1];
			whichOne = other.whichOne
		}

		fibonacci_iterator & operator++ () {
			whichOne = !whichOne;
			state[whichOne] = state[0] + state[1];
			return *this;
		}

		fibonacci_iterator operator++ (int) {
			fibonacci_iterator result(*this);
			++(*this);
			return result;
		}

		const Integer & operator* () const {
			return state[whichOne];
		}
	};

	template <typename Integer>
	bool operator== (const fibonacci_iterator<Integer> & left,
		const fibonacci_iterator<Integer> & right)
	{
		return *left == *right;
	}

	template <typename Integer>
	bool operator!= (const fibonacci_iterator<Integer> & left,
		const fibonacci_iterator<Integer> & right)
	{
		return !(left == right);
	}
} // namespace test2

template <typename Iterator>
long long int doTest(unsigned n) {
	const std::clock_t begin = std::clock();
	const auto i = *Iterator(n) % 10;
	(void)i;
	const std::clock_t end = std::clock();
	return end - begin;
}

int main(int argc, char *argv[])
{
	assert(argc == 2);
	typedef boost::multiprecision::cpp_int Integer;
	const int n = std::atoi(argv[1]);
	assert(n >= 0);

	std::cout << "Test1 took " << doTest<Test1::fibonacci_iterator<Integer>>(n) << " ticks.\n";
	std::cout << "Test1 took " << doTest<Test2::fibonacci_iterator<Integer>>(n) << " ticks.\n";
}

