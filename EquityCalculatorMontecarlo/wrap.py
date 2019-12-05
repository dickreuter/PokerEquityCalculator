import cppimport

mc = cppimport.imp("Scoring")


def _run(my_cards, cards_on_table, players):
    equity = mc.montecarlo(my_cards, cards_on_table, players, 1000)
    print(equity)


if __name__ == "__main__":
    my_cards = {'3H', '3S'}
    cards_on_table = {'8S', '4S', 'QH', '8C', '4H'}
    players = 2
    _run(my_cards, cards_on_table, players)
