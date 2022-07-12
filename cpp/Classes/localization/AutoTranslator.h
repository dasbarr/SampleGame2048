#ifndef SAMPLEGAME2048_AUTOTRANSLATOR_H
#define SAMPLEGAME2048_AUTOTRANSLATOR_H

#include <string>
#include "SignalBase.h"
#include "localization/LocalizedStringIds.h"

namespace sample_game {
    /**
     * Provides automatic translation for one string when application language changes.
     */
    class AutoTranslator : public jl::SignalObserver {
    public:
        AutoTranslator() = default;
        ~AutoTranslator() = default;

        /**
         * Sets a new locale id.
         * @param localeId New locale id.
         */
        void setLocaleId(LocalizedStringId localeId);

        /**
         * Sets if auto translation is allowed or not. If not, auto translation will not be performed.
         * @param allowed True if auto translation is allowed, false otherwise.
         */
        void setAutoTranslationAllowed(bool allowed);

    protected:
        /**
         * Sets a localized string. Should be implemented by subclasses.
         * @param localizedString Localized string to set.
         * @protected
         */
        virtual void setLocalizedString(const std::string& localizedString) = 0;

    private:
        void updateLocalization();

        /**
         * Locale id that will be used to translate current component.
         * @private
         */
        LocalizedStringId _localeId = LocalizedStringId::EMPTY_LOCALE;

        /**
         * If true, label will be auto-translated when application language changes.
         * @private
         */
        bool _autoTranslationAllowed = false;
    };
}

#endif //SAMPLEGAME2048_AUTOTRANSLATOR_H
