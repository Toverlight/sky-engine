
set(PROJ_NAME SKYPROJECT)

file(GLOB PROJ_SOURCES *.cpp)
message("Project Source files: ${PROJ_SOURCES}")

set(PROJ_TARGET ${PROJ_NAME}-${CMAKE_SYSTEM_NAME})

# 添加可执行文件
add_executable(${PROJ_TARGET} ${PROJ_SOURCES})
target_link_libraries(${PROJ_TARGET} core)
