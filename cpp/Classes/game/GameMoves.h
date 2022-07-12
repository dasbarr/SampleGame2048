#ifndef SAMPLEGAME2048_GAMEMOVES_H
#define SAMPLEGAME2048_GAMEMOVES_H

namespace sample_game {
    /**
     * Possible in-game moves.
     */
    enum Move {
        INCORRECT_MOVE = 0, // auxiliary state, represents a move that cannot be performed
        UP = 1,
        DOWN = 2,
        LEFT = 3,
        RIGHT = 4
    };
}

#endif //SAMPLEGAME2048_GAMEMOVES_H
