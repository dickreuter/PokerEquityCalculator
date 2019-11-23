#include <list>
#include <tuple>
#include <vector>
#include <iostream>
#include "Deck.h"
#include "Scoring.h"

int main() {
	std::set<std::string> my_cards_ = { "KC", "TC" };
	std::set<std::string> cards_on_table = { "AD", "TD", "7S" };
	const int number_of__players = 6;
	const int number_of_iterations = 1000;
	int wins = 0;

	for (int i = 0; i < number_of_iterations; i++)
	{
		Deck deck;
		deck.remove_visible_cards(my_cards_, cards_on_table);
		deck.distribute_cards(number_of__players);
		std::vector<CardsWithTableCombined> cards_with_table_combined = deck.get_cards_combined();
		bool first_player_has_best_hand = eval_best_hand(cards_with_table_combined);
		if (first_player_has_best_hand == true)
			wins += 1;
	}
	double equity = (wins / number_of_iterations) * 100;
	std::cout << "Equity: " << equity << "%" << std::endl;
	return 0;
}