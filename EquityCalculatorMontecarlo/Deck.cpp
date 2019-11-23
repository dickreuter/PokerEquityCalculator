//
// Created by dickr on 06/11/2019.
//

#include <iostream>
#include "Deck.h"
#include <algorithm>
#include <random>
#include <iterator>

Deck::Deck() {
	std::string combined;
	std::cout << "Constructing deck..." << std::endl;
	for (char& r : ranks) {
		for (char& s : suits) {
			combined = std::string() + r + s;
			full_deck.insert(combined);
		};
	};
	std::cout << "Cards in deck: " << full_deck.size() << std::endl;
}

void Deck::remove_visible_cards(const Hand& my_cards_, const std::set<std::string>& cards_on_table_) {
	// remove my_cards and cards_on_table from full_deck
	set_difference(full_deck.begin(), full_deck.end(), my_cards_.begin(), my_cards_.end(),
		std::inserter(remaining_cards_tmp, remaining_cards_tmp.end()));

	// remove visible table cards from deck
	set_difference(remaining_cards_tmp.begin(), remaining_cards_tmp.end(), cards_on_table_.begin(),
		cards_on_table_.end(),
		std::inserter(remaining_cards, remaining_cards.end()));

	std::cout << "Remaining cards: " << remaining_cards.size() << std::endl;

	this->my_cards = my_cards_.cards;
	this->cards_on_table = cards_on_table_;

	std::cout << "Removed my cards from deck...\n";
}

void Deck::distribute_cards(int number_players) {
	constexpr size_t cards_in_hand = 2;

	std::vector<std::string> shuffled_deck(remaining_cards.begin(), remaining_cards.end());
	std::shuffle(shuffled_deck.begin(), shuffled_deck.end(), std::mt19937_64(std::random_device()()));
	std::vector<Hand> player_hands(number_players);  // empty container

	auto hand_it = player_hands.begin();
	*hand_it = Hand(my_cards);  // set my own cards
	hand_it++;

	auto card_it = shuffled_deck.begin();
	while (hand_it != player_hands.end()) {
		*hand_it = Hand(std::set<std::string>{*++card_it, * ++card_it});
		++hand_it;
	}

	while (cards_on_table.size() < 5) {
		cards_on_table.emplace(*++card_it);
	}

	// print out the hands
	for (auto const& player_hand : player_hands) {
		std::cout << "Cards: ";
		for (const auto& card : player_hand.cards)
			std::cout << card << " ";
		std::cout << std::endl;
	}
	this->player_hands = player_hands;

	std::cout << "Cards on table: ";
	print_set(cards_on_table);
}

std::vector<CardsWithTableCombined> Deck::get_cards_combined() {
	CardsWithTableCombined cards_with_table_combined;
	std::vector<CardsWithTableCombined> all_cards_with_table_combined;

	for (const auto& player_hand : player_hands) {
		cards_with_table_combined = player_hand.cards;
		cards_with_table_combined.insert(cards_on_table.begin(), cards_on_table.end());
		all_cards_with_table_combined.push_back(cards_with_table_combined);
	}

	return all_cards_with_table_combined;
}

void Deck::print_set(const std::set<std::string>& set) {
	for (const auto& card : set)
		std::cout << card << " ";
	std::cout << std::endl;
}