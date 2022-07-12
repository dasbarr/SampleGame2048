namespace sample_game {
    
    /// <summary>
    /// Game config.
    /// </summary>
    public static class GameConfig {
     
        //-------------------------------------------------------------
        // Base
        //-------------------------------------------------------------

        /// <summary>
        /// Default language for localization.
        /// </summary>
        public const LanguageId cDefaultLanguageId = LanguageId.En;

        //-------------------------------------------------------------
        // Game
        //-------------------------------------------------------------

        /// <summary>
        /// Game board will contain that number of items horizontally and the same amount of items vertically.
        /// </summary>
        public const int cGameBoardSize = 4;

        /// <summary>
        /// Tile movement animation duration (in seconds).
        /// </summary>
        public const float cTileMovementDuration =0.6f;

        /// <summary>
        /// Number of random tiles that will be on the empty board at the start of the new game.
        /// </summary>
        public const int cNumInitialRandomTiles = 2;
        
        /// <summary>
        /// Number of random tiles that will be added to game board each turn (if possible).
        /// </summary>
        public const int cNumRandomTilesEachTurn = 2;

        /// <summary>
        /// Initial value for game tiles, represents a tile with number 2^{initial value}.
        /// </summary>
        public const int cTileInitialValue = 1;

        /// <summary>
        /// Game ends when player gets a tile with that number on it.
        /// </summary>
        public const uint cNumberOnWinTile = 2048;
    }
} // namespace sample_game