set(CMAKE_CXX_FLAGS_RELEASE "/MT")
set(CMAKE_CXX_FLAGS_DEBUG "/MTd")
find_package(GTest)

if (GTest_FOUND)
	enable_testing()

	add_executable(test_maths
		vec2_test.cpp
		matrix_test.cpp
	)

	target_include_directories(test_maths PUBLIC ${GTEST_INCLUDE_DIR})
	target_include_directories(test_maths PUBLIC "${PROJECT_SOURCE_DIR}/include")

	target_link_libraries(test_maths
		${GTEST_LIBRARY_DEBUG}
		${GTEST_MAIN_LIBRARY_DEBUG})

	add_test(test_maths test_maths)
endif()