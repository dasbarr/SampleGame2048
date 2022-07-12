#ifndef SAMPLEGAME2048_IBOT_H
#define SAMPLEGAME2048_IBOT_H

#include "game/GameMoves.h"
#include <unordered_set>

namespace sample_game {
    /**
     * Common interface for all bots.
     */
    class IBot {
    public:
        /**
         * Calculates a new move based on the game state provided.
         * @param gameBoardState State of the game board.
         * @param availableMoves Available moves for that state.
         * @return Move that bot should make from that game state.
         */
        virtual Move calcNextMove(const std::vector<std::vector<int>>& gameBoardState,
                                  const std::unordered_set<Move>& availableMoves) = 0;
    };
}

#endif //SAMPLEGAME2048_IBOT_H
