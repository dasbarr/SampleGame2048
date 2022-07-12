#include "BottomUI.h"
#include "game/GameConfig.h"
#include "utils/ButtonFactory.h"
#include "utils/ServiceLocator.h"
#include "localization/LocalizationManager.h"
#include "bots/BotController.h"

USING_NS_CC;

sample_game::BottomUI::~BottomUI() {
    CC_SAFE_RELEASE_NULL(_toggleBotButton);
    CC_SAFE_RELEASE_NULL(_botEnabledLabel);
}

bool sample_game::BottomUI::init() {
    if (!Node::init())
        return false;

    Size uiSize(GameConfig::s_gameWindowWidth, GameConfig::s_bottomUIHeight);
    setContentSize(uiSize);

    auto* background = LayerColor::create(Color4B(110,110,110,255), uiSize.width, uiSize.height);
    this->addChild(background);

    auto toggleBotButtonPosition = Vec2(10, uiSize.height * 0.5f);
    _toggleBotButton = utils::ButtonFactory::createAutoTranslatedButton(LocalizedStringId::START_BOT);
    _toggleBotButton->retain();
    _toggleBotButton->setContentSize(Size(130, 30));
    _toggleBotButton->setAnchorPoint(Vec2(0,0.5f));
    _toggleBotButton->setPosition(Vec2(10, uiSize.height * 0.5f));
    _toggleBotButton->addClickEventListener([](Ref* sender){
        GET_SERVICE(BotController)->toggleBot();
    });
    addChild(_toggleBotButton);

    _botEnabledLabel = AutoTranslatedUIText::create(
            LocalizedStringId::BOT_ENABLED, GameConfig::s_fontName, GameConfig::s_defaultFontSize
    );
    _botEnabledLabel->retain();
    _botEnabledLabel->setAnchorPoint(Vec2(0,0.5f));
    _botEnabledLabel->setPosition(
        Vec2(toggleBotButtonPosition.x + _toggleBotButton->getContentSize().width + 10, toggleBotButtonPosition.y)
    );
    addChild(_botEnabledLabel);

    auto* toggleLanguageButton = utils::ButtonFactory::createAutoTranslatedButton(LocalizedStringId::LANGUAGE_NAME);
    toggleLanguageButton->retain();
    toggleLanguageButton->setTitleFontName(GameConfig::s_fontName);
    toggleLanguageButton->setTitleFontSize(GameConfig::s_defaultFontSize);
    toggleLanguageButton->setAnchorPoint(Vec2(1,0.5));
    auto toggleLanguageButtonPosition = Vec2(GameConfig::s_gameWindowWidth - 10, uiSize.height * 0.5f);
    toggleLanguageButton->setPosition(toggleLanguageButtonPosition);
    toggleLanguageButton->addClickEventListener([](Ref* sender){
        GET_SERVICE(LocalizationManager)->toggleLanguage();
    });
    addChild(toggleLanguageButton);

    auto* languageLabel = AutoTranslatedUIText::create(
        LocalizedStringId::LANGUAGE, GameConfig::s_fontName, GameConfig::s_defaultFontSize
    );
    languageLabel->setAnchorPoint(Vec2(1,0.5));
    languageLabel->setPosition(
        Vec2(
            toggleLanguageButtonPosition.x - toggleLanguageButton->getContentSize().width - 10,
            toggleLanguageButtonPosition.y
        )
    );
    addChild(languageLabel);

    // update bot-related components when bot state changes
    auto* botController = GET_SERVICE(BotController);
    botController->onBotStateChanged.Connect(this, &BottomUI::updateBotStateIndication);
    // set initial state of bot-related components
    updateBotStateIndication(botController->isBotEnabled());

    return true;
}

void sample_game::BottomUI::updateBotStateIndication(bool botEnabled) {
    _toggleBotButton->setLocaleId(
        botEnabled
            ? LocalizedStringId::STOP_BOT
            : LocalizedStringId::START_BOT
    );

    _botEnabledLabel->setOpacity(botEnabled ? 255 : 0);
}
