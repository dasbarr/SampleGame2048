#ifndef SAMPLEGAME2048_GAMEUI_H
#define SAMPLEGAME2048_GAMEUI_H

#include <string>
#include "cocos2d.h"
#include "SignalBase.h"
#include "ui/EndGameWindow.h"
#include "game/GameController.h"

namespace sample_game {
    /**
     * Represents game UI.
     */
    class GameUI : public cocos2d::Node, public jl::SignalObserver {
    public:
        CREATE_FUNC(GameUI);

        ~GameUI() override;

    CC_CONSTRUCTOR_ACCESS:
        bool init() override;

    private:
        GameUI() = default;

        void gameStateChangedHandler(GameController::GameState newGameState);

        EndGameWindow* _endGameWindow = nullptr;
    };
}

#endif //SAMPLEGAME2048_GAMEUI_H
