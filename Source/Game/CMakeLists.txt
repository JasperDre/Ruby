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
    "*.hpp"
    "*.h")

add_executable(Game ${SRC})

target_include_directories(Game PRIVATE "${CMAKE_CURRENT_LIST_DIR}/")

target_link_libraries(Game PUBLIC Framework)
target_include_directories(Game PUBLIC "../Framework/")

ADD_PROJECT_FILTERS(${SRC_DIR} SRC Source)