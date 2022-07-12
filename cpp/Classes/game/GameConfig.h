#ifndef SAMPLEGAME2048_GAMECONFIG_H
#define SAMPLEGAME2048_GAMECONFIG_H

#include "cocos2d.h"
#include "localization/LanguageIds.h"

namespace sample_game {
    /**
     * Game config.
     */
    class GameConfig {
    public:
        GameConfig() = delete;

        // Base // --------------------------------------------------

        // Size of the game window.
        static const float s_gameWindowWidth;
        static const float s_gameWindowHeight;

        /**
         * Default language for localization.
         */
        static const LanguageId s_defaultLanguage;

        // UI // ----------------------------------------------------

        /**
         * Height of the top UI line.
         */
        static const float s_topUIHeight;
        /**
         * Height of the bottom UI line.
         */
        static const float s_bottomUIHeight;

        /**
         * Name of the UI font.
         */
        static const std::string s_fontName;

        /**
         * Default UI font size.
         */
        static const float s_defaultFontSize;

        // View // --------------------------------------------------

        /**
         * Indents between game board tiles and between game view and UI lines.
         */
        static const int s_gameBoardTileIndent;

        // Game // --------------------------------------------------

        /**
         * Game board will contain that number of items horizontally and the same amount of items vertically.
         */
        static const int s_gameBoardSize;

        /**
         * Delay between game turns (in seconds).
         */
        static const float s_gameTurnDelay;

        /**
         * Number of random tiles that will be on the empty board at the start of the new game.
         */
        static const unsigned int s_numInitialRandomTiles;

        /**
         * Number of random tiles that will be added to game board each turn (if possible).
         */
        static const unsigned int s_numRandomTilesEachTurn;

        /**
         * Initial value for game tiles, represents tile number 2^1 = 2.
         */
        static const int s_tileInitialValue;

        /**
         * Game ends when player gets a tile with that number on it.
         */
        static const unsigned int s_numberOnWinTile;
    };
}

#endif //SAMPLEGAME2048_GAMECONFIG_H
