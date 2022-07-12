#include "ScoreProxy.h"
#include <limits>
#include "utils/SimpleLogger.h"

sample_game::ScoreProxy* sample_game::ScoreProxy::create() {
    auto* ret = new (std::nothrow) ScoreProxy();
    if (ret) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

unsigned int sample_game::ScoreProxy::getCurrentScore() const {
    return _currentScore;
}

unsigned int sample_game::ScoreProxy::getBestScore() const {
    return _bestScore;
}

void sample_game::ScoreProxy::clearCurrentScore() {
    _currentScore = 0;

    dispatchScoreChanged();
}

void sample_game::ScoreProxy::addScore(unsigned int pointsToAdd) {
    if (_currentScore > std::numeric_limits<unsigned int>::max() - pointsToAdd) {
        utils::SimpleLogger::warn("Score overflow, max value will be used.");

        _currentScore = std::numeric_limits<unsigned int>::max();
    }
    else {
        _currentScore += pointsToAdd;
    }

    if (_currentScore > _bestScore) {
        // update best score
        _bestScore = _currentScore;
    }

    dispatchScoreChanged();
}

bool sample_game::ScoreProxy::getIsNewRecord() const {
    return _currentScore == _bestScore;
}

void sample_game::ScoreProxy::dispatchScoreChanged() const {
    onScoreChanged.Emit(_currentScore, _bestScore);
}
