project (AppWarrior2)

option (BUILD_SHARED_LIBS "Build shared libraries" ON)
option (ENABLE_TESTS "Enable unit tests" ON)

add_subdirectory (include)
add_subdirectory (src)

if (ENABLE_TESTS)
	enable_testing()
	add_subdirectory (test)
endif()
