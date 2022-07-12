#include "EndGameWindow.h"
#include <string>
#include "utils/ButtonFactory.h"
#include "game/GameConfig.h"
#include "utils/ServiceLocator.h"
#include "game/ScoreProxy.h"

USING_NS_CC;

sample_game::EndGameWindow::~EndGameWindow() {
    CC_SAFE_RELEASE_NULL(_winLabel);
    CC_SAFE_RELEASE_NULL(_loseLabel);
    CC_SAFE_RELEASE_NULL(_scoreLabel);
    CC_SAFE_RELEASE_NULL(_newRecordLabel);
}

bool sample_game::EndGameWindow::init() {
    if (!Node::init())
        return false;

    setContentSize(Size(GameConfig::s_gameWindowWidth, GameConfig::s_gameWindowHeight));

    // create modal background
    auto* backgroundShadow = LayerColor::create(Color4B(0,0,0,200));
    addChild(backgroundShadow);
    // disable clicks on the content below background shadow
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [](Touch* touch, Event* event) -> bool { return true; };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    // create inner window
    auto* innerWindow = createInnerWindow();
    innerWindow->setPositionNormalized(Vec2(0.5, 0.5));
    addChild(innerWindow);

    // subscribe to game end
    GET_SERVICE(GameController)->onGameStateChanged.Connect(this, &EndGameWindow::gameStateChangedHandler);

    return true;
}

void sample_game::EndGameWindow::gameStateChangedHandler(GameController::GameState newGameState) {
    if (newGameState == GameController::GameState::GAME_ENDED)
        updateContents();
}

void sample_game::EndGameWindow::updateContents() {
    auto* gameBoardProxy = GET_SERVICE(GameBoardProxy);
    auto gameWon = gameBoardProxy->isWinTileAcquired();

    _winLabel->setOpacity(gameWon ? 255 : 0);
    _loseLabel->setOpacity(gameWon ? 0 : 255);

    auto* scoreProxy = GET_SERVICE(ScoreProxy);
    _scoreLabel->setString(std::to_string(scoreProxy->getCurrentScore()));

    _newRecordLabel->setOpacity(scoreProxy->getIsNewRecord() ? 255 : 0);
}

cocos2d::Node* sample_game::EndGameWindow::createInnerWindow() {
    Size innerWindowSize(500, 300);
    auto* innerWindow = Node::create();
    innerWindow->setContentSize(innerWindowSize);
    innerWindow->setAnchorPoint(Vec2(0.5, 0.5));

    auto* background = LayerColor::create(
        Color4B(110,110,110,255), innerWindowSize.width, innerWindowSize.height
    );
    innerWindow->addChild(background);

    auto winLabelPosition = Vec2(innerWindowSize.width * 0.5f, innerWindowSize.height - 30);
    float titleFontSize = 30;
    _winLabel = AutoTranslatedUIText::create(
        LocalizedStringId::END_GAME_WINDOW_WIN,
        GameConfig::s_fontName, titleFontSize
    );
    _winLabel->retain();
    _winLabel->setAnchorPoint(Vec2(0.5,1));
    _winLabel->setPosition(winLabelPosition);
    innerWindow->addChild(_winLabel);

    _loseLabel = AutoTranslatedUIText::create(
            LocalizedStringId::END_GAME_WINDOW_LOSE,
            GameConfig::s_fontName, titleFontSize
    );
    _loseLabel->retain();
    _loseLabel->setAnchorPoint(Vec2(0.5,1));
    _loseLabel->setPosition(winLabelPosition);
    innerWindow->addChild(_loseLabel);

    auto scoreTitleLabelPosition = Vec2(winLabelPosition.x, winLabelPosition.y - 90);
    auto* scoreTitleLabel = AutoTranslatedUIText::create(
            LocalizedStringId::END_GAME_WINDOW_SCORE,
            GameConfig::s_fontName, GameConfig::s_defaultFontSize
    );
    scoreTitleLabel->setAnchorPoint(Vec2(0.5,1));
    scoreTitleLabel->setPosition(scoreTitleLabelPosition);
    innerWindow->addChild(scoreTitleLabel);

    auto scoreLabelPosition = Vec2(scoreTitleLabelPosition.x, scoreTitleLabelPosition.y - 40);
    _scoreLabel = ui::Text::create("123", GameConfig::s_fontName, 25);
    _scoreLabel->retain();
    _scoreLabel->setPosition(scoreLabelPosition);
    innerWindow->addChild(_scoreLabel);

    _newRecordLabel = AutoTranslatedUIText::create(
            LocalizedStringId::END_GAME_WINDOW_NEW_RECORD,
            GameConfig::s_fontName, 25
    );
    _newRecordLabel->retain();
    _newRecordLabel->setAnchorPoint(Vec2(0.5,1));
    _newRecordLabel->setPosition(Vec2(scoreLabelPosition.x, scoreLabelPosition.y - 30));
    innerWindow->addChild(_newRecordLabel);

    auto* newGameButton = utils::ButtonFactory::createAutoTranslatedButton(LocalizedStringId::END_GAME_WINDOW_PLAY_AGAIN);
    newGameButton->setContentSize(Size(130, 30));
    newGameButton->setTitleFontName(GameConfig::s_fontName);
    newGameButton->setAnchorPoint(Vec2(0.5f,0));
    newGameButton->setPosition(Vec2(innerWindowSize.width * 0.5f, 30));
    newGameButton->addClickEventListener([](Ref* sender){
        GET_SERVICE(GameController)->startNewGame();
    });
    innerWindow->addChild(newGameButton);

    return innerWindow;
}
