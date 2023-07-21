cmake_minimum_required(VERSION 3.22.1)
project(loader)

include_directories(${PROJECT_SOURCE_DIR}/app/src/main/jni/loader/includes)

aux_source_directory(./includes DIR_SRCS)
aux_source_directory(. MAIN)
aux_source_directory(./headers HEADERS)
#add_library(loader SHARED ${MAIN} ${HEADERS})

add_library(dobby SHARED IMPORTED)
set_target_properties(dobby PROPERTIES IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/app/src/main/jniLibs/armeabi-v7a/libdobby.so)
include_directories(${PROJECT_SOURCE_DIR}/app/src/main/jni/loader/includes)
link_directories(${PROJECT_SOURCE_DIR}/app/src/main/jniLibs/armeabi-v7a)

add_library(loader SHARED ${MAIN} ${HEADERS} ${DIR_SRCS})
target_link_libraries(loader ${dobby})

#link_libraries(${dobby})