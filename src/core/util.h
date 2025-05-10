#pragma once
#include <glm/glm.hpp>

glm::vec2 rotateVec2(glm::vec2 v, float radians) {
    float cos_theta = cosf(radians);
    float sin_theta = sinf(radians);
    return glm::vec2(
        v.x * cos_theta - v.y * sin_theta,
        v.x * sin_theta + v.y * cos_theta
    );
}
