#include "MainScene.h"
#include "ui/GameUI.h"
#include "game/GameController.h"
#include "utils/ServiceLocator.h"
#include "game/ScoreProxy.h"
#include "view/GameView.h"
#include "game/GameConfig.h"
#include "bots/BotController.h"
#include "bots/PushTheTempoBot.h"

USING_NS_CC;

bool sample_game::MainScene::init() {
    if (!Scene::init())
        return false;

    // init game services
    utils::ServiceLocator::registerService<GameBoardProxy>(GameBoardProxy::create());
    utils::ServiceLocator::registerService<ScoreProxy>(ScoreProxy::create());
    auto* gameView = GameView::create();
    utils::ServiceLocator::registerService<GameView>(gameView);
    auto* gameController = GameController::create();
    utils::ServiceLocator::registerService<GameController>(gameController);
    // use simple bot
    utils::ServiceLocator::registerService<BotController>(BotController::create<PushTheTempoBot>());

    // init visual components
    auto* background = LayerColor::create(Color4B(79,79,79,255));
    addChild(background);

    gameView->setAnchorPoint(Vec2(0.5, 0));
    gameView->setPosition(GameConfig::s_gameWindowWidth * 0.5f, (float)GameConfig::s_bottomUIHeight);
    addChild(gameView);

    auto* gameUI = GameUI::create();
    addChild(gameUI);

    // start the game
    gameController->startNewGame();

    return true;
}
