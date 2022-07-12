#ifndef SAMPLEGAME2048_LOCALIZATIONMANAGER_H
#define SAMPLEGAME2048_LOCALIZATIONMANAGER_H

#include <string>
#include <map>
#include "base/CCRef.h"
#include "Signal.h"
#include "localization/LocalizedStringIds.h"
#include "localization/Localization.h"
#include "localization/LanguageIds.h"

namespace sample_game {
    /**
     * Provides strings for game localization.
     */
    class LocalizationManager : public cocos2d::Ref {
    public:
        static LocalizationManager* create();

        ~LocalizationManager() override = default;

        /**
         * Dispatched when current language was changed.
         */
        jl::Signal<void()> onCurrentLanguageChanged;

        /**
         * Gets a localized string.
         * @param localizedStringId Id for that string.
         * @return Localized string with that id or default string if localization string is missing.
         */
        const std::string& getLocalizedString(LocalizedStringId localizationStringId) const;

        /**
         * Switches to another language (if possible).
         */
        void toggleLanguage();

    private:
        LocalizationManager();

        /**
         * Sets a specific language as current language.
         * @param languageToSet Id of the language that will be set.
         * @private
         */
        void setLanguage(LanguageId languageToSet);

        /**
         * Filename of a file with localizations data.
         * @private
         */
        static const std::string s_localizationsFileName;
        /**
         * Special locale that will be used when current language is not set properly.
         * @private
         */
        static const std::string s_missingLanguage;

        /**
         * Contains pairs 'language id -> localization for that language'.
         * @private
         */
        std::map<LanguageId, Localization> _localizations;

        /**
         * Id of a current language.
         * @private
         */
        LanguageId _currentLanguage = NOT_INITIALIZED;
    };
}

#endif //SAMPLEGAME2048_LOCALIZATIONMANAGER_H
