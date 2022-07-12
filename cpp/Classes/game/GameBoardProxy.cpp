#include "GameBoardProxy.h"
#include "game/GameConfig.h"

USING_NS_CC;

sample_game::GameBoardProxy* sample_game::GameBoardProxy::create() {
    auto* ret = new (std::nothrow) GameBoardProxy();
    if (ret) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

sample_game::GameBoardProxy::GameBoardProxy() {
    // init random source
    _randomSource.seed(std::random_device{}());

    // create game board
    for (int i = 0; i < GameConfig::s_gameBoardSize; i++) {
        _boardState.emplace_back(std::vector<int>(GameConfig::s_gameBoardSize));
    }
}

const std::vector<std::vector<int>>& sample_game::GameBoardProxy::getBoardState() const {
    return _boardState;
}

bool sample_game::GameBoardProxy::isWinTileAcquired() const {
    return _winTileAcquired;
}

const std::unordered_set<sample_game::Move>& sample_game::GameBoardProxy::getAvailableMoves() const {
    return _availableMoves;
}

bool sample_game::GameBoardProxy::hasAvailableMoves() const {
    return !_availableMoves.empty();
}

void sample_game::GameBoardProxy::reset() {
    // reset field to empty spaces
    for (auto& row : _boardState) {
        for (auto& tileValue : row) {
            tileValue = s_emptyTileValue;
        }
    }

    _winTileAcquired = false;

    // add initial tiles
    placeRandomTiles(GameConfig::s_numInitialRandomTiles);
}

void sample_game::GameBoardProxy::placeRandomTiles(unsigned int numTiles) {
    // find empty tiles
    std::vector<std::pair<unsigned int, unsigned int>> emptyTilesCoords;
    for (int i = 0; i < GameConfig::s_gameBoardSize; i++) {
        for (int j = 0; j < GameConfig::s_gameBoardSize; j++) {
            if (_boardState[i][j] == s_emptyTileValue)
                emptyTilesCoords.emplace_back(std::pair(i, j));
        }
    }

    std::shuffle(std::begin(emptyTilesCoords), std::end(emptyTilesCoords), _randomSource);
    auto numTilesToPlace = std::min(numTiles, emptyTilesCoords.size());
    for (auto i = 0U; i < numTilesToPlace; i++) {
        auto& tileCoords = emptyTilesCoords[i];
        _boardState[tileCoords.first][tileCoords.second] = GameConfig::s_tileInitialValue;
    }

    updateAvailableMoves();

    onBoardStateSet.Emit();
}

void sample_game::GameBoardProxy::updateAvailableMoves() {
    _availableMoves.clear();

    // move is available either if adjacent cell is empty or if it contains the same number as checked cell
    auto checkMoveAvailable = [&] (int destRow, int destColumn, int value) {
        auto destValue = _boardState[destRow][destColumn];
        return destValue == s_emptyTileValue || destValue == value;
    };

    for (auto i = 0; i < GameConfig::s_gameBoardSize; i++) {
        for (auto j = 0; j < GameConfig::s_gameBoardSize; j++) {
            auto currentCellValue = _boardState[i][j];

            if (currentCellValue == s_emptyTileValue)
                continue; // empty tile can't be moved

            // left
            if (j - 1 >= 0 && checkMoveAvailable(i, j - 1, currentCellValue))
                _availableMoves.insert(Move::LEFT);
            // right
            if (j + 1 < GameConfig::s_gameBoardSize && checkMoveAvailable(i, j + 1, currentCellValue))
                _availableMoves.insert(Move::RIGHT);
            // up
            if (i - 1 >= 0 && checkMoveAvailable(i - 1, j, currentCellValue))
                _availableMoves.insert(Move::UP);
            // down
            if (i + 1 < GameConfig::s_gameBoardSize && checkMoveAvailable(i + 1, j, currentCellValue))
                _availableMoves.insert(Move::DOWN);

            if (_availableMoves.size() == 4) {
                // all possible moves are available, it's not necessary to check further
                return;
            }
        }
    }
}

bool sample_game::GameBoardProxy::makeMove(Move move, OUT unsigned int& moveScore) {
    moveScore = 0;

    if (move == Move::INCORRECT_MOVE || _availableMoves.count(move) == 0)
        return false; // can't make a move

    // for each row/column tile movement will go from start to end index in the needed direction
    auto startIndex = move == Move::LEFT || move == Move::UP ? 0 : GameConfig::s_gameBoardSize - 1;
    auto endIndex = startIndex == 0 ? GameConfig::s_gameBoardSize - 1 : 0;
    auto delta = startIndex == 0 ? 1 : -1;

    auto isHorizontalMove = move == Move::LEFT || move == Move::RIGHT;
    auto getCellValue = [&isHorizontalMove, this](int outerIndex, int index) -> int {
        return isHorizontalMove
               ? _boardState[outerIndex][index]
               : _boardState[index][outerIndex];
    };
    auto setCellValue = [&isHorizontalMove, this](int outerIndex, int index, int value) {
        if (isHorizontalMove) {
            _boardState[outerIndex][index] = value;
        }
        else {
            _boardState[index][outerIndex] = value;
        }
    };
    auto packCellCoords = [&isHorizontalMove](int outerIndex, int index) -> std::pair<int, int> {
        return isHorizontalMove
               ? std::pair<int, int>(outerIndex, index)
               : std::pair<int, int>(index, outerIndex);
    };

    std::vector<BoardTileMoveInfo> boardTilesMoveData;

    // outer index corresponds to row index for horizontal moves and column index for vertical moves
    for (int outerIndex = 0; outerIndex < GameConfig::s_gameBoardSize; outerIndex++) {
        int currentIndex = startIndex;
        do {
            auto currentCellValue = getCellValue(outerIndex, currentIndex);

            // try to find non-empty value in some cell after the current cell
            bool nonEmptyValueFound = false;
            for (int checkIndex = currentIndex + delta; checkIndex != endIndex + delta; checkIndex += delta) {
                auto checkCellValue = getCellValue(outerIndex, checkIndex);
                if (checkCellValue != s_emptyTileValue) {
                    // non-empty value found
                    nonEmptyValueFound = true;

                    auto moved = false;
                    auto merged = false;
                    if (currentCellValue == s_emptyTileValue) {
                        // move value to the empty current cell
                        setCellValue(outerIndex, currentIndex, checkCellValue);

                        moved = true;
                    }
                    else if (currentCellValue == checkCellValue) {
                        // merge value with the non-empty current cell
                        auto mergedValue = currentCellValue + 1;
                        setCellValue(outerIndex, currentIndex, mergedValue);

                        auto scoreToAdd = 1U << mergedValue;
                        if (scoreToAdd >= GameConfig::s_numberOnWinTile)
                            _winTileAcquired = true;
                        moveScore += scoreToAdd;

                        merged = true;
                    }

                    if (moved || merged) {
                        // empty check cell
                        setCellValue(outerIndex, checkIndex, s_emptyTileValue);

                        // add info about tile movement
                        boardTilesMoveData.emplace_back(
                                packCellCoords(outerIndex, checkIndex),
                                packCellCoords(outerIndex, currentIndex)
                        );
                    }

                    // prevent double merges, but allow merge after move
                    if (!moved)
                        currentIndex += delta;
                    break;
                }
            }

            if (!nonEmptyValueFound) {
                // all cells after the current one are empty, it's not necessary to continue
                break;
            }
        } while (currentIndex != endIndex);
    }

    updateAvailableMoves();

    if (!boardTilesMoveData.empty())
        onTilesMoved.Emit(boardTilesMoveData);

    return true;
}
