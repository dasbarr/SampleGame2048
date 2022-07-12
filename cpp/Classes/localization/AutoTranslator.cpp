#include "AutoTranslator.h"
#include "localization/LocalizationManager.h"
#include "utils/ServiceLocator.h"

void sample_game::AutoTranslator::setLocaleId(LocalizedStringId localeId) {
    _localeId = localeId;

    if (_autoTranslationAllowed) {
        updateLocalization();
    }
    else {
        // setting a new locale will enable auto translation
        setAutoTranslationAllowed(true);
    }
}

void sample_game::AutoTranslator::updateLocalization() {
    if (!_autoTranslationAllowed)
        return;

    auto& localizedString = GET_SERVICE(LocalizationManager)->getLocalizedString(_localeId);
    setLocalizedString(localizedString);
}

void sample_game::AutoTranslator::setAutoTranslationAllowed(bool allowed) {
    if (_autoTranslationAllowed == allowed)
        return;

    _autoTranslationAllowed = allowed;

    auto* localizationManager = GET_SERVICE(LocalizationManager);
    if (allowed) {
        updateLocalization();
        localizationManager->onCurrentLanguageChanged.Connect(this, &AutoTranslator::updateLocalization);
    }
    else {
        localizationManager->onCurrentLanguageChanged.Disconnect(this, &AutoTranslator::updateLocalization);
    }
}
