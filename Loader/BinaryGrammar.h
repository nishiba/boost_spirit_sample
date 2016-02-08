#pragma once


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include "Expression/Binary.h"

namespace qi = boost::spirit::qi;


template <typename Itr, typename Skip, typename Inner>
class BinaryGrammar : public qi::grammar<Itr, Expression(), Skip> {
public:
	BinaryGrammar(Inner& inner) : BinaryGrammar::base_type(_expr), _inner(inner)
	{
		using namespace boost::spirit;
		using namespace boost::phoenix;
		for (BinaryOperator o : BinaryOperator()) {
			_op.add(toString(o), o);
		}
		_expr = (qi::no_case[_op] >> '(' >> _inner >> ',' >> _inner >> ')')[_val = makeBinary()];
	}

private:
	Inner& _inner;
	qi::symbols<char, BinaryOperator> _op;
	qi::rule<Itr, Expression(), Skip> _expr;

private:
	static auto makeBinary()
	{
		using namespace boost::spirit;
		return boost::phoenix::bind(
			[](auto& op, auto& x, auto& y) {return Binary(op, x, y); },
			_1, _2, _3);
	}
};

