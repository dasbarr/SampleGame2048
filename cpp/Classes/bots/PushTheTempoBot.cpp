#include "PushTheTempoBot.h"

sample_game::PushTheTempoBot::PushTheTempoBot() {
    _randomSource.seed(std::random_device{}());
}

sample_game::Move sample_game::PushTheTempoBot::calcNextMove(const std::vector<std::vector<int>>& gameBoardState,
                                                               const std::unordered_set<Move>& availableMoves) {
    if (availableMoves.empty())
        return Move::INCORRECT_MOVE;

    // make random available move
    std::vector<Move> availableMovesToSelect(availableMoves.begin(), availableMoves.end());
    std::shuffle(std::begin(availableMovesToSelect), std::end(availableMovesToSelect), _randomSource);
    return availableMovesToSelect[0];
}
