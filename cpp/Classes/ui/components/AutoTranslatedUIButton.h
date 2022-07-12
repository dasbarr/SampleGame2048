#ifndef SAMPLEGAME2048_AUTOTRANSLATEDUIBUTTON_H
#define SAMPLEGAME2048_AUTOTRANSLATEDUIBUTTON_H

#include "ui/UIButton.h"
#include "localization/LocalizedStringIds.h"
#include "localization/AutoTranslator.h"

namespace sample_game {
    /**
     * UI button with auto-translation functionality.
     */
    class AutoTranslatedUIButton : public cocos2d::ui::Button, public AutoTranslator {
    public:
        static AutoTranslatedUIButton* create(LocalizedStringId localeId);

        ~AutoTranslatedUIButton() override = default;

        // note: that method is not virtual in cocos2d, so it's necessary to hide it
        void setTitleText(const std::string& text);

    CC_CONSTRUCTOR_ACCESS:
        bool init(LocalizedStringId localeId);

    protected:
        void setLocalizedString(const std::string& localizedString) override;

    private:
        AutoTranslatedUIButton() = default;
    };
}

#endif //SAMPLEGAME2048_AUTOTRANSLATEDUIBUTTON_H
