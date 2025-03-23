set (AW_SOURCES
	3rdparty/md5.c
	ANSI.c
	GrafTypes.cpp
	UApplication.cpp
	UDateTime.cpp
	UDigest.cpp
	UError.cpp
	UFileSys.cpp
	UGraphics.cpp
	UMath.cpp
	UMemory.cpp
	UMessageSys.cpp
	UMouse.cpp
	UNetwork.cpp
	UOperatingSystem.cpp
	USound.cpp
	UTimer.cpp
	UUserInterface.cpp
)

add_library (AppWarrior2 ${AW_SOURCES})
target_include_directories (AppWarrior2 PUBLIC ${PROJECT_SOURCE_DIR}/include)
set_target_properties (AppWarrior2 PROPERTIES VERSION 2.0 SOVERSION 2)
