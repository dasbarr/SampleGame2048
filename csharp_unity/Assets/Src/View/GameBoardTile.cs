using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

namespace sample_game {

    /// <summary>
    /// Represents one square item on the game board.
    /// </summary>
    public class GameBoardTile : MonoBehaviour {

        //-------------------------------------------------------------
        // Nested
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Dependencies
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Class constants
        //-------------------------------------------------------------

        private static readonly Color cEmptyTileColor = Color.white;
        private static readonly List<Color> cTileColors = new List<Color> {
            new Color(0.933f, 0.894f, 0.855f), // 2^1  = 2
            new Color(0.929f, 0.878f, 0.784f), // 2^2  = 4
            new Color(0.949f, 0.694f, 0.475f), // 2^3  = 8
            new Color(0.961f, 0.584f, 0.388f), // 2^4  = 16
            new Color(0.965f, 0.486f, 0.373f), // 2^5  = 32
            new Color(0.965f, 0.369f, 0.231f), // 2^6  = 64
            new Color(0.929f, 0.812f, 0.447f), // 2^7  = 128
            new Color(0.929f, 0.800f, 0.380f), // 2^8  = 256
            new Color(0.929f, 0.784f, 0.314f), // 2^9  = 512
            new Color(0.929f, 0.773f, 0.247f), // 2^10 = 1024
            new Color(0.929f, 0.761f, 0.180f)  // 2^11 = 2048
        };
        
        private static readonly Color cSmallNumberLabelColor = new Color(0.467f, 0.431f, 0.396f); // for 2^1 a 2^2 tiles
        private static readonly Color cLargeNumberLabelColor = new Color(0.973f, 0.957f, 0.945f); // for all other tiles

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

        public RectTransform rectTransform { get; private set; }

        /// <summary>
        /// Value (power-of-2) that represents number displayed on that tile (2^(tileValue) = number_to_show).
        /// </summary>
        public int numberValue {
            set {
                // set proper color for tile background and number label
                if (value >= 1) {
                    _backgroundImage.color = value <= cTileColors.Count
                        ? cTileColors[value - 1]
                        : cTileColors[cTileColors.Count - 1]; // use max possible color

                    _tileNumberLabel.gameObject.SetActive(true);
                    _tileNumberLabel.color = value <= 2
                        ? cSmallNumberLabelColor
                        : cLargeNumberLabelColor;
                    _tileNumberLabel.text = (1 << value).ToString();
                }
                else {
                    // empty tile
                    _backgroundImage.color = cEmptyTileColor;
                    _tileNumberLabel.gameObject.SetActive(false);
                }
            }
        }

        //-------------------------------------------------------------
        // Private properties serialized for Unity
        //-------------------------------------------------------------

        /// <summary>
        /// Label that contains a number displayed on the current tile.
        /// </summary>
        [SerializeField]
        private Text _tileNumberLabel = default;

        /// <summary>
        /// Tile background.
        /// </summary>
        [SerializeField]
        private Image _backgroundImage = default;
        
        //-------------------------------------------------------------
        // Public methods
        //-------------------------------------------------------------

        //-------------------------------------------------------------
        // Protected methods
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Private methods
        //-------------------------------------------------------------
        
        //-------------------------------------------------------------
        // Unity methods
        //-------------------------------------------------------------

        private void Awake() {
            rectTransform = transform as RectTransform;
        }

        //-------------------------------------------------------------
        // Handlers
        //-------------------------------------------------------------
    }
} // namespace sample_game