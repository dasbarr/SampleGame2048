#include "ButtonFactory.h"
#include "ui/UIScale9Sprite.h"
#include "game/GameConfig.h"

USING_NS_CC;

Size sample_game::utils::ButtonFactory::s_defaultButtonSize = Size(100, 30);

ui::Button* sample_game::utils::ButtonFactory::createButton(const Size& buttonSize) {
    auto* button = ui::Button::create();
    initButton(button, buttonSize);

    return button;
}

sample_game::AutoTranslatedUIButton* sample_game::utils::ButtonFactory::createAutoTranslatedButton(
    LocalizedStringId localeId, const cocos2d::Size& buttonSize
) {
    auto* button = AutoTranslatedUIButton::create(localeId);
    initButton(button, buttonSize);

    return button;
}

void sample_game::utils::ButtonFactory::initButton(cocos2d::ui::Button* button, const cocos2d::Size& buttonSize) {
    // button will use default texture, so it's necessary to set texture rect and button state colors properly
    Rect defaultTextureRect(0, 0, 2, 2);
    // normal state
    auto* buttonRendererNormal = button->getRendererNormal();
    buttonRendererNormal->setTextureRect(defaultTextureRect);
    buttonRendererNormal->setColor(Color3B(168, 168, 168));
    // clicked state
    auto* buttonRendererClicked = button->getRendererClicked();
    buttonRendererClicked->setTextureRect(defaultTextureRect);
    buttonRendererClicked->setColor(Color3B(188, 188, 188));
    // disabled state
    auto* buttonRendererDisabled = button->getRendererDisabled();
    buttonRendererDisabled->setTextureRect(defaultTextureRect);
    buttonRendererDisabled->setColor(Color3B(168, 168, 168));
    buttonRendererDisabled->setOpacity(128);

    button->ignoreContentAdaptWithSize(false);
    button->setContentSize(buttonSize);

    // disable zoom
    button->setZoomScale(0);

    // set title label params
    button->setTitleFontName(GameConfig::s_fontName);
    button->setTitleFontSize(GameConfig::s_defaultFontSize);
    button->setTitleColor(Color3B::BLACK);
}
