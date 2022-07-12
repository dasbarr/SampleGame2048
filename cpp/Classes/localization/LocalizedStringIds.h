#ifndef SAMPLEGAME2048_LOCALIZEDSTRINGIDS_H
#define SAMPLEGAME2048_LOCALIZEDSTRINGIDS_H

namespace sample_game {
    /**
     * Ids for localization string used in game.
     */
    enum LocalizedStringId : int {
        EMPTY_LOCALE = 0, // if of a special locale that contains an empty string

        LANGUAGE_NAME = 1,

        // top ui
        GAME_DESCRIPTION = 2,
        NEW_GAME = 3,
        CURRENT_SCORE_TITLE = 4,
        BEST_SCORE_TITLE = 5,

        // bottom ui
        LANGUAGE = 6,
        START_BOT = 7,
        STOP_BOT = 8,
        BOT_ENABLED = 9,

        // end game window
        END_GAME_WINDOW_WIN = 10,
        END_GAME_WINDOW_LOSE = 11,
        END_GAME_WINDOW_SCORE = 12,
        END_GAME_WINDOW_NEW_RECORD = 13,
        END_GAME_WINDOW_PLAY_AGAIN = 14
    };
}

#endif //SAMPLEGAME2048_LOCALIZEDSTRINGIDS_H
