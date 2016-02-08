#pragma once


#include <boost/variant/variant.hpp>
#include <boost/variant/recursive_variant.hpp>

struct Add;
struct Mul;
struct Binary;

typedef boost::variant<
	double,
	boost::recursive_wrapper<Add>,
	boost::recursive_wrapper<Mul>,
	boost::recursive_wrapper<Binary>
> Expression;


struct Add {
	Expression _x;
	Expression _y;
	Add(const Expression& x, const Expression& y) : _x(x), _y(y) {}
};
struct Mul {
	Expression _x;
	Expression _y;
	Mul(const Expression& x, const Expression& y) : _x(x), _y(y) {}
};




