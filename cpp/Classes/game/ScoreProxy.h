#ifndef SAMPLEGAME2048_SCOREPROXY_H
#define SAMPLEGAME2048_SCOREPROXY_H

#include "base/CCRef.h"
#include "Signal.h"

namespace sample_game {
    /**
     * Holds info about player score.
     */
    class ScoreProxy : public cocos2d::Ref {
    public:
        static ScoreProxy* create();

        ~ScoreProxy() override = default;

        /**
         * Dispatched when player score changes. Contains current score and best score.
         */
        jl::Signal<void(unsigned int, unsigned int)> onScoreChanged;

        unsigned int getCurrentScore() const;
        unsigned int getBestScore() const;

        /**
         * Clears current score (best score will remain untouched).
         */
        void clearCurrentScore();

        /**
         * Adds points to the current score. Updates best score if necessary.
         * @param pointsToAdd That number of points will be added to the score.
         */
        void addScore(unsigned int pointsToAdd);

        /**
         * Checks if there is a new record.
         * @return True if there is a new record, false otherwise.
         */
        bool getIsNewRecord() const;

    private:
        ScoreProxy() = default;

        void dispatchScoreChanged() const;

        unsigned int _currentScore = 0;
        unsigned int _bestScore = 0;
    };
}

#endif //SAMPLEGAME2048_SCOREPROXY_H
