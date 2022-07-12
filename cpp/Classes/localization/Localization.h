#ifndef SAMPLEGAME2048_LOCALIZATION_H
#define SAMPLEGAME2048_LOCALIZATION_H

#include <string>
#include <unordered_map>
#include "localization/LocalizedStringIds.h"
#include "LanguageIds.h"
#include "document.h"

namespace sample_game {
    /**
     * Contains unpacked localization data.
     */
    class Localization {
    public:
        Localization(const rapidjson::Value& languageData);
        virtual ~Localization() = default;

        /**
         * Gets id of the language used by that localization.
         * @return Id of the language used by that localization.
         */
        LanguageId getLanguageId() const;

        /**
         * Gets a localized string if it exists.
         * @param localizedStringId Id for that string.
         * @return Requested string if it exists, special 'missing' string otherwise.
         */
        const std::string& getLocalizedString(LocalizedStringId localizedStringId) const;

    protected:
        /**
         * Contains pairs 'localized string id -> localized string'.
         * @protected
         */
        std::unordered_map<int, std::string> _localizedStrings;

    private:
        /**
         * Id of the language used by that localization.
         * @private
         */
        LanguageId _languageId;

        /**
         * Special locale that will be used when requested string is missing.
         * @private
         */
        static const std::string s_missingLocale;
    };
}

#endif //SAMPLEGAME2048_LOCALIZATION_H
