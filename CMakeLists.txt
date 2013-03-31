#Specify the version being used aswell as the language
cmake_minimum_required(VERSION 2.6)
#Name your project here
project(TicTacToe)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin/bin/bin/")

set( COCOS_ROOT /work/dev/game/cocos )
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
include_directories ( ${COCOS_ROOT}/cocos2dx
			${COCOS_ROOT}/cocos2dx/include
			${COCOS_ROOT}/cocos2dx/platform/linux
			${COCOS_ROOT}/cocos2dx/kazmath/include
			/usr/include/linux
			/usr/include/c++/4.6
		#	/usr/include/c++/4.6/x86_64-linux-gnu
)


set( SRC_FILES 
	Classes/AppDelegate.cpp
	Classes/MonkeyRush.cpp
	main.cpp
 )

add_executable(TicTacToe ${SRC_FILES} )                      
target_link_libraries(TicTacToe ${COCOS_LIBS} )
