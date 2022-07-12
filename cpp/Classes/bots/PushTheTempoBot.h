#ifndef SAMPLEGAME2048_PUSHTHETEMPOBOT_H
#define SAMPLEGAME2048_PUSHTHETEMPOBOT_H

#include <random>
#include "IBot.h"

namespace sample_game {
    /**
     * Simple bot that makes random moves (no move availability checks).
     */
    class PushTheTempoBot : public IBot {
    public:
        PushTheTempoBot();
        ~PushTheTempoBot() = default;

        Move calcNextMove(const std::vector<std::vector<int>>& gameBoardState,
                          const std::unordered_set<Move>& availableMoves) override;

    private:
        std::default_random_engine _randomSource;
    };
}

#endif //SAMPLEGAME2048_PUSHTHETEMPOBOT_H
