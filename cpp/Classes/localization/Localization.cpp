#include "Localization.h"
#include "utils/SimpleLogger.h"

using namespace rapidjson;

const std::string sample_game::Localization::s_missingLocale = "<missing>";

sample_game::Localization::Localization(const rapidjson::Value& languageData) {
    // unpack language id
    auto languageIdInt = languageData["languageId"].GetInt();
    _languageId = languageIdInt > LanguageId::FIRST_ELEMENT && languageIdInt < LanguageId::LAST_ELEMENT
        ? static_cast<LanguageId>(languageIdInt)
        : LanguageId::UNSUPPORTED;

    // unpack localized strings
    auto& localizedStrings = languageData["localizedStrings"];
    for (SizeType i = 0; i < localizedStrings.Size(); i++) {
        auto& localizedStringData = localizedStrings[i];

        auto localizedStringId = localizedStringData["id"].GetInt();
        auto localizedString = localizedStringData["localizedString"].GetString();
        _localizedStrings[localizedStringId] = std::string(localizedString);
    }
}

sample_game::LanguageId sample_game::Localization::getLanguageId() const {
    return _languageId;
}

const std::string& sample_game::Localization::getLocalizedString(LocalizedStringId localizedStringId) const {
    if (_localizedStrings.count(localizedStringId) > 0)
        return _localizedStrings.at(localizedStringId);

    utils::SimpleLogger::error("Localized string '" + std::to_string(localizedStringId) + "' is missing");
    return s_missingLocale;
}
