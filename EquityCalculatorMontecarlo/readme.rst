Poker hand evaluator with montecarlo simulation to calculate equity
===================================================================


The code implements a c++ version of a montecarlo simulation to
evaluate a poker hand by estimating the amount of wins assuming
all players stay in the game up to the river.

A similar implementation is also available in python (both in pure python
and in numpy). The pure python implementation is significantly slower. The numpy
version is almost 1000 faster, but lacks some flexibility. It's the aim
of this version over overcome them and also implement
ranges and give maximum flexibility at maximum speed.

`Scoring.cpp`: Contains logic to evaluate a hand.

`Test.cpp`: Contains unit tests for hand evaluation and montecarlo simulation.