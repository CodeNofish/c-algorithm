cmake_minimum_required(VERSION 3.23)

project(c-algorithm)

set(CMAKE_CXX_STANDARD 23)

list(APPEND exclude_dirs lib include)

include_directories(include)
#add_subdirectory(lib)

file(GLOB_RECURSE main_cpp_s ${CMAKE_CURRENT_LIST_DIR}/*.cpp)
foreach (main_cpp ${main_cpp_s})
    cmake_path(GET main_cpp PARENT_PATH parent_path)
    cmake_path(GET parent_path FILENAME subdir_name)

    if (${subdir_name} IN_LIST exclude_dirs)
        continue()
    endif ()

    string(REPLACE / _ my_prefix ${parent_path})
    #    message(${my_prefix})

    cmake_path(GET main_cpp FILENAME file_name)
    cmake_path(REMOVE_EXTENSION file_name LAST_ONLY OUTPUT_VARIABLE file_name)

    string(JOIN "_" target_name ${my_prefix} ${file_name})

    add_executable(${target_name} ${main_cpp})
    target_link_libraries(${target_name} PUBLIC ${extra_libs})

    target_include_directories(${target_name} PUBLIC ${extra_includes})
endforeach ()