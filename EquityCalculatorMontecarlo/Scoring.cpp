#include "Scoring.h"

#include <array>
#include <vector>
#include <iostream>
#include <tuple>
#include <algorithm>

namespace
{
	constexpr auto x = std::array<int, 4>{2, 2, 2, 1};
}

bool eval_best_hand(const std::vector<CardsWithTableCombined>& all_cards_with_table_combined)
// returns true if first player has best hand
{
	std::vector<std::tuple< std::vector<int>, std::vector<int>, std::string>> all_players_score;
	std::vector<std::tuple< std::vector<int>, std::vector<int>, std::string>>  all_players_score_original;
	bool best_hand;

	for (const auto& cards_with_table : all_cards_with_table_combined)
	{
		auto result = calc_score(cards_with_table);
		all_players_score.emplace_back(result);
	}
	all_players_score_original = all_players_score;

	std::sort(all_players_score.begin(), all_players_score.end(), std::greater<>());
	if (all_players_score[0] == all_players_score_original[0])
		best_hand = true; // first player is best hand
	else
		best_hand = false; // different player is best hand

	return best_hand;
}

template <typename T1, typename T2>
bool sortdesc_tuple(const std::tuple<T1, T2>& a, const std::tuple<T1, T2>& b)
{
	return (std::get<0>(a) > std::get<0>(b));
}

Score get_rcounts(const CardsWithTableCombined& all_cards_with_table_combined,
	std::vector<std::size_t> available_ranks,
	const std::string original_ranks) {
	Score rcounts;
	for (const auto& card : all_cards_with_table_combined) {
		available_ranks.emplace_back(original_ranks.find(card.substr(0, 1)));
	}
	for (int i = 0; i <= 12; i++) {
		int count = std::count(available_ranks.begin(), available_ranks.end(), i);
		if (count > 0) {
			rcounts.emplace_back(std::make_pair(count, i));
		}
	}
	return rcounts;
}

