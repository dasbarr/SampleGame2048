#ifndef SAMPLEGAME2048_AUTOTRANSLATEDUITEXT_H
#define SAMPLEGAME2048_AUTOTRANSLATEDUITEXT_H

#include "ui/UIText.h"
#include "localization/LocalizedStringIds.h"
#include "localization/AutoTranslator.h"

namespace sample_game {
    /**
     * UI text with auto-translation functionality.
     */
    class AutoTranslatedUIText : public cocos2d::ui::Text, public AutoTranslator {
    public:
        static AutoTranslatedUIText* create(LocalizedStringId localeId, const std::string& fontName, float fontSize);

        ~AutoTranslatedUIText() override = default;

        // note: that method is not virtual in cocos2d, so it's necessary to hide it
        void setString(const std::string& text);

    CC_CONSTRUCTOR_ACCESS:
        bool init(LocalizedStringId localeId, const std::string& fontName, float fontSize);

    protected:
        void setLocalizedString(const std::string& localizedString) override;

    private:
        AutoTranslatedUIText() = default;
    };
}

#endif //SAMPLEGAME2048_AUTOTRANSLATEDUITEXT_H
