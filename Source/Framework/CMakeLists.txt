cmake_minimum_required(VERSION 3.7.0)

# Custom macro function to add project filters
macro(ADD_PROJECT_FILTERS path input_list prepend)
  foreach(_source IN ITEMS ${${input_list}})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${prepend}/${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
  endforeach()
endmacro()

set(IMGUI_DIR "${SUBMODULES_DIR}/imgui")
set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/")

file(GLOB IMGUI
  "${IMGUI_DIR}/imconfig.h"
  "${IMGUI_DIR}/imgui.h"
  "${IMGUI_DIR}/imgui_internal.h"
  "${IMGUI_DIR}/imstb_rectpack.h"
  "${IMGUI_DIR}/imstb_textedit.h"
  "${IMGUI_DIR}/imstb_truetype.h"
  "${IMGUI_DIR}/backends/imgui_impl_opengl3.h"
  "${IMGUI_DIR}/backends/imgui_impl_glfw.h"
  "${IMGUI_DIR}/imgui.cpp"
  "${IMGUI_DIR}/imgui_draw.cpp"
  "${IMGUI_DIR}/imgui_tables.cpp"
  "${IMGUI_DIR}/imgui_widgets.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp"
  "${IMGUI_DIR}/backends/imgui_impl_glfw.cpp"
)

file(GLOB_RECURSE SRC SRC_DIR
    "*.cpp"
    "*.h"
    "*.hpp")

# GLFW
add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
  IMPORTED_LOCATION "${DEPENDENCIES_DIR}/glfw/src/Debug/glfw3.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${SUBMODULES_DIR}/glfw/include"
)
target_compile_options(glfw INTERFACE "$<$<CXX_COMPILER_ID:MSVC>:/MP>")

# GLAD
add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
  IMPORTED_LOCATION "${DEPENDENCIES_DIR}/glad/Debug/glad.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/glad/include"
)
target_compile_options(glad INTERFACE "$<$<CXX_COMPILER_ID:MSVC>:/MP>")

add_library(Framework STATIC ${SRC} ${IMGUI})

source_group("imgui" FILES ${IMGUI})

target_include_directories(Framework PRIVATE "${CMAKE_CURRENT_LIST_DIR}/")

# GLFW
target_link_libraries(Framework glfw)

# GLAD
target_link_libraries(Framework glad)

# RapidJSON
target_include_directories(Framework PUBLIC "${SUBMODULES_DIR}/rapidjson/include")

# STB
target_include_directories(Framework PUBLIC "${SUBMODULES_DIR}/stb")

# TILESON
target_include_directories(Framework PUBLIC "${SUBMODULES_DIR}/tileson")

# IMGUI
target_include_directories(Framework PUBLIC "${IMGUI_DIR}")

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)