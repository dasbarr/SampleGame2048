#ifndef SAMPLEGAME2048_TOPUI_H
#define SAMPLEGAME2048_TOPUI_H

#include "cocos2d.h"
#include "SignalBase.h"

namespace sample_game {
    /**
     * Top UI line.
     */
    class TopUI : public cocos2d::Node, public jl::SignalObserver {
    public:
        CREATE_FUNC(TopUI);

        ~TopUI() override;

    CC_CONSTRUCTOR_ACCESS:
        bool init() override;

    private:
        TopUI() = default;

        /**
         * Label for current score.
         * @private
         */
        cocos2d::Label* _currentScoreLabel = nullptr;
        /**
         * Label for best score.
         * @private
         */
        cocos2d::Label* _bestScoreLabel = nullptr;

        void updateScores(unsigned int currentScore, unsigned int bestScore);
    };
}

#endif //SAMPLEGAME2048_TOPUI_H
