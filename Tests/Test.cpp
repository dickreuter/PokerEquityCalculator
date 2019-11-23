#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE HandEvaluationTests

#include <boost/test/included/unit_test.hpp>
#include "../EquityCalculatorMontecarlo/Deck.h"
#include "../EquityCalculatorMontecarlo/Scoring.h"

BOOST_AUTO_TEST_CASE(card_evaluation1)
{
	std::set<std::string> cards1 = { "3H", "3S", "4H", "4S", "8S", "8C", "QH" };
	std::set<std::string> cards2 = { "KH", "6C", "4H", "4S", "8S", "8C", "QH" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = false;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation2)
{
	std::set<std::string> cards1 = { "8H", "8D", "QH", "7H", "9H", "JH", "TH" };
	std::set<std::string> cards2 = { "KH", "6C", "QH", "7H", "9H", "JH", "TH" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = false;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation3)
{
	std::set<std::string> cards1 = { "AS", "KS", "TS", "9S", "7S", "2H", "2H" };
	std::set<std::string> cards2 = { "AS", "KS", "TS", "9S", "8S", "2H", "2H" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = false;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation4)
{
	std::set<std::string> cards1 = { "8S", "TS", "8H", "KS", "9S", "TH", "KH" };
	std::set<std::string> cards2 = { "TD", "7S", "8H", "KS", "9S", "TH", "KH" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = true;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation5)
{
	std::set<std::string> cards1 = { "2D", "2H", "AS", "AD", "AH", "8S", "7H" };
	std::set<std::string> cards2 = { "7C", "7S", "7H", "AD", "AS", "8S", "8H" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = true;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation6)
{
	std::set<std::string> cards1 = { "7C", "7S", "7H", "AD", "KS", "5S", "8H" };
	std::set<std::string> cards2 = { "2D", "3H", "AS", "4D", "5H", "8S", "7H" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = false;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation6b)
{
	std::set<std::string> cards1 = { "7C", "7C", "AC", "AC", "8C", "8S", "7H" };
	std::set<std::string> cards2 = { "2C", "3C", "4C", "5C", "6C", "8S", "KH" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = false;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation7)
{
	std::set<std::string> cards1 = { "AC", "JS", "AS", "2D", "5H", "3S", "3H" };
	std::set<std::string> cards2 = { "QD", "JD", "TS", "9D", "6H", "8S", "KH" };
	std::set<std::string> cards3 = { "2D", "3D", "4S", "5D", "6H", "8S", "KH" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2,cards3 };

	bool expected = false;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation8)
{
	std::set<std::string> cards1 = { "7C", "5S", "3S", "JD", "8H", "2S", "KH" };
	std::set<std::string> cards2 = { "AD", "3D", "4S", "5D", "9H", "8S", "KH" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = false;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}

BOOST_AUTO_TEST_CASE(card_evaluation9)
{
	std::set<std::string> cards1 = { "2C", "2D", "4S", "4D", "4H", "8S", "KH" };
	std::set<std::string> cards2 = { "7C", "7S", "7D", "7H", "8H", "8S", "JH" };

	const std::vector<CardsWithTableCombined> all_cards{ cards1,cards2 };

	bool expected = false;
	bool won = eval_best_hand(all_cards);
	BOOST_TEST(won == expected);
}