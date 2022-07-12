/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "AppDelegate.h"
#include "StaticSignalConnectionAllocators.h"
#include "game/MainScene.h"
#include "game/GameConfig.h"
#include "utils/ServiceLocator.h"
#include "localization/LocalizationManager.h"
#include "input/InputManager.h"

// init signal library allocators
enum { eMaxConnections = 50 };
jl::StaticSignalConnectionAllocator<eMaxConnections> g_oSignalConnectionAllocator;
jl::StaticObserverConnectionAllocator<eMaxConnections> g_oObserverConnectionAllocator;

USING_NS_CC;

void AppDelegate::initGLContextAttrs() {
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // init signal library allocators
    jl::SignalBase::SetCommonConnectionAllocator(&g_oSignalConnectionAllocator);
    jl::SignalObserver::SetCommonConnectionAllocator(&g_oObserverConnectionAllocator);

    // init common services
    sample_game::utils::ServiceLocator::registerService<sample_game::LocalizationManager>(
        sample_game::LocalizationManager::create()
    );
    sample_game::utils::ServiceLocator::registerService<sample_game::InputManager>(
        sample_game::InputManager::create()
    );

    // initialize director
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();
    if (!glView) {

        glView = GLViewImpl::createWithRect(
            "SampleGame2048",
            cocos2d::Rect(
                    0, 0,
                    sample_game::GameConfig::s_gameWindowWidth, sample_game::GameConfig::s_gameWindowHeight
                )
        );

        director->setOpenGLView(glView);
    }

    // set FPS
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glView->setDesignResolutionSize(
        sample_game::GameConfig::s_gameWindowWidth, sample_game::GameConfig::s_gameWindowHeight,
        ResolutionPolicy::NO_BORDER
    );

    // create a scene. it's an autorelease object
    auto scene = sample_game::MainScene::create();

    // run
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    // nothing to do
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    // nothing to do
}

void AppDelegate::cleanupBeforeExit() {
    // cleanup services
    sample_game::utils::ServiceLocator::clear();

    // flush log to disk
    sample_game::utils::SimpleLogger::flush();
}
