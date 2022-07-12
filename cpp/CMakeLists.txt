#/****************************************************************************
# Copyright (c) 2013-2014 cocos2d-x.org
# Copyright (c) 2015-2017 Chukong Technologies Inc.
#
# http://www.cocos2d-x.org
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
# ****************************************************************************/

cmake_minimum_required(VERSION 3.6)

set(APP_NAME SampleGame2048)

project(${APP_NAME})

if(NOT DEFINED BUILD_ENGINE_DONE) # to test SampleGame2048 into root project
    set(COCOS2DX_ROOT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cocos2d)
    set(CMAKE_MODULE_PATH ${COCOS2DX_ROOT_PATH}/cmake/Modules/)

    include(CocosBuildSet)
    add_subdirectory(${COCOS2DX_ROOT_PATH}/cocos ${ENGINE_BINARY_PATH}/cocos/core)
endif()

# record sources, headers, resources...
set(GAME_SOURCE)
set(GAME_HEADER)

set(GAME_RES_FOLDER
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
    )
if(APPLE OR WINDOWS)
    cocos_mark_multi_resources(common_res_files RES_TO "Resources" FOLDERS ${GAME_RES_FOLDER})
endif()

# add cross-platforms source files and header files 
list(APPEND GAME_SOURCE
     Classes/AppDelegate.cpp
     )
list(APPEND GAME_HEADER
     Classes/AppDelegate.h
     )

list(APPEND GAME_HEADER
     proj.win32/main.h
     proj.win32/resource.h
     )
list(APPEND GAME_SOURCE
     proj.win32/main.cpp
     proj.win32/game.rc
     ${common_res_files}
     )

# mark app compile info and libs info
set(all_code_files
    ${GAME_HEADER}
        Classes/bots/BotController.h
        Classes/bots/IBot.h
        Classes/bots/PushTheTempoBot.h
        Classes/game/BoardTileMoveInfo.h
        Classes/game/GameBoardProxy.h
        Classes/game/GameConfig.h
        Classes/game/GameController.h
        Classes/game/GameMoves.h
        Classes/game/MainScene.h
        Classes/game/ScoreProxy.h
        Classes/input/InputManager.h
        Classes/localization/AutoTranslator.h
        Classes/localization/LanguageIds.h
        Classes/localization/Localization.h
        Classes/localization/LocalizationManager.h
        Classes/localization/LocalizedStringIds.h
        Classes/ui/BottomUI.h
        Classes/ui/EndGameWindow.h
        Classes/ui/GameUI.h
        Classes/ui/TopUI.h
        Classes/ui/components/AutoTranslatedUIButton.h
        Classes/ui/components/AutoTranslatedUIText.h
        Classes/utils/ButtonFactory.h
        Classes/utils/ServiceLocator.h
        Classes/utils/SimpleLogger.h
        Classes/view/GameBoardTile.h
        Classes/view/GameView.h
    ${GAME_SOURCE}
        Classes/bots/BotController.cpp
        Classes/bots/PushTheTempoBot.cpp
        Classes/game/GameBoardProxy.cpp
        Classes/game/GameConfig.cpp
        Classes/game/GameController.cpp
        Classes/game/MainScene.cpp
        Classes/game/ScoreProxy.cpp
        Classes/input/InputManager.cpp
        Classes/localization/AutoTranslator.cpp
        Classes/localization/Localization.cpp
        Classes/localization/LocalizationManager.cpp
        Classes/ui/BottomUI.cpp
        Classes/ui/EndGameWindow.cpp
        Classes/ui/GameUI.cpp
        Classes/ui/TopUI.cpp
        Classes/ui/components/AutoTranslatedUIButton.cpp
        Classes/ui/components/AutoTranslatedUIText.cpp
        Classes/utils/ButtonFactory.cpp
        Classes/utils/ServiceLocator.cpp
        Classes/utils/SimpleLogger.cpp
        Classes/view/GameBoardTile.cpp
        Classes/view/GameView.cpp)

set(jl_signal
        third_party/jl_signal/src/DoublyLinkedList.h
        third_party/jl_signal/src/FastDelegate.h
        third_party/jl_signal/src/ObjectPool.h third_party/jl_signal/src/ObjectPool.cpp
        third_party/jl_signal/src/ObjectPoolScopedAllocator.h
        third_party/jl_signal/src/ScopedAllocator.h
        third_party/jl_signal/src/Signal.h
        third_party/jl_signal/src/SignalBase.h third_party/jl_signal/src/SignalBase.cpp
        third_party/jl_signal/src/SignalDefinitions.h
        third_party/jl_signal/src/StaticSignalConnectionAllocators.h
        third_party/jl_signal/src/Utils.h)

add_executable(${APP_NAME} ${all_code_files} ${jl_signal})

target_link_libraries(${APP_NAME} cocos2d)
target_include_directories(${APP_NAME}
        PRIVATE Classes
        PRIVATE ${COCOS2DX_ROOT_PATH}/cocos/audio/include/
        PRIVATE third_party/jl_signal/src
        PRIVATE third_party/rapidjson/include/rapidjson
)

# mark app resources
setup_cocos_app_config(${APP_NAME})

cocos_copy_target_dll(${APP_NAME})

if(LINUX OR WINDOWS)
    cocos_get_resource_path(APP_RES_DIR ${APP_NAME})
    cocos_copy_target_res(${APP_NAME} LINK_TO ${APP_RES_DIR} FOLDERS ${GAME_RES_FOLDER})
endif()

set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${APP_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
