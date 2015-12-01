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

void usage(const char *invocation) {
	std::cerr << "usage: " << invocation << " <n begin> [<n end>]\n"
		"with <n end> greater than <n begin>.\n";
}

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3) {
		assert(argc == 1);
		usage(argv[0]);
		return 1;
	}

	const int n1 = std::atoi(argv[1]);
	if (n1 < 0) {
		usage(argv[0]);
		return 2;
	}

	const int n2 = argc > 2 ? std::atoi(argv[2]) : n1 + 1;
	if (n2 <= n1) {
		usage(argv[0]);
		return 3;
	}

	typedef boost::multiprecision::cpp_int Integer;
	std::copy_n(fibonacci_iterator<Integer>(n1), 
		        n2 - n1, 
		        std::ostream_iterator<Integer>(std::cout, "\n"));
}

