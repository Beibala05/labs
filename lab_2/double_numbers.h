#ifndef DOUBLE_NUMBERS_H
#define DOUBLE_NUMBERS_H

#include <vector>
#include <cstddef>
#include <ostream>

struct DoubleNumbers
{
	DoubleNumbers();
	DoubleNumbers(const DoubleNumbers& other);
	DoubleNumbers(DoubleNumbers&& other) 								noexcept;
	DoubleNumbers(std::vector<double> other_numbers);
	DoubleNumbers(std::initializer_list<double> list);


	DoubleNumbers& 			operator =  (const DoubleNumbers& other);
	DoubleNumbers& 			operator =  (DoubleNumbers&& other);
	DoubleNumbers& 			operator += (const DoubleNumbers& other);
	DoubleNumbers& 			operator -= (const DoubleNumbers& other);
	DoubleNumbers& 			operator *= (const DoubleNumbers& other);
	DoubleNumbers 			operator +  (const DoubleNumbers& other)	const;
	DoubleNumbers 			operator -  (const DoubleNumbers& other)	const;
	DoubleNumbers 			operator *  (const DoubleNumbers& other)	const;
	DoubleNumbers& 			operator += (double scalar);
	DoubleNumbers& 			operator -= (double scalar);
	DoubleNumbers& 			operator *= (double scalar);
	DoubleNumbers 			operator +  (double scalar)					const;
	DoubleNumbers 			operator -  (double scalar)					const;
	DoubleNumbers 			operator *  (double scalar)					const;
	bool 					operator == (const DoubleNumbers& other)	const;
	bool 					operator != (const DoubleNumbers& other)	const;
	double 					operator () (double x)						const;

	DoubleNumbers 			derivative() 								const;
	DoubleNumbers 			integral() 									const;

	size_t				 	size()										const;
	std::vector<double> 	get_numbers() 								const;
		

private:
	std::vector<double> 	numbers;
};

std::ostream& operator << (std::ostream& os, const DoubleNumbers& numbers);

#endif // DOUBLE_NUMBERS_H