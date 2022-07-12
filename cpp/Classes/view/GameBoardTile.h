#ifndef SAMPLEGAME2048_GAMEBOARDTILE_H
#define SAMPLEGAME2048_GAMEBOARDTILE_H

#include "cocos2d.h"
#include "2d/CCLayer.h"

namespace sample_game {
    /**
     * Represents one square item on the game board.
     */
    class GameBoardTile : public cocos2d::Sprite {
    public:
        static GameBoardTile* create(float tileSize);

        ~GameBoardTile() override;

        /**
         * Sets value (power-of-2) that represents number displayed on that tile (2^(tileValue) = number_to_show).
         * @param tileValue Tile value (power-of-2).
         */
        void setTileValue(int tileValue);

        /**
         * Marks current tile position as 'default position' for that tile.
         */
        void markCurrentPositionAsDefault();
        /**
         * Gets tile default position.
         * @return Tile default position.
         */
        const cocos2d::Vec2& getDefaultPosition() const;
        /**
         * Immediately moves tile to its default position.
         */
        void moveToDefaultPosition();

    CC_CONSTRUCTOR_ACCESS:
        bool initWithSize(float tileSize);

    private:
        GameBoardTile() = default;

        /**
         * Tile background.
         * @private
         */
        cocos2d::LayerColor* _background = nullptr;

        /**
         * Label for number on the tile.
         * @private
         */
        cocos2d::Label* _numberLabel = nullptr;

        /**
         * Tile default position.
         * @private
         */
        cocos2d::Vec2 _defaultPosition;
    };
}

#endif //SAMPLEGAME2048_GAMEBOARDTILE_H
