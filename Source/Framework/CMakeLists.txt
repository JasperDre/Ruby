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

set(SRC_DIR "${CMAKE_CURRENT_LIST_DIR}/")

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

add_library(Framework STATIC ${SRC})

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

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)