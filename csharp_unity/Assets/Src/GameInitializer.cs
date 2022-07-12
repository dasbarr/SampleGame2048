using sample_game.utils;
using DG.Tweening;
using UnityEngine;

namespace sample_game {
    
    /// <summary>
    /// Entry point, initializes the game.
    /// </summary>
    public static class GameInitializer {
        
        //-------------------------------------------------------------
        // Class constants
        //-------------------------------------------------------------
        
        private const int cTargetFrameRate = 60;
        
        //-------------------------------------------------------------
        // Class methods
        //-------------------------------------------------------------
        
        [RuntimeInitializeOnLoadMethod(RuntimeInitializeLoadType.AfterSceneLoad)]
        private static void OnApplicationLoaded() {
            Application.targetFrameRate = cTargetFrameRate;
            
            // make sure that all canvases will have proper size before game initialization
            Canvas.ForceUpdateCanvases();
            
            // init common services
            ServiceLocator.RegisterService(new LocalizationManager());
            ServiceLocator.RegisterService(GameObject.FindObjectOfType<InputManager>());
            
            // init game services
            ServiceLocator.RegisterService(new GameBoardProxy());
            ServiceLocator.RegisterService(new ScoreProxy());
            ServiceLocator.RegisterService(GameObject.FindObjectOfType<GameView>());
            
            var gameController = new GameController();
            ServiceLocator.RegisterService(gameController);
            
            // use simple bot
            ServiceLocator.RegisterService(BotController.Create<PushTheTempoBot>());
            
            // init DOTween
            DOTween.Init(false, true, LogBehaviour.ErrorsOnly);
            DOTween.defaultAutoPlay = AutoPlay.None;
            DOTween.defaultUpdateType = UpdateType.Normal;

            // start the game
            gameController.StartNewGame();
        }
    }
} // namespace sample_game