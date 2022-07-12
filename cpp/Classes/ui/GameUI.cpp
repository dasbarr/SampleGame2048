#include "GameUI.h"
#include "cocos2d.h"
#include "game/GameConfig.h"
#include "ui/TopUI.h"
#include "ui/BottomUI.h"
#include "utils/ServiceLocator.h"

USING_NS_CC;

sample_game::GameUI::~GameUI() {
    CC_SAFE_RELEASE_NULL(_endGameWindow);
}

bool sample_game::GameUI::init() {
    if (!Node::init())
        return false;

    setContentSize(Size(GameConfig::s_gameWindowWidth, GameConfig::s_gameWindowHeight));

    auto* topUI = TopUI::create();
    topUI->setPosition(0, GameConfig::s_gameWindowHeight - GameConfig::s_topUIHeight);
    addChild(topUI);

    auto* bottomUI = BottomUI::create();
    addChild(bottomUI);

    _endGameWindow = EndGameWindow::create();
    // end game window should be above other gui elements
    _endGameWindow->setLocalZOrder(1);
    _endGameWindow->retain();

    auto* gameController = GET_SERVICE(GameController);
    gameController->onGameStateChanged.Connect(this, &GameUI::gameStateChangedHandler);

    return true;
}

void sample_game::GameUI::gameStateChangedHandler(GameController::GameState newGameState) {
    if (newGameState == GameController::GameState::NEW_GAME_PREPARATION) {
        // hide end game window
        removeChild(_endGameWindow, false);
    }
    else if (newGameState == GameController::GameState::GAME_ENDED) {
        // show end game window
        addChild(_endGameWindow);
    }
}
