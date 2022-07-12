#include "TopUI.h"
#include "game/GameConfig.h"
#include "utils/ButtonFactory.h"
#include "utils/ServiceLocator.h"
#include "localization/LocalizationManager.h"
#include "game/ScoreProxy.h"
#include "game/GameController.h"
#include "ui/components/AutoTranslatedUIText.h"

USING_NS_CC;

sample_game::TopUI::~TopUI() {
    CC_SAFE_RELEASE_NULL(_currentScoreLabel);
    CC_SAFE_RELEASE_NULL(_bestScoreLabel);
}

bool sample_game::TopUI::init() {
    if (!Node::init())
        return false;

    Size uiSize(GameConfig::s_gameWindowWidth, GameConfig::s_topUIHeight);
    setContentSize(uiSize);

    auto* background = LayerColor::create(Color4B(110,110,110,255), uiSize.width, uiSize.height);
    this->addChild(background);

    auto* descLabel = AutoTranslatedUIText::create(
        LocalizedStringId::GAME_DESCRIPTION, GameConfig::s_fontName, 18
    );
    descLabel->setPosition(Vec2(10, 120));
    descLabel->setTextHorizontalAlignment(TextHAlignment::LEFT);
    descLabel->setAnchorPoint(Vec2(0, 1));
    descLabel->ignoreContentAdaptWithSize(false);
    descLabel->setTextAreaSize(Size(GameConfig::s_gameWindowWidth - 20, 70));
    addChild(descLabel);

    auto* newGameButton = utils::ButtonFactory::createAutoTranslatedButton(LocalizedStringId::NEW_GAME);
    newGameButton->setTitleFontName(GameConfig::s_fontName);
    newGameButton->setAnchorPoint(Vec2(0, 0));
    newGameButton->setPosition(Vec2(10, 10));
    newGameButton->addClickEventListener([](Ref* sender){
        GET_SERVICE(GameController)->startNewGame();
    });
    addChild(newGameButton);

    auto* currentScoreTitleLabel = AutoTranslatedUIText::create(
        LocalizedStringId::CURRENT_SCORE_TITLE, GameConfig::s_fontName, GameConfig::s_defaultFontSize
    );
    currentScoreTitleLabel->setAnchorPoint(Vec2(1, 0));
    currentScoreTitleLabel->setPosition(Vec2(680, 26));
    addChild(currentScoreTitleLabel);
    _currentScoreLabel = Label::createWithSystemFont("", GameConfig::s_fontName, GameConfig::s_defaultFontSize);
    _currentScoreLabel->retain();
    _currentScoreLabel->setAnchorPoint(Vec2(0.5, 0));
    _currentScoreLabel->setPosition(640, 3);
    addChild(_currentScoreLabel);

    auto* bestScoreTitleLabel = AutoTranslatedUIText::create(
        LocalizedStringId::BEST_SCORE_TITLE, GameConfig::s_fontName, GameConfig::s_defaultFontSize
    );
    bestScoreTitleLabel->setAnchorPoint(Vec2(1, 0));
    bestScoreTitleLabel->setPosition(Vec2(790, 26));
    addChild(bestScoreTitleLabel);
    _bestScoreLabel = Label::createWithSystemFont("", GameConfig::s_fontName, GameConfig::s_defaultFontSize);
    _bestScoreLabel->retain();
    _bestScoreLabel->setAnchorPoint(Vec2(0.5, 0));
    _bestScoreLabel->setPosition(750, 3);
    addChild(_bestScoreLabel);

    // subscribe to score change
    auto* scoreProxy = GET_SERVICE(ScoreProxy);
    scoreProxy->onScoreChanged.Connect(this, &TopUI::updateScores);
    // set initial score values
    updateScores(scoreProxy->getCurrentScore(), scoreProxy->getBestScore());

    return true;
}

void sample_game::TopUI::updateScores(unsigned int currentScore, unsigned int bestScore) {
    _currentScoreLabel->setString(std::to_string(currentScore));
    _bestScoreLabel->setString(std::to_string(bestScore));
}
