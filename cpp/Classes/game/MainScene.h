#ifndef SAMPLEGAME2048_MAINSCENE_H
#define SAMPLEGAME2048_MAINSCENE_H

#include "cocos2d.h"

namespace sample_game {
    /**
     * Main game scene.
     */
    class MainScene : public cocos2d::Scene {
    public:
        CREATE_FUNC(MainScene);

        ~MainScene() override = default;

    CC_CONSTRUCTOR_ACCESS:
        virtual bool init();

    private:
        MainScene() = default;
    };
}

#endif //SAMPLEGAME2048_MAINSCENE_H
