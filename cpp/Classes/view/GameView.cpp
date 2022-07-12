#include "GameView.h"
#include "game/GameConfig.h"
#include "utils/ServiceLocator.h"
#include "game/GameController.h"

USING_NS_CC;

sample_game::GameView::~GameView() {
    discardTileMoveActions();
}

bool sample_game::GameView::init() {
    if (!Node::init())
        return false;

    // board view will be in between of top and bottom UI lines
    float boardViewHeight = GameConfig::s_gameWindowHeight - GameConfig::s_topUIHeight - GameConfig::s_bottomUIHeight;
    setContentSize(Size(boardViewHeight, boardViewHeight));

    float boardTileSize = (boardViewHeight - (GameConfig::s_gameBoardSize + 1) * GameConfig::s_gameBoardTileIndent) /
            GameConfig::s_gameBoardSize;

    auto* background = DrawNode::create();
    addChild(background);
    Color4F backgroundColor(0.35f, 0.35f, 0.35f, 1.0f);

    // create board tiles
    Vec2 tilePosition;
    for (int i = 0; i < GameConfig::s_gameBoardSize; i++) {
        auto& currentRow = _boardTiles.emplace_back(Vector<GameBoardTile*>());

        for (int j = 0; j < GameConfig::s_gameBoardSize; j++) {
            // create tile
            auto* tile = GameBoardTile::create(boardTileSize);

            tilePosition.x = GameConfig::s_gameBoardTileIndent * (j + 1) + boardTileSize * j;
            tilePosition.y = boardViewHeight - GameConfig::s_gameBoardTileIndent * (i + 1) - boardTileSize * i;

            tile->setPosition(tilePosition);
            tile->setAnchorPoint(Vec2(0,1));

            // mark that position as 'default position' for that tile
            tile->markCurrentPositionAsDefault();

            currentRow.pushBack(tile);
            addChild(tile);

            // draw tile background under the tile
            background->drawSolidRect(
                tilePosition,
                Vec2(tilePosition.x + boardTileSize, tilePosition.y - boardTileSize),
                backgroundColor
            );
        }
    }

    // subscribe to board changes
    auto* gameBoardProxy = GET_SERVICE(GameBoardProxy);
    gameBoardProxy->onBoardStateSet.Connect(this, &GameView::showActualBoardState);
    gameBoardProxy->onTilesMoved.Connect(this, &GameView::boardTilesMovedHandler);

    showActualBoardState();

    return true;
}

void sample_game::GameView::boardTilesMovedHandler(const std::vector<BoardTileMoveInfo>& boardTilesMoveData) {
    discardTileMoveActions();

    if (!boardTilesMoveData.empty()) {
        // Move duration should be a bit less than turn delay to ensure that move animation finishes
        // before the next turn.
        static auto moveAnimationDuration = GameConfig::s_gameTurnDelay - 0.05f;

        Vector<FiniteTimeAction*> moveActions;

        // move tiles with animation
        for (auto& moveInfo : boardTilesMoveData) {
            auto* tileToMove = _boardTiles[moveInfo.tileStartCoords.first].at(moveInfo.tileStartCoords.second);
            // tile should be above non-moving tiles
            tileToMove->setLocalZOrder(1);
            // tile will move to the destinationTile position
            auto* destinationTile = _boardTiles[moveInfo.tileEndCoords.first].at(moveInfo.tileEndCoords.second);

            auto* tileMoveAction = MoveTo::create(moveAnimationDuration, destinationTile->getDefaultPosition());
            auto* easeAction = EaseSineIn::create(tileMoveAction);
            tileToMove->runAction(easeAction);
        }

        // make movement end callback sequence
        _tileMoveCallbackSequence = Sequence::createWithTwoActions(
            DelayTime::create(moveAnimationDuration),
            CallFunc::create(CC_CALLBACK_0(GameView::tilesMovementAnimationEndHandler, this))
        );
        _tileMoveCallbackSequence->retain();
        runAction(_tileMoveCallbackSequence);
    }
}

void sample_game::GameView::discardTileMoveActions() {
    if (_tileMoveCallbackSequence == nullptr)
        return; // nothing to discard

    stopAction(_tileMoveCallbackSequence);
    CC_SAFE_RELEASE_NULL(_tileMoveCallbackSequence);

    // stop tile animation actions, move all tiles to default positions
    for (int i = 0; i < GameConfig::s_gameBoardSize; i++) {
        for (int j = 0; j < GameConfig::s_gameBoardSize; j++) {
            auto* tile = _boardTiles[i].at(j);

            tile->stopAllActions();
            tile->moveToDefaultPosition();
            tile->setLocalZOrder(0);
        }
    }
}

void sample_game::GameView::showActualBoardState() {
    discardTileMoveActions();

    auto& currentBoardState = GET_SERVICE(GameBoardProxy)->getBoardState();
    for (int i = 0; i < GameConfig::s_gameBoardSize; i++) {
        for (int j = 0; j < GameConfig::s_gameBoardSize; j++) {
            _boardTiles[i].at(j)->setTileValue(currentBoardState[i][j]);
        }
    }
}

void sample_game::GameView::tilesMovementAnimationEndHandler() {
    showActualBoardState();

    onTileMovementAnimationEnded.Emit();
}
