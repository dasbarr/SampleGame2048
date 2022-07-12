using System.Collections.Generic;
using System.Linq;
using sample_game.utils;

namespace sample_game {
    
    /// <summary>
    /// Simple bot that makes random available moves.
    /// </summary>
    public class PushTheTempoBot : IBot {
        
        //-------------------------------------------------------------
        // Nested
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Dependencies
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Class constants
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Class variables
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Class methods
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Constructor/destructor
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Variables
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Events
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Properties
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Private properties serialized for Unity
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Public methods
        //-------------------------------------------------------------

        public Move CalcNextMove(List<List<int>> gameBoardState, HashSet<Move> availableMoves) {
            return availableMoves.Count > 0
                ? availableMoves.Shuffle().First()
                : Move.IncorrectMove;
        }
        
        //-------------------------------------------------------------
        // Protected methods
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Private methods
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Unity methods
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Handlers
        //-------------------------------------------------------------
    }
} // namespace sample_game