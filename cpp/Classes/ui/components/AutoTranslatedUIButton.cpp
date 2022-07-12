#include "AutoTranslatedUIButton.h"

USING_NS_CC;

sample_game::AutoTranslatedUIButton* sample_game::AutoTranslatedUIButton::create(LocalizedStringId localeId) {
    auto* button = new (std::nothrow) AutoTranslatedUIButton();
    if (button && button->init(localeId)) {
        button->autorelease();
        return button;
    }

    CC_SAFE_DELETE(button);
    return nullptr;
}

bool sample_game::AutoTranslatedUIButton::init(LocalizedStringId localeId) {
    if (!ui::Button::init())
        return false;

    setLocaleId(localeId);

    return true;
}

void sample_game::AutoTranslatedUIButton::setTitleText(const std::string& text) {
    // setting a string manually will remove auto translation
    setAutoTranslationAllowed(false);
    ui::Button::setTitleText(text);
}

void sample_game::AutoTranslatedUIButton::setLocalizedString(const std::string& localizedString) {
    ui::Button::setTitleText(localizedString);
}
