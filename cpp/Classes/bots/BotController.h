#ifndef SAMPLEGAME2048_BOTCONTROLLER_H
#define SAMPLEGAME2048_BOTCONTROLLER_H

#include <memory>
#include "cocos2d.h"
#include "Signal.h"
#include "SignalBase.h"
#include "bots/IBot.h"
#include "game/GameController.h"

namespace sample_game {
    /**
     * Controls a game bot.
     */
    class BotController : public cocos2d::Ref, public jl::SignalObserver {
    public:
        template<class TBot>
        static BotController* create() {
            auto* ret = new (std::nothrow) BotController();
            if (ret) {
                ret->_bot = std::make_unique<TBot>();

                ret->autorelease();
                return ret;
            }

            CC_SAFE_DELETE(ret);
            return nullptr;
        }

        ~BotController() override = default;

        /**
         * Dispatched when bot state (enabled or disabled) was changed. Contains true if bot is enabled now,
         * false otherwise.
         */
        jl::Signal<void(bool)> onBotStateChanged;

        /**
         * Checks if bot is enabled or not.
         * @return true if bot is enabled now, false otherwise.
         */
        bool isBotEnabled() const;

        /**
         * Toggles the bot.
         */
        void toggleBot();

    private:
        BotController() = default;

        void gameStateChangedHandler(GameController::GameState newGameState);

        /**
         * Makes a game move.
         * @private
         */
        void makeMove();

        /**
         * If bot can't make a valid move after that number of attempts, it should be stopped.
         * @private
         */
        static const unsigned int s_maxMoveAttempts = 10;

        /**
         * Bot state (enabled or disabled).
         * @private
         */
        bool _botEnabled = false;

        std::unique_ptr<IBot> _bot;
    };
}

#endif //SAMPLEGAME2048_BOTCONTROLLER_H
