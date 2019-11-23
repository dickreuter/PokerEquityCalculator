#pragma once

#include <string>
#include <set>
#include <list>
#include <vector>
#include "Scoring.h"

typedef std::set<std::string> CardsWithTableCombined;

struct Hand {
	Hand() = default;

	Hand(std::set<std::string> cards) : cards(std::move(cards)) {}

	std::set<std::string> cards;

	void insert(const std::string& card) {
		cards.insert(card);
	}

	void insert_hand(const Hand& hand) {
		for (const std::string& card : hand.cards)
			cards.insert(card);
	}

	[[nodiscard]] auto begin() const { return cards.begin(); }

	[[nodiscard]] auto end() const { return cards.end(); }
};

class Deck {
private:
	std::string ranks = "23456789TJQKA";
	std::string suits = "CDHS";
	Hand my_cards;
	std::set<std::string> remaining_cards_tmp;
	std::set<std::string> remaining_cards;
	std::set<std::string> cards_on_table;
	void print_set(const std::set<std::string>& set);
public:
	std::set<std::string> full_deck;

	std::vector<Hand> player_hands;

	Deck();

	void distribute_cards(int number_of_players);

	void remove_visible_cards(const Hand& my_cards_, const std::set<std::string>& cards_on_table);

	std::vector<CardsWithTableCombined> get_cards_combined();
};
