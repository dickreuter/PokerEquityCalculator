#pragma once

#include <boost/python.hpp>
#include <set>
#include <string>
#include <vector>
#include "Deck.h"


using CardsWithTableCombined = std::set<std::string>;
using Score = std::vector<std::tuple<int, int>>;

bool eval_best_hand(const std::vector<CardsWithTableCombined>&);
std::tuple< std::vector<int>, std::vector<int>, std::string> calc_score(const CardsWithTableCombined&);

__declspec(dllexport) double montecarlo(const std::set<std::string>&, const std::set<std::string>&, const int, const int);


template<typename T>
std::vector<T> slice(std::vector<T> const& v, int m, int n)
{
	if (m > v.size())
		m = v.size();
	if (n > v.size())
		n = v.size();
	auto first = v.cbegin() + m;
	auto last = v.cbegin() + n;  // ending index needs to be n=x+1

	std::vector<T> vec(first, last);
	return vec;
}