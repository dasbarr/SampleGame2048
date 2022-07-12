#include "GameBoardTile.h"
#include <vector>
#include <string>
#include "game/GameConfig.h"

USING_NS_CC;

sample_game::GameBoardTile* sample_game::GameBoardTile::create(float tileSize) {
    auto* ret = new (std::nothrow) GameBoardTile();
    if (ret && ret->initWithSize(tileSize)) {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

sample_game::GameBoardTile::~GameBoardTile() {
    CC_SAFE_RELEASE_NULL(_background);
    CC_SAFE_RELEASE_NULL(_numberLabel);
}

bool sample_game::GameBoardTile::initWithSize(float tileSize) {
    if (!init())
        return false;

    setContentSize(Size(tileSize, tileSize));

    _background = LayerColor::create(Color4B(0,0,0,255), tileSize, tileSize);
    _background->retain();
    _background->setAnchorPoint(Vec2(0, 0));
    addChild(_background);

    _numberLabel = Label::createWithSystemFont("", GameConfig::s_fontName, 32);
    _numberLabel->retain();
    _numberLabel->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
    _numberLabel->setAnchorPoint(Vec2(0.5, 0.5));
    _numberLabel->setOverflow(Label::Overflow::SHRINK);
    _numberLabel->setDimensions(tileSize, tileSize);
    _numberLabel->setPosition(tileSize * 0.5f, tileSize * 0.5f);
    addChild(_numberLabel);

    setCascadeOpacityEnabled(true);

    return true;
}

void sample_game::GameBoardTile::setTileValue(int tileValue) {
    static std::vector<Color3B> tileColors({
        Color3B(238, 228, 218), // 2^1  = 2
        Color3B(237, 224, 200), // 2^2  = 4
        Color3B(242, 177, 121), // 2^3  = 8
        Color3B(245, 149, 99),  // 2^4  = 16
        Color3B(246, 124, 95),  // 2^5  = 32
        Color3B(246, 94,  59),  // 2^6  = 64
        Color3B(237, 207, 114), // 2^7  = 128
        Color3B(237, 204, 97),  // 2^8  = 256
        Color3B(237, 200, 80),  // 2^9  = 512
        Color3B(237, 197, 63),  // 2^10 = 1024
        Color3B(237, 194, 46),  // 2^11 = 2048
    });

    static Color3B smallNumberLabelColor(119, 110, 101); // for 2^1 a 2^2 tiles
    static Color3B largeNumberLabelColor(248, 244, 241); // for all other tiles

    // set proper color for tile background and number label
    uint8_t tileOpacity = 0;
    if (tileValue >= 1) {
        tileOpacity = 255;

        auto& tileColor = tileValue <= static_cast<int>(tileColors.size())
            ? tileColors[tileValue - 1]
            : tileColors[tileColors.size() - 1]; // use max possible color
        _background->setColor(tileColor);

        auto& numberLabelColor = tileValue <= 2
            ? smallNumberLabelColor
            : largeNumberLabelColor;
        _numberLabel->setColor(numberLabelColor);

        _numberLabel->setString(std::to_string(1 << tileValue));
    }
    setOpacity(tileOpacity);
}

void sample_game::GameBoardTile::markCurrentPositionAsDefault() {
    _defaultPosition = getPosition();
}

const cocos2d::Vec2& sample_game::GameBoardTile::getDefaultPosition() const {
    return _defaultPosition;
}

void sample_game::GameBoardTile::moveToDefaultPosition() {
    setPosition(_defaultPosition);
}
