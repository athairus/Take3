add_library(gameboy STATIC "")
target_include_directories(gameboy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(gameboy PRIVATE
	gameboy.cpp
)
set_target_properties(gameboy PROPERTIES CXX_STANDARD 14 CXX_STANDARD_REQUIRED 14)

set_target_properties(gameboy PROPERTIES AUTOMOC ON AUTORCC ON)
find_package(Qt5 REQUIRED COMPONENTS Core)
target_link_libraries(gameboy Qt5::Core)
