#include "BotController.h"
#include "utils/ServiceLocator.h"
#include "input/InputManager.h"

bool sample_game::BotController::isBotEnabled() const {
    return _botEnabled;
}

void sample_game::BotController::toggleBot() {
    _botEnabled = !_botEnabled;

    // disable user input when bot is playing
    GET_SERVICE(InputManager)->setPlayerInputAllowed(!_botEnabled);

    auto* gameController = GET_SERVICE(GameController);
    if (_botEnabled) {
        // subscribe to game state change to make moves
        gameController->onGameStateChanged.Connect(this, &BotController::gameStateChangedHandler);

        if (gameController->getCurrentGameState() == GameController::GameState::WAITING_FOR_INPUT) {
            // make 1st bot move
            makeMove();
        }
    }
    else {
        // unsubscribe
        gameController->onGameStateChanged.Disconnect(this, &BotController::gameStateChangedHandler);
    }

    onBotStateChanged.Emit(_botEnabled);
}

void sample_game::BotController::gameStateChangedHandler(GameController::GameState newGameState) {
    if (!_botEnabled)
        return;

    if (newGameState == GameController::GameState::NEW_GAME_PREPARATION ||
        newGameState == GameController::GameState::GAME_ENDED
    ) {
        // game was ended or new game is about to start, in that case bot should be disabled
        toggleBot();
    }
    else if (newGameState == GameController::GameState::WAITING_FOR_INPUT) {
        // make next bot move
        makeMove();
    }
}

void sample_game::BotController::makeMove() {
    auto* gameController = GET_SERVICE(GameController);
    auto* gameBoardProxy = GET_SERVICE(GameBoardProxy);

    unsigned int numAvailableMoveAttempts = s_maxMoveAttempts;
    while (numAvailableMoveAttempts > 0) {
        auto successMove = gameController->makeMove(_bot->calcNextMove(
            gameBoardProxy->getBoardState(), gameBoardProxy->getAvailableMoves()
        ));
        if (successMove)
            return;

        numAvailableMoveAttempts--;
    }

    // if we are here, the bot wasn't able to make a move, so we should disable it
    toggleBot();
}