std::tuple< std::vector<int>, std::vector<int>, std::string> calc_score(const CardsWithTableCombined& all_cards_with_table_combined) {
	const std::string original_ranks = "23456789TJQKA";
	const std::vector<std::string> original_suits{ "C","D","H","S" };
	std::vector<std::size_t> available_ranks;
	std::vector<std::string> available_suits;
	std::vector<int> score;
	std::vector<int> card_ranks;
	std::string hand_type;
	bool flush = false;
	bool straight = false;

	Score rcounts;
	std::vector<std::tuple<std::string, int>> rsuits;

	rcounts = get_rcounts(all_cards_with_table_combined, available_ranks, original_ranks);

	// sort tuple and split into score and card ranks
	std::sort(rcounts.begin(), rcounts.end(), sortdesc_tuple<int, int>);
	for (auto it = std::make_move_iterator(rcounts.begin()),
		end = std::make_move_iterator(rcounts.end()); it != end; ++it)
	{
		score.push_back(std::get<0>(*it));  // amount of occurrences
		card_ranks.push_back(std::get<1>(*it));  // ranks of individual cards
	}

	bool potential_threeofakind = score[0] == 3;
	bool potential_twopair = score == std::vector<int> {2, 2, 1, 1, 1};
	bool potential_pair = score == std::vector<int> {2, 1, 1, 1, 1, 1};

	auto sub_score2 = slice(score, 0, 2);
	auto sub_score4 = slice(score, 0, 5);
	auto sub_score0 = slice(score, 0, 0);
	// # fullhouse(three of a kind and pair, or two three of a kind)
	if (sub_score2 == std::vector<int> {3, 2} || sub_score2 == std::vector<int> {3, 3}) {
		// make adjustment
		card_ranks = slice(card_ranks, 0, 2);
		score = { 3,2 };
	}
	// edge case: convert three pair to two pair
	//const auto x = &score[3];
	else if (sub_score4 == std::vector<int>{2, 2, 2, 1}) {
		score = { 2,2,1 };
		int kicker = std::max(card_ranks[2], card_ranks[3]);
		card_ranks = { card_ranks[0], card_ranks[1], kicker };
	}
	else if (score[0] == 4) {  // four of a kind
		score = { 4, };
		// avoid for example 11, 8, 9
		std::sort(card_ranks.begin(), card_ranks.end(), std::greater <>());
		card_ranks = { card_ranks[0], card_ranks[1] };
	}
	else if (score.size() >= 5) {  // high card, flush, straight and straight flush
		// straight
		// adjust for 5 high straight
		if (std::find(card_ranks.begin(), card_ranks.end(), 12) != card_ranks.end()) {
			card_ranks[0] += -1;
			std::sort(card_ranks.begin(), card_ranks.end(), std::greater <>());  // sort again
		}
		for (int i = 0; i < card_ranks.size() - 4; ++i) {
			bool straight = card_ranks[i] - card_ranks[i + 4] == 4;
			if (straight == true) {
				card_ranks = {
					card_ranks[i], card_ranks[i + 1], card_ranks[i + 2], card_ranks[i + 3],
					card_ranks[i + 4] };
				break;
			}
		}

		//flush
		for (std::string card : all_cards_with_table_combined) {
			available_suits.emplace_back(card.substr(1, 1));
		}

		std::vector<int> suit_counts;
		std::vector<std::string> suit_cards;
		for (const auto& suit : original_suits) {  // why can original_suits not be a string and suit a char?
			int count = std::count(available_suits.begin(), available_suits.end(), suit);
			if (count > 0) {
				rsuits.emplace_back(std::make_pair(suit, count));
			}
		}
		std::sort(rsuits.begin(), rsuits.end(), sortdesc_tuple<std::string, int>);
		flush = std::get<1>(rsuits[0]) >= 5; // the most occurred suit appear at least 5 times

		if (flush == true)
		{
			auto flush_suit = std::get<1>(rsuits[0]);
			CardsWithTableCombined flush_hand;
			for (auto card : all_cards_with_table_combined) {
				if (card[1] == flush_suit) {
					flush_hand.insert(card);
				}
			}

			Score rcounts_flush = get_rcounts(flush_hand, available_ranks, original_ranks);
			// sort tuple and split into score and card ranks
			std::sort(rcounts_flush.begin(), rcounts_flush.end(), sortdesc_tuple<int, int>);
			for (auto it = std::make_move_iterator(rcounts_flush.begin()),
				end = std::make_move_iterator(rcounts_flush.end()); it != end; ++it)
			{
				card_ranks.push_back(std::get<0>(*it));  // ranks of individual cards
				score.push_back(std::get<1>(*it));  // amount of occurrences
			}

			//	# check for straight in flush
			// if 12 in card_ranks and -1 not in card_ranks : # adjust if 5 high straight
			if (std::find(card_ranks.begin(), card_ranks.end(), 12) != card_ranks.end() &&
				!(std::find(card_ranks.begin(), card_ranks.end(), -1) != card_ranks.end())) {
			}
			card_ranks[0] += -1;
			for (int i = 0; i < card_ranks.size() - 4; i++) {
				straight = card_ranks[i] - card_ranks[i + 4] == 4;
				if (straight == true)
				{
					break;
				}
			}
		}
	}
	// no pair, straight, flush, or straight flush
	if (flush == false && straight == false)
		score = { 1 };
	else if (flush == true && straight == false)
		score = { 3, 1, 2 };
	else if (flush == false && straight == true)
		score = { 3, 1, 3 };
	else if (flush == true && straight == true)
		score = { 5 };

	if (score[0] == 1 && potential_threeofakind == true)
		score = { 3,1 };
	else if (score[0] == 1 && potential_twopair == true)
		score = { 2, 2, 1 };
	else if (score[0] == 1 && potential_pair == true)
		score = { 2, 1, 1 };

	if (score[0] == 5)
		// # crdRanks=crdRanks[:5] # five card rule makes no difference {:5] would be incorrect
		hand_type = "StraightFlush";
	else if (score[0] == 4)
		hand_type = "FoufOfAKind"; // crdRanks = crdRanks[:2] # already implemented above
	else if (slice(score, 0, 2) == std::vector<int> {3, 2})
		hand_type = "FullHouse"; // # crdRanks = crdRanks[:2] # already implmeneted above
	else if (slice(score, 0, 3) == std::vector<int> {3, 1, 3}) {
		hand_type = "Flush";
		card_ranks = slice(card_ranks, 0, 5);
	}

	else if (slice(score, 0, 3) == std::vector<int> {3, 1, 2}) {
		hand_type = "Straight";
		card_ranks = slice(card_ranks, 0, 5);
	}

	else if (slice(score, 0, 2) == std::vector<int> {3, 1}) {
		hand_type = "ThreeOfAKind";
		card_ranks = slice(card_ranks, 0, 3);
	}
	else if (slice(score, 0, 2) == std::vector<int> {3, 1}) {
		hand_type = "ThreeOfAKind";
		card_ranks = slice(card_ranks, 0, 3);
	}
	else if (slice(score, 0, 2) == std::vector<int> {2, 2}) {
		hand_type = "TwoPair";
		card_ranks = slice(card_ranks, 0, 3);
	}
	else if (score[0] == 2) {
		hand_type = "Pair";
		card_ranks = slice(card_ranks, 0, 4);
	}
	else if (score[0] == 1) {
		hand_type = "HighCard";
		card_ranks = slice(card_ranks, 0, 5);
	}
	else
		throw std::runtime_error("Card Type error!");

	auto res = std::make_tuple(score, card_ranks, hand_type);
	return res;
}