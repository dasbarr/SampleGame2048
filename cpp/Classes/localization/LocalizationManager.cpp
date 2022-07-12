#include "LocalizationManager.h"
#include "game/GameConfig.h"
#include "utils/SimpleLogger.h"
#include <CCFileUtils.h>
#include "document.h"

using namespace rapidjson;
USING_NS_CC;

const std::string sample_game::LocalizationManager::s_localizationsFileName = "Localizations.json";
const std::string sample_game::LocalizationManager::s_missingLanguage = "<no localization>";

sample_game::LocalizationManager* sample_game::LocalizationManager::create() {
    auto* ret = new (std::nothrow) LocalizationManager();
    if (ret) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

sample_game::LocalizationManager::LocalizationManager() {
    // load localizations from a file
    if (FileUtils::getInstance()->isFileExist(s_localizationsFileName)) {
        auto localizationsFileContents = FileUtils::getInstance()->getStringFromFile("Localizations.json");

        Document localizationsDocument;
        localizationsDocument.Parse(localizationsFileContents.c_str());

        auto& localizationsData = localizationsDocument["localizations"];
        for (SizeType i = 0; i < localizationsData.Size(); i++) {
            auto& languageData = localizationsData[i];

            auto localization = Localization(languageData);
            _localizations.emplace(localization.getLanguageId(), std::move(localization));
        }
    }

    // set initial language
    setLanguage(GameConfig::s_defaultLanguage);
}

const std::string& sample_game::LocalizationManager::getLocalizedString(LocalizedStringId localizedStringId) const {
    if (localizedStringId == LocalizedStringId::EMPTY_LOCALE) {
        static std::string emptyLocaleStr;
        return emptyLocaleStr;
    }

    if (_localizations.count(_currentLanguage) == 0) {
        utils::SimpleLogger::error("Current language is not set");
        return s_missingLanguage;
    }

    auto& currentLocalization = _localizations.at(_currentLanguage);
    return currentLocalization.getLocalizedString(localizedStringId);
}

void sample_game::LocalizationManager::toggleLanguage() {
    // We used ordered map, so we can use next language. We want to 'toggle' the language, so order of
    // localizations doesn't matter.
    auto nextLocalizationIter = std::next(_localizations.find(_currentLanguage));
    if (nextLocalizationIter == _localizations.end())
        nextLocalizationIter = _localizations.begin();

    auto newLanguage = nextLocalizationIter->first;
    setLanguage(newLanguage);
}

void sample_game::LocalizationManager::setLanguage(LanguageId languageToSet) {
    if (languageToSet == _currentLanguage)
        return; // already set
    if (_localizations.count(languageToSet) == 0) {
        utils::SimpleLogger::error(
                "Can't set language '" + std::to_string(languageToSet) + "' - localization data doesn't exist"
        );
        return;
    }

    _currentLanguage = languageToSet;
    onCurrentLanguageChanged.Emit();
}
