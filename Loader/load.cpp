#include "stdafx.h"


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include "Expression/Expression.h"
#include "Loader/load.h"
#include "Loader/ExpressionGrammar.h"


namespace qi = boost::spirit::qi;

Expression loadAsExpression(const std::string& str)
{
	ExpressionGrammar<decltype(str.begin())> g;

	Expression result;
	auto begin = str.begin();
	auto end = str.end();
	bool isSuccess = boost::spirit::qi::phrase_parse(begin, end, g, boost::spirit::qi::ascii::space, result);
	std::cout << (isSuccess && (begin == end) ? "OK" : "Fail") << std::endl;
	return result;
}
