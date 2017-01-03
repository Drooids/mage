# Handle source files first.
set(Mage_SOURCES
	"win32_mage.cpp")

set(Mage_ENGINE_SOURCES
	"engine/ogl_canvas.cpp"
	"engine/ogl_program.cpp"
	"engine/ogl_shader_controller.cpp"
	"engine/ogl_texture.cpp"
	"engine/ogl_vertex_array.cpp")

set(Mage_ENGINE_TEXT_SOURCES
	"engine/text/ogl_font.cpp"
	"engine/text/text_engine.cpp")

set(Mage_WIN32_ENGINE_SOURCES
	"engine/win32_engine_context.cpp"
	"engine/win32_engine_system.cpp")

set(Mage_UI_SOURCES
	"ui/ui_frame.cpp"
	"ui/ui_layer.cpp")

set(Mage_OS_SOURCES
	"os/win32_window.cpp")

# Handle the include files.
set(Mage_HEADERS
	"${Mage_INCLUDE_PATH}/exception.hpp"
	"${Mage_INCLUDE_PATH}/noncopyable.hpp"
	"${Mage_INCLUDE_PATH}/string_util.hpp")

set(Mage_ENGINE_HEADERS
	"${Mage_INCLUDE_PATH}/engine/buffer.hpp"
	"${Mage_INCLUDE_PATH}/engine/exception.hpp"
	"${Mage_INCLUDE_PATH}/engine/graph.hpp"
	"${Mage_INCLUDE_PATH}/engine/object.hpp"
	"${Mage_INCLUDE_PATH}/engine/render_canvas.hpp"
	"${Mage_INCLUDE_PATH}/engine/render_system.hpp"
	"${Mage_INCLUDE_PATH}/engine/scene_graph.hpp"
	"${Mage_INCLUDE_PATH}/engine/shader.hpp"
	"${Mage_INCLUDE_PATH}/engine/texture.hpp"
	"${Mage_INCLUDE_PATH}/engine/vertex_array.hpp")

set(Mage_ENGINE_TEXT_HEADERS
	"${Mage_INCLUDE_PATH}/engine/text/exception.hpp"
	"${Mage_INCLUDE_PATH}/engine/text/engine.hpp"
	"${Mage_INCLUDE_PATH}/engine/text/font.hpp")

set(Mage_MATH_HEADERS
	"${Mage_INCLUDE_PATH}/math/matrix.hpp"
	"${Mage_INCLUDE_PATH}/math/vector2.hpp")

set(Mage_UI_HEADERS
	"${Mage_INCLUDE_PATH}/ui/element.hpp"
	"${Mage_INCLUDE_PATH}/ui/frame.hpp"
	"${Mage_INCLUDE_PATH}/ui/layer.hpp")

set(Mage_WIN32_ENGINE_HEADERS
	"${Mage_INCLUDE_PATH}/engine/win32/render_context.hpp"
	"${Mage_INCLUDE_PATH}/engine/win32/render_system.hpp")

set(Mage_OS_HEADERS
	"${Mage_INCLUDE_PATH}/os/win32_window.hpp"
	"${Mage_INCLUDE_PATH}/os/win32_exception.hpp"
	"${Mage_INCLUDE_PATH}/os/window.hpp")

# Create MSVC groups.
source_group("Sources" FILES ${Mage_SOURCES})
source_group("Sources\\engine" FILES ${Mage_ENGINE_SOURCES})
source_group("Sources\\engine\\text" FILES ${Mage_ENGINE_TEXT_SOURCES})
source_group("Sources\\engine\\win32" FILES ${Mage_WIN32_ENGINE_SOURCES})
source_group("Sources\\ui" FILES ${Mage_UI_SOURCES})
source_group("Sources\\os" FILES ${Mage_OS_SOURCES})

source_group("Include" FILES ${Mage_HEADERS})
source_group("Include\\engine" FILES ${Mage_ENGINE_HEADERS})
source_group("Include\\engine\\text" FILES ${Mage_ENGINE_TEXT_HEADERS})
source_group("Include\\engine\\win32" FILES  ${Mage_WIN32_ENGINE_HEADERS})
source_group("Include\\math" FILES ${Mage_MATH_HEADERS})
source_group("Include\\ui" FILES ${Mage_UI_HEADERS})
source_group("Include\\os" FILES ${Mage_OS_HEADERS})

add_executable(Engine WIN32
	${Mage_SOURCES}
	${Mage_ENGINE_SOURCES}
	${Mage_ENGINE_TEXT_SOURCES} 
	${Mage_WIN32_ENGINE_SOURCES}
	${Mage_UI_SOURCES}
	${Mage_OS_SOURCES}
	${Mage_HEADERS}
	${Mage_ENGINE_HEADERS}
	${Mage_ENGINE_TEXT_HEADERS}
	${Mage_MATH_HEADERS}
	${Mage_UI_HEADERS}
	${Mage_WIN32_ENGINE_HEADERS}
	${Mage_OS_HEADERS})

find_package(OpenMP)
if (OpenMP_FOUND)
	set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

find_package(GLEW REQUIRED)
if (GLEW_FOUND)
	target_include_directories(Engine PUBLIC ${GLEW_INCLUDE_DIRS})
	target_link_libraries(Engine ${GLEW_LIBRARIES})
	target_compile_definitions(Engine PRIVATE GLEW_STATIC)
endif()

find_package(OpenGL REQUIRED)
if (OpenGL_FOUND) 
	target_include_directories(Engine PUBLIC ${OPENGL_INCLUDE_DIRS})
	target_link_libraries(Engine ${OPENGL_LIBRARIES})
endif()

set(Boost_USE_STATIC_LIBS   ON)
set(Boost_USE_MULTITHREADED ON)
find_package(Boost REQUIRED COMPONENTS filesystem system)
if (Boost_FOUND)
	target_include_directories(Engine PUBLIC ${Boost_INCLUDE_DIRS})
	target_link_libraries(Engine ${Boost_LIBRARIES})
endif()

find_package(Freetype REQUIRED)
if (Freetype_FOUND)
	target_include_directories(Engine PUBLIC ${FREETYPE_INCLUDE_DIRS})
	target_link_libraries(Engine ${FREETYPE_LIBRARIES})
endif()

find_package(Lua51 REQUIRED)
if (Lua_FOUND)
	target_include_directories(Engine PUBLIC ${LUA_INCLUDE_DIR})
	target_link_libraries(Engine ${LUA_LIBRARY})
endif()

target_include_directories(Engine
	PUBLIC "${PROJECT_SOURCE_DIR}/include"
	PUBLIC "${PROJECT_BINARY_DIR}/include"
)
