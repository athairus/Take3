add_executable(gameboy-test "")
target_include_directories(gameboy-test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(gameboy-test PRIVATE
	main.cpp
)
set_target_properties(gameboy-test PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED 14)

target_link_libraries(gameboy-test gameboy)

set_target_properties(gameboy-test PROPERTIES AUTOMOC ON AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Core)
target_link_libraries(gameboy-test Qt5::Core)
