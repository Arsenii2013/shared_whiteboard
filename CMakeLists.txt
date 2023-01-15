cmake_minimum_required(VERSION 3.25)
project(shared_whiteboard)


find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(shared_whiteboard main.cpp image.hpp commands/command.hpp tool/tool.hpp commands/draw_circle.cpp commands/draw_circle.hpp toolbar.hpp tool/circle_maker.cpp tool/circle_maker.hpp utilities.hpp command_stack.hpp whiteboard.hpp service_commands/service_command.hpp service_commands/undo.cpp service_commands/undo.hpp tool/undo_maker.cpp tool/undo_maker.hpp commands/draw_rectangle.cpp commands/draw_rectangle.hpp tool/rectangle_maker.cpp tool/rectangle_maker.hpp commands/draw_image.cpp commands/draw_image.hpp tool/line_maker.cpp tool/line_maker.hpp commands/draw_poly_line.cpp commands/draw_poly_line.hpp tool/drawing_tool.hpp tool/service_tool.hpp tool/tool_tool.hpp service_commands/redo.cpp service_commands/redo.hpp tool/redo_maker.cpp tool/redo_maker.hpp commands/command_dto.hpp commands/command_name.hpp commands/command_dto_io.cpp tool_command/tool_command.hpp tool/tool_name.hpp tool/thickness_changer.cpp tool/thickness_changer.hpp tool_command/change_thickness.cpp tool_command/change_thickness.hpp tool_command/change_color.cpp tool_command/change_color.hpp tool/color_changer.cpp tool/color_changer.hpp toolbar_resource_loader.hpp)

target_link_libraries( shared_whiteboard ${OpenCV_LIBS} )
target_link_libraries(shared_whiteboard sfml-graphics sfml-audio)