#ifndef SAMPLEGAME2048_ENDGAMEWINDOW_H
#define SAMPLEGAME2048_ENDGAMEWINDOW_H

#include "cocos2d.h"
#include "ui/components/AutoTranslatedUIText.h"
#include "ui/UIText.h"
#include "game/GameController.h"

namespace sample_game {
    /**
     * End game window, will be shown when player wins or loses the game.
     */
    class EndGameWindow : public cocos2d::Node, public jl::SignalObserver {
    public:
        CREATE_FUNC(EndGameWindow);

        ~EndGameWindow() override;

    CC_CONSTRUCTOR_ACCESS:
        bool init() override;

    private:
        EndGameWindow() = default;

        /**
         * Creates an inner window (window with content).
         * @return Created window.
         * @private
         */
        cocos2d::Node* createInnerWindow();

        void gameStateChangedHandler(GameController::GameState newGameState);

        /**
         * Updates window contents.
         */
        void updateContents();

        /**
         * If player wins, that label will be shown.
         * @private
         */
        AutoTranslatedUIText* _winLabel = nullptr;
        /**
         * If player loses, that label will be shown.
         * @private
         */
        AutoTranslatedUIText* _loseLabel = nullptr;

        /**
         * Label that shows player current score.
         * @private
         */
        cocos2d::ui::Text* _scoreLabel = nullptr;

        /**
         * 'New record!' label.
         * @private
         */
        AutoTranslatedUIText* _newRecordLabel = nullptr;
    };
}

#endif //SAMPLEGAME2048_ENDGAMEWINDOW_H
