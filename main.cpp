// Experiments.cpp : コンソール アプリケーションのエントリ ポイントを定義します。
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <algorithm>

#include <boost/variant/static_visitor.hpp>
#include "Expression/Expression.h"
#include "Expression/Binary.h"
#include "Loader/load.h"



double calc(const Expression& e);

struct calculator : public boost::static_visitor<double> {
public:
	double operator()(const double x) const { return x; }
	double operator()(const Add& x) const { return calc(x._x) + calc(x._y); }
	double operator()(const Mul& x) const { return calc(x._x) * calc(x._y); }
	double operator()(const Binary& x) const { return toFunction(x._op)(calc(x._lhs), calc(x._rhs)); }
};

double calc(const Expression& e)
{
	return boost::apply_visitor(calculator(), e);
}

int main()
{

	std::string buffer;
	while (std::cout << "# ", std::getline(std::cin, buffer)) {
		Expression result = loadAsExpression(buffer);
		std::cout << calc(result) << std::endl;
	}
	return 0;
}
