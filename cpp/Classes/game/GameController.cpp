#include "GameController.h"
#include <random>
#include "input/InputManager.h"
#include "utils/ServiceLocator.h"
#include "game/GameConfig.h"
#include "game/ScoreProxy.h"
#include "view/GameView.h"

USING_NS_CC;

sample_game::GameController* sample_game::GameController::create() {
    auto* ret = new (std::nothrow) GameController();
    if (ret) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

sample_game::GameController::GameController() {
    // subscribe for user input
    GET_SERVICE(InputManager)->onPlayerInput.Connect(this, &GameController::userInputHandler);

    // subscribe for turn end
    GET_SERVICE(GameView)->onTileMovementAnimationEnded.Connect(this, &GameController::endCurrentTurn);
}

sample_game::GameController::GameState sample_game::GameController::getCurrentGameState() const {
    return _currentGameState;
}

void sample_game::GameController::startNewGame() {
    setGameState(GameState::NEW_GAME_PREPARATION);

    GET_SERVICE(GameBoardProxy)->reset();
    GET_SERVICE(ScoreProxy)->clearCurrentScore();

    setGameState(GameState::WAITING_FOR_INPUT);
}

bool sample_game::GameController::makeMove(Move move) {
    if (_currentGameState == GameState::WAITING_FOR_INPUT) {
        // make a move
        unsigned int moveScore;
        auto moveSuccess = GET_SERVICE(GameBoardProxy)->makeMove(move, moveScore);
        if (moveSuccess) {
            setGameState(GameState::GAME_TURN_IN_PROGRESS);

            // update score
            GET_SERVICE(ScoreProxy)->addScore(moveScore);
            return true;
        }
    }

    return false;
}

void sample_game::GameController::setGameState(GameState newGameState) {
    if (_currentGameState == newGameState)
        return; // nothing changed

    _currentGameState = newGameState;
    onGameStateChanged.Emit(newGameState);
}

void sample_game::GameController::endCurrentTurn() {
    auto* gameBoardProxy = GET_SERVICE(GameBoardProxy);

    if (gameBoardProxy->isWinTileAcquired()) {
        setGameState(GameState::GAME_ENDED);
    }
    else {
        // place new tiles before new turn
        gameBoardProxy->placeRandomTiles(GameConfig::s_numRandomTilesEachTurn);
        if (gameBoardProxy->hasAvailableMoves()) {
            // start new turn
            setGameState(GameState::WAITING_FOR_INPUT);
        }
        else {
            // no more moves on the game field
            setGameState(GameState::GAME_ENDED);
        }
    }
}

void sample_game::GameController::userInputHandler(const EventKeyboard::KeyCode userInput) {
    if (_currentGameState != GameState::WAITING_FOR_INPUT)
        return;

    Move currentPlayerMove;
    switch (userInput) {
        case EventKeyboard::KeyCode::KEY_W:
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            currentPlayerMove = Move::UP;
            break;
        case EventKeyboard::KeyCode::KEY_A:
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            currentPlayerMove = Move::LEFT;
            break;
        case EventKeyboard::KeyCode::KEY_S:
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            currentPlayerMove = Move::DOWN;
            break;
        case EventKeyboard::KeyCode::KEY_D:
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            currentPlayerMove = Move::RIGHT;
            break;
        default:
            currentPlayerMove = Move::INCORRECT_MOVE;
            break;
    }

    makeMove(currentPlayerMove);
}
