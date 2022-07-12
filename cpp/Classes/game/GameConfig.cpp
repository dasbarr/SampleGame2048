#include "GameConfig.h"

// Base // --------------------------------------------------

const float sample_game::GameConfig::s_gameWindowWidth = 800;
const float sample_game::GameConfig::s_gameWindowHeight = 600;
const sample_game::LanguageId sample_game::GameConfig::s_defaultLanguage = LanguageId::EN;

// UI // ----------------------------------------------------

const float sample_game::GameConfig::s_topUIHeight = 120;
const float sample_game::GameConfig::s_bottomUIHeight = 50;
const std::string sample_game::GameConfig::s_fontName = "Roboto-Regular.ttf";
const float sample_game::GameConfig::s_defaultFontSize = 16;

// View // --------------------------------------------------

const int sample_game::GameConfig::s_gameBoardTileIndent = 10;

// Game // --------------------------------------------------

const int sample_game::GameConfig::s_gameBoardSize = 4;
const float sample_game::GameConfig::s_gameTurnDelay = 0.4f;
const unsigned int sample_game::GameConfig::s_numInitialRandomTiles = 2;
const unsigned int sample_game::GameConfig::s_numRandomTilesEachTurn = 2;
const int sample_game::GameConfig::s_tileInitialValue = 1;
const unsigned int sample_game::GameConfig::s_numberOnWinTile = 2048;
