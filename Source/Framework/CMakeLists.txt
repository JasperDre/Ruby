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

# Custom macro function to add PCH
macro(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource)
  if(MSVC)
  get_filename_component(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    set(PrecompiledBinary "${CMAKE_CURRENT_BINARY_DIR}/${PrecompiledBasename}.pch")
    set_source_files_properties(${PrecompiledSource}
                                PROPERTIES COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_OUTPUTS "${PrecompiledBinary}")
    set_source_files_properties(${Sources}
                                PROPERTIES COMPILE_FLAGS "/Yu\"${PrecompiledHeader}\" /FI\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\""
                                           OBJECT_DEPENDS "${PrecompiledBinary}")
  endif(MSVC)
endmacro(ADD_MSVC_PRECOMPILED_HEADER)

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

# GLAD
add_library(glad STATIC IMPORTED)
set_target_properties(glad PROPERTIES
  IMPORTED_LOCATION "${DEPENDENCIES_DIR}/glad/Debug/glad.lib"
  INTERFACE_INCLUDE_DIRECTORIES "${DEPENDENCIES_DIR}/glad/include"
)

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

ADD_MSVC_PRECOMPILED_HEADER("FrameworkPCH.h" "FrameworkPCH.cpp")
ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)