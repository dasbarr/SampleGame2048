#ifndef SAMPLEGAME2048_BUTTONFACTORY_H
#define SAMPLEGAME2048_BUTTONFACTORY_H

#include "math/CCGeometry.h"
#include "localization/LocalizedStringIds.h"
#include "ui/components/AutoTranslatedUIButton.h"

namespace sample_game::utils {
    /**
     * Creates UI buttons.
     */
    class ButtonFactory {
    public:
        ButtonFactory() = delete;

        /**
         * Creates a new button that will use default texture.
         * @param buttonSize Size of the button.
         * @return Created button.
         */
        static cocos2d::ui::Button* createButton(const cocos2d::Size& buttonSize = s_defaultButtonSize);
        /**
         * Creates a new button with auto-translated label. Button will use default texture.
         * @param localeId Localized string id for button title.
         * @param buttonSize Size of the button.
         * @return Created button.
         */
        static AutoTranslatedUIButton* createAutoTranslatedButton(LocalizedStringId localeId,
                                                                  const cocos2d::Size& buttonSize = s_defaultButtonSize);

    private:
        static void initButton(cocos2d::ui::Button* button, const cocos2d::Size& buttonSize);

        /**
         * Default button size.
         * @private
         */
        static cocos2d::Size s_defaultButtonSize;
    };
}

#endif //SAMPLEGAME2048_BUTTONFACTORY_H
