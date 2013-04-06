#Build Eclipse Project with cmake -G "Eclipse CDT4 - Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug
#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)
#Name your project here
project(TicTacToe)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/bin/bin/")

set( COCOS_ROOT /work/dev/game/cocos )
set( COCOS_SRC_ROOT /work/dev/game/cocos/cocos2dx )

set( COCOS_CONF Debug64 )
set( COCOS_LIBS cocos2d GLEW fmodex64 z cocosdenshion )

set( COCOS_LIBS_PATH ${COCOS_ROOT}/cocos2dx/proj.linux/${COCOS_CONF}
	${COCOS_ROOT}/CocosDenshion/proj.linux/${COCOS_CONF}
	${COCOS_ROOT}/CocosDenshion/third_party/fmod/lib64/api/lib
 )

link_directories ( ${COCOS_ROOT}/cocos2dx/proj.linux/${COCOS_CONF}
	${COCOS_ROOT}/CocosDenshion/proj.linux/${COCOS_CONF}
	${COCOS_ROOT}/CocosDenshion/third_party/fmod/lib64/api/lib
 )


add_definitions( -DLINUX ) #Needes by COCOS include files to select platform specific files
include_directories ( ${COCOS_SRC_ROOT}
			${COCOS_SRC_ROOT}/include
			${COCOS_SRC_ROOT}/platform/linux
			${COCOS_SRC_ROOT}/kazmath/include
			${COCOS_SRC_ROOT}/touch_dispatcher
			${COCOS_SRC_ROOT}/sprite_nodes
			${COCOS_SRC_ROOT}/draw_nodes
			${COCOS_SRC_ROOT}/cocoa
			/usr/include/c++/4.6
			/usr/include
)


set( SRC_FILES
    #Classes/TouchableSprite.cpp
	Classes/AppDelegate.cpp
	Classes/MonkeyRush.cpp
	main.cpp
 )

add_executable(TicTacToe ${SRC_FILES} )                      
target_link_libraries(TicTacToe ${COCOS_LIBS} )
