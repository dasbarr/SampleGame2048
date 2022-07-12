#ifndef SAMPLEGAME2048_BOARDTILEMOVEINFO_H
#define SAMPLEGAME2048_BOARDTILEMOVEINFO_H

#include "cocos2d.h"

namespace sample_game {
    /**
     * Contains info about board tile movement.
     */
    struct BoardTileMoveInfo {
        /**
         * Tile with that coords was moved.
         */
        std::pair<int, int> tileStartCoords;
        /**
         * Tile was moved to that coords.
         */
        std::pair<int, int> tileEndCoords;

        BoardTileMoveInfo(std::pair<int, int> tileCoords_, std::pair<int, int> tileDestinationCoords_)
                : tileStartCoords(std::move(tileCoords_))
                , tileEndCoords(std::move(tileDestinationCoords_))
        {}
    };
}

#endif //SAMPLEGAME2048_BOARDTILEMOVEINFO_H
