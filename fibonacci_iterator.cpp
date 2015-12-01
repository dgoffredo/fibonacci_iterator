// fibonacci_iterator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <boost/multiprecision/cpp_int.hpp>

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

int main()
{
	typedef boost::multiprecision::cpp_int Integer;

    Integer i = *fibonacci_iterator<Integer>(200) % 10;
	return static_cast<int>(i);
}

