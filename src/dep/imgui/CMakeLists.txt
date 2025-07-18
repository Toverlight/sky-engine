# 查找并载入Cmake预设
find_package(SDL3 REQUIRED)

file(GLOB IMGUI_SOURCES
    imgui*.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(imgui
    ${SDL3_LIBRARIES}
)
