#include "AutoTranslatedUIText.h"

sample_game::AutoTranslatedUIText* sample_game::AutoTranslatedUIText::create(LocalizedStringId localeId,
                                                                               const std::string& fontName,
                                                                               float fontSize
) {
    auto* text = new (std::nothrow) AutoTranslatedUIText();
    if (text && text->init(localeId, fontName, fontSize)) {
        text->autorelease();
        return text;
    }

    CC_SAFE_DELETE(text);
    return nullptr;
}

bool sample_game::AutoTranslatedUIText::init(LocalizedStringId localeId, const std::string& fontName, float fontSize) {
    if (!Text::init("", fontName, fontSize))
        return false;

    setLocaleId(localeId);

    return true;
}

void sample_game::AutoTranslatedUIText::setString(const std::string& text) {
    // setting a string manually will remove auto translation
    setAutoTranslationAllowed(false);
    Text::setString(text);
}

void sample_game::AutoTranslatedUIText::setLocalizedString(const std::string& localizedString) {
    Text::setString(localizedString);
}
