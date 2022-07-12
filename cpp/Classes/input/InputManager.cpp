#include "InputManager.h"
#include <unordered_set>

USING_NS_CC;

sample_game::InputManager* sample_game::InputManager::create() {
    auto* ret = new (std::nothrow) InputManager();
    if (ret) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

sample_game::InputManager::~InputManager() {
    auto* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->removeEventListener(_eventListenerKeyboard);

    CC_SAFE_RELEASE_NULL(_eventListenerKeyboard);
}

sample_game::InputManager::InputManager() {
    _eventListenerKeyboard = EventListenerKeyboard::create();
    _eventListenerKeyboard->retain();
    _eventListenerKeyboard->onKeyReleased = CC_CALLBACK_2(InputManager::keyReleasedHandler, this);

    auto* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithFixedPriority(_eventListenerKeyboard, 1);
}

void sample_game::InputManager::keyReleasedHandler(EventKeyboard::KeyCode keyCode, Event* event) {
    if (!_playerInputAllowed)
        return;

    // keys used in game
    static auto controlKeys = std::unordered_set<EventKeyboard::KeyCode>({
         EventKeyboard::KeyCode::KEY_W, EventKeyboard::KeyCode::KEY_UP_ARROW,
         EventKeyboard::KeyCode::KEY_A, EventKeyboard::KeyCode::KEY_LEFT_ARROW,
         EventKeyboard::KeyCode::KEY_S, EventKeyboard::KeyCode::KEY_DOWN_ARROW,
         EventKeyboard::KeyCode::KEY_D, EventKeyboard::KeyCode::KEY_RIGHT_ARROW
    });

    if (controlKeys.count(keyCode) > 0) {
        // player pressed one of control keys
        onPlayerInput.Emit(keyCode);
    }
}

void sample_game::InputManager::setPlayerInputAllowed(bool value) {
    _playerInputAllowed = value;
}
