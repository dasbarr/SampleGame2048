#ifndef SAMPLEGAME2048_GAMEVIEW_H
#define SAMPLEGAME2048_GAMEVIEW_H

#include <vector>
#include "cocos2d.h"
#include "base/CCVector.h"
#include "Signal.h"
#include "view/GameBoardTile.h"
#include "game/BoardTileMoveInfo.h"

namespace sample_game {
    /**
     * Game board visual representation.
     */
    class GameView : public cocos2d::Node, public jl::SignalObserver {
    public:
        CREATE_FUNC(GameView);

        ~GameView() override;

        jl::Signal<void()> onTileMovementAnimationEnded;

    CC_CONSTRUCTOR_ACCESS:
        bool init() override;

    private:
        GameView() = default;

        /**
         * Handles animated tile movement.
         * @param boardTilesMoveData Data about tile movement.
         * @private
         */
        void boardTilesMovedHandler(const std::vector<BoardTileMoveInfo>& boardTilesMoveData);

        /**
         * Discards tile movement actions (if possible).
         * @private
         */
        void discardTileMoveActions();
        /**
         * Shows actual state of the game board.
         * @private
         */
        void showActualBoardState();

        /**
         * Actions on the end of tiles movement animation.
         * @private
         */
        void tilesMovementAnimationEndHandler();

        /**
         * 2D array, contains game board tiles.
         * @private
         */
        std::vector<cocos2d::Vector<GameBoardTile*>> _boardTiles;

        /**
         * Cocos2dx Sequence for tile movement callback.
         * @private
         */
        cocos2d::Sequence* _tileMoveCallbackSequence = nullptr;
    };
}

#endif //SAMPLEGAME2048_GAMEVIEW_H
