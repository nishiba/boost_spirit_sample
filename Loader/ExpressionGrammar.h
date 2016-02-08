#pragma once



#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include "Loader/BinaryGrammar.h"

namespace qi = boost::spirit::qi;

template <typename Itr, typename Skip = boost::spirit::ascii::space_type>
class ExpressionGrammar : public qi::grammar<Itr, Expression(), Skip> {
public:
	ExpressionGrammar() : ExpressionGrammar::base_type(_expr), _binary(*this)
	{
		using namespace boost::spirit;
		using namespace boost::phoenix;

		_group = '(' >> _expr[_val = _1] >> ')';
		_factor = double_ | _group | _binary;
		_term = _factor[_val = _1] >> +('*' >> _factor[_val = makeMul()]);
		_terms = _term | _factor;
		_expr = _terms[_val = _1] >> *('+' >> _terms[_val = makeAdd()]);
	}
private:
	qi::rule<Itr, Expression(), Skip> _expr, _term, _factor, _group, _terms;
	BinaryGrammar<Itr, Skip, ExpressionGrammar> _binary;

private:
	static auto makeAdd()
	{
		return boost::phoenix::bind(
			[](auto& x, auto& y) {return Add(x, y); },
			boost::spirit::_val, boost::spirit::_1);
	}

	static auto makeMul()
	{
		return boost::phoenix::bind(
			[](auto& x, auto& y) {return Mul(x, y); },
			boost::spirit::_val, boost::spirit::_1);
	}
};
