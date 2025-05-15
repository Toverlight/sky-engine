#pragma once

constexpr int INIT_OBJECT_CHILDREN = 6;
constexpr int INIT_SCENE_SCREEN_OBJECTS = 20;
constexpr int INIT_SCENE_WORLD_OBJECTS = 20;

enum class Anchor
{
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    CENTER_LEFT,
    CENTER,
    CENTER_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT
};

// TODO:文本对齐功能
// enum class TextAlign
// {
//     LEFT,
//     CENTER,
//     RIGHT
// };