#ifndef SAMPLEGAME2048_INPUTMANAGER_H
#define SAMPLEGAME2048_INPUTMANAGER_H

#include "cocos2d.h"
#include "Signal.h"

namespace sample_game {
    /**
     * Handles player input.
     */
    class InputManager : public cocos2d::Ref {
    public:
        static InputManager* create();

        ~InputManager() override;

        /**
         * Dispatched when player presses some button. Contains pressed button keyCode.
         */
        jl::Signal<void(cocos2d::EventKeyboard::KeyCode)> onPlayerInput;

        /**
         * Sets if player input allowed or not. If not, game will not receive signals related to button press.
         * @param value True for 'allowed' state, false otherwise.
         */
        void setPlayerInputAllowed(bool value);

    private:
        InputManager();

        void keyReleasedHandler(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

        /**
         * Event listener for keyboard events.
         * @private
         */
        cocos2d::EventListenerKeyboard* _eventListenerKeyboard = nullptr;

        /**
         * Indicates if player input is allowed or not.
         * @private
         */
        bool _playerInputAllowed = true;
    };
}

#endif //SAMPLEGAME2048_INPUTMANAGER_H
