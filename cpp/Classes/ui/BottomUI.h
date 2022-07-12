#ifndef SAMPLEGAME2048_BOTTOMUI_H
#define SAMPLEGAME2048_BOTTOMUI_H

#include "cocos2d.h"
#include "SignalBase.h"
#include "ui/components/AutoTranslatedUIText.h"
#include "ui/components/AutoTranslatedUIButton.h"
#include "ui/UIButton.h"

namespace sample_game {
    /**
     * Bottom UI line.
     */
    class BottomUI : public cocos2d::Node, public jl::SignalObserver {
    public:
        CREATE_FUNC(BottomUI);

        ~BottomUI() override;

    CC_CONSTRUCTOR_ACCESS:
        bool init() override;

    private:
        BottomUI() = default;

        void updateBotStateIndication(bool botEnabled);

        /**
         * Toggle bot button.
         * @private
         */
        AutoTranslatedUIButton* _toggleBotButton = nullptr;

        /**
         * 'Bot enabled' label.
         * @private
         */
        AutoTranslatedUIText* _botEnabledLabel = nullptr;
    };
}

#endif //SAMPLEGAME2048_BOTTOMUI_H
