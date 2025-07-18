file(GLOB EDITOR_SOURCES *.cpp)
message("Editor Source files: ${EDITOR_SOURCES}")

set(EDITOR_TARGET ${PROJECT_NAME}-${CMAKE_SYSTEM_NAME})

add_executable(${EDITOR_TARGET} ${EDITOR_SOURCES})
target_link_libraries(${EDITOR_TARGET} core imgui)
