#ifndef SAMPLEGAME2048_GAMEBOARDPROXY_H
#define SAMPLEGAME2048_GAMEBOARDPROXY_H

#include <vector>
#include <unordered_set>
#include <random>
#include "game/BoardTileMoveInfo.h"
#include "game/GameMoves.h"
#include "Signal.h"

namespace sample_game {
    /// <summary>
    /// Representation of the game board - square grid with cells that contain numbers.
    /// </summary>
    class GameBoardProxy : public cocos2d::Ref {
    public:
        static GameBoardProxy* create();

        /**
         * Value that represents an empty tile on the game board.
         */
        static const int s_emptyTileValue = -1;

        ~GameBoardProxy() = default;

        /**
         * Dispatched when the new state set for the whole board.
         */
        jl::Signal<void()> onBoardStateSet;
        /**
         * Dispatched when some tiles were moved. Contains info about that movements.
         */
        jl::Signal<void(const std::vector<BoardTileMoveInfo>&)> onTilesMoved;

        /**
         * Gets current board state.
         */
        const std::vector<std::vector<int>>& getBoardState() const;

        /**
         * Gets an information if win tile was acquired or not.
         */
        bool isWinTileAcquired() const;

        /**
         * Gets all available moves for current game board state.
         */
        const std::unordered_set<Move>& getAvailableMoves() const;

        /**
         * True if at least one move is available.
         */
        bool hasAvailableMoves() const;

        /**
         * Resets game board to initial state.
         */
        void reset();

        /**
         * Place random tiles with initial values if possible.
         * @param numTiles Number of tiles that will be placed.
         */
        void placeRandomTiles(unsigned int numTiles);

        /**
         * Makes a move (if that move is available).
         * @param move Move to make.
         * @param moveScore Out parameter, will contain score player earned by that move.
         * @return True if move was performed successfully, false otherwise.
         */
        bool makeMove(Move move, OUT unsigned int& moveScore);

    private:
        GameBoardProxy();

        /**
         * Finds all available moves at current game board state and updates 'available moves' list.
         * Move is available if there are two equal adjacent values (not zero) or if one of adjacent
         * values is non-zero and the second one is zero.
         * @private
         */
        void updateAvailableMoves();

        /**
         * Represents current board state. Contains 'power-of-2' values for corresponding tiles (for example,
         * it will contain 10 for tile number 2^10 = 1024). Note that -1 represents an empty tile. Also note that first
         * index is the index of the row, second index is the index of column. (0, 0) is the top left cell.
         * @private
         */
        std::vector<std::vector<int>> _boardState;

        /**
         * Contains all available moves for current game board state.
         * @private
         */
        std::unordered_set<Move> _availableMoves;

        /**
         * If true, win tile was acquired by player on one of previous moves.
         * @private
         */
        bool _winTileAcquired = false;

        std::default_random_engine _randomSource;
    };
}

#endif //SAMPLEGAME2048_GAMEBOARDPROXY_H
