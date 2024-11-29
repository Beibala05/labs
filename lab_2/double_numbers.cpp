#include "double_numbers.h"

#include <cmath>

DoubleNumbers::DoubleNumbers()
{
	numbers.push_back(0.0);
}

DoubleNumbers::DoubleNumbers(std::vector<double> other_numbers)
{
	numbers = other_numbers;
}

DoubleNumbers::DoubleNumbers(const DoubleNumbers& other)
{
	numbers = other.get_numbers();
}

DoubleNumbers::DoubleNumbers(DoubleNumbers&& other) noexcept
{
	numbers = std::move(other.get_numbers());
}

DoubleNumbers::DoubleNumbers(std::initializer_list<double> list)
{
	for (double i : list)
	{
		numbers.push_back(i);
	}
}

DoubleNumbers& DoubleNumbers::operator=(const DoubleNumbers& other)
{
	numbers = other.get_numbers();

	return *this;
}

DoubleNumbers& DoubleNumbers::operator=(DoubleNumbers&& other)
{
	numbers = std::move(other.get_numbers());

	return *this;
}

DoubleNumbers DoubleNumbers::operator+(const DoubleNumbers& other) const
{
	std::vector<double> result(std::max(this->size(), other.size()));

	for (int i = 0; i < result.size(); ++i)
	{
		if (i < this->size())
		{
			result[i] += this->get_numbers()[i];
		}

		if (i < other.size())
		{
			result[i] += other.get_numbers()[i];
		}
	}

	return DoubleNumbers(result);
}

DoubleNumbers DoubleNumbers::operator-(const DoubleNumbers& other) const
{
	std::vector<double> result(std::max(this->size(), other.size()));

	for (int i = 0; i < result.size(); ++i)
	{
		if (i < this->size())
		{
			result[i] += this->get_numbers()[i];
		}

		if (i < other.size())
		{
			result[i] -= other.get_numbers()[i];
		}
	}

	return DoubleNumbers(result);
}

DoubleNumbers DoubleNumbers::operator*(const DoubleNumbers& other) const
{
	std::vector<double> result(this->size() + other.size() - 1);

    for (size_t i = 0; i < this->size(); ++i) 
    {
        for (size_t j = 0; j < other.size(); ++j) 
        {
            result[i + j] += this->get_numbers()[i] * other.get_numbers()[j];
        }
    }

	return DoubleNumbers(result);
}

DoubleNumbers& DoubleNumbers::operator+=(const DoubleNumbers& other)
{
	*this = *this + other;
	return *this;
}

DoubleNumbers& DoubleNumbers::operator-=(const DoubleNumbers& other)
{
	*this = *this - other;
	return *this;
}

DoubleNumbers& DoubleNumbers::operator*=(const DoubleNumbers& other)
{
	*this = *this * other;
	return *this;
}

DoubleNumbers DoubleNumbers::operator+(double scalar) const
{
	std::vector<double> result;

	for (auto& element : numbers)
	{
		result.push_back(element);
	}

	result.at(result.size() - 1) += scalar;

	return DoubleNumbers(result);
}

DoubleNumbers DoubleNumbers::operator-(double scalar) const
{
	std::vector<double> result;

	for (auto& element : numbers)
	{
		result.push_back(element);
	}

	result.at(result.size() - 1) -= scalar;

	return DoubleNumbers(result);
}

DoubleNumbers DoubleNumbers::operator*(double scalar) const
{
	std::vector<double> result;

	for (auto& element : numbers)
	{
		result.push_back(element * scalar);
	}

	return DoubleNumbers(result);
}

DoubleNumbers& DoubleNumbers::operator+=(double scalar)
{
	*this = *this + scalar;
	return *this;
}

DoubleNumbers& DoubleNumbers::operator-=(double scalar)
{
	*this = *this - scalar;
	return *this;
}

DoubleNumbers& DoubleNumbers::operator*=(double scalar)
{
	*this = *this * scalar;
	return *this;
}

bool DoubleNumbers::operator==(const DoubleNumbers& other) const
{
	return this->get_numbers() == other.get_numbers();
}

bool DoubleNumbers::operator!=(const DoubleNumbers& other) const
{
	return this->get_numbers() != other.get_numbers();
}

double DoubleNumbers::operator()(double x) const
{
	double result = 0.0;

	for (int i = 0; i < numbers.size(); ++i)
	{
		result += (pow(x, numbers.size() - i - 1) * numbers[i]);
	}

	return result;
}

std::vector<double> DoubleNumbers::get_numbers() const
{
	return numbers;
}

size_t DoubleNumbers::size() const
{
	return numbers.size();
}


DoubleNumbers DoubleNumbers::derivative() const 
{
	if (numbers.size() == 0 || numbers.size() == 1) return DoubleNumbers();

    std::vector<double> result;

	for (int i = 0; i < numbers.size() - 1; ++i)
	{
		result.push_back(numbers[i] * (numbers.size() - i - 1));
	}

	return DoubleNumbers(result);
}

DoubleNumbers DoubleNumbers::integral() const
{
	if (numbers.size() == 0 || numbers.size() == 1) return DoubleNumbers();

	std::vector<double> result;

	int j = numbers.size();

	for (int i = 0; i < numbers.size(); ++i)
	{
		result.push_back(numbers[i] / j);
		j--;
	}

	result.push_back(0);
	
	return DoubleNumbers(result);
}

std::ostream& operator<<(std::ostream& os, const DoubleNumbers& numbers)
{
    for (int i = 0; i < numbers.size(); ++i)
    {
        os 
        << (numbers.get_numbers()[i] >= 0 ? " + " : " - ") 
        << std::abs(numbers.get_numbers()[i])
        << "x^" 
        << numbers.size() - i - 1;
    }

    return os;
}