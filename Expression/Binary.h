#pragma once


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include "Expression.h"
#include "utility/enum.h"

enum class BinaryOperator {
	max, min, LAST,
};
GENERATE_ENUM_ITERATOR(BinaryOperator);


inline std::string toString(const BinaryOperator& op)
{
	switch (op) {
	case BinaryOperator::max: return "max";
	case BinaryOperator::min: return "min";
	}
	return "";
}

inline std::function<double(double, double)> toFunction(const BinaryOperator& op)
{
	switch (op) {
	case BinaryOperator::max: return [](const double&x, const double& y) {return std::max<double>(x, y); };
	case BinaryOperator::min: return [](const double&x, const double& y) {return std::min<double>(x, y); };
	}
	return [](const double&x, const double& y) {return 0.0;};
};

struct Binary {
	BinaryOperator _op;
	Expression _lhs;
	Expression _rhs;

	Binary(const BinaryOperator& op, const Expression& lhs, const Expression& rhs)
		: _op(op), _lhs(lhs), _rhs(rhs) {}
};

