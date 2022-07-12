#ifndef SAMPLEGAME2048_GAMECONTROLLER_H
#define SAMPLEGAME2048_GAMECONTROLLER_H

#include <vector>
#include "cocos2d.h"
#include "SignalBase.h"
#include "Signal.h"
#include "game/GameBoardProxy.h"
#include "game/BoardTileMoveInfo.h"
#include "game/GameMoves.h"

namespace sample_game {
    /**
     * Holds main game logic.
     */
    class GameController : public cocos2d::Ref, public jl::SignalObserver {
    public:
        /**
         * Represents game state.
         */
        enum GameState {
            UNINITIALIZED,         // game state before initialization
            NEW_GAME_PREPARATION,  // preparing for the new game start
            WAITING_FOR_INPUT,     // game is waiting for the player/bot input
            GAME_TURN_IN_PROGRESS, // waiting for game turn end
            GAME_ENDED             // game ended (win or lose)
        };

        static GameController* create();

        ~GameController() override = default;

        /**
         * Dispatched when a new game state was set. Contains new game state.
         */
        jl::Signal<void(GameState)> onGameStateChanged;

        GameState getCurrentGameState() const;

        /**
         * Interrupts current game and starts a new one.
         */
        void startNewGame();

        /**
         * Makes a game move (if possible).
         * @param move Move to make.
         * @return True if move was successful, false otherwise.
         */
        bool makeMove(Move move);

    private:
        GameController();

        /**
         * Sets a new game state.
         * @param newGameState New game state to set.
         * @private
         */
        void setGameState(GameState newGameState);

        /**
         * Ends current turn, starts a new game turn (if possible) or ends the game.
         */
        void endCurrentTurn();

        /**
         * Handler for user input.
         * @param userInput KeyCode of the key pressed by the player.
         * @private
         */
        void userInputHandler(const cocos2d::EventKeyboard::KeyCode userInput);

        /**
         * Current game state.
         * @private
         */
        GameState _currentGameState = GameState::UNINITIALIZED;
    };
}

#endif //SAMPLEGAME2048_GAMECONTROLLER_H
