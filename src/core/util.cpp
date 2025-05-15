#include "util.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstddef>
#include <glm/common.hpp>

glm::vec2 Math::rotateVec2(glm::vec2 v, float radians)
{
    float cos_theta = cosf(radians);
    float sin_theta = sinf(radians);
    return glm::vec2(
        v.x * cos_theta - v.y * sin_theta,
        v.x * sin_theta + v.y * cos_theta
    );
}

float Math::angleBetweenVec2s(glm::vec2 a, glm::vec2 b)
{
    float dot_product = glm::dot(a, b);
    float magnitude_a = glm::length(a);
    float magnitude_b = glm::length(b);
    float cos_theta = dot_product / (magnitude_a * magnitude_b);
    return acos(glm::clamp(cos_theta, -1.0f, 1.0f)); // 限制在[-1, 1]范围内，避免浮点数误差导致的错误
}

void Graphics::renderTexture(const Texture &texture, const glm::vec2 &position, SDL_Renderer* renderer)
 {
    if (renderer == nullptr || texture.texture == nullptr) {
        return;
    }

    SDL_FRect src_rect;
    src_rect.x = texture.clip.x;
    src_rect.y = texture.clip.y;
    src_rect.w = texture.clip.w;
    src_rect.h = texture.clip.h;

    SDL_FRect dst_rect;
    dst_rect.x = position.x;
    dst_rect.y = position.y;
    dst_rect.w = texture.size.x;
    dst_rect.h = texture.size.y;

    SDL_RenderTextureRotated(renderer, texture.texture, &src_rect, &dst_rect, texture.angle, nullptr, texture.is_flipped ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
}

void Graphics::renderLine(const glm::vec2& start, const glm::vec2& end, SDL_FColor color, float thickness, SDL_Renderer* renderer)
{
    if (renderer == nullptr) return;
    SDL_SetRenderDrawColorFloat(renderer, color.r, color.g, color.b, color.a);
    glm::vec2 diff = end - start;
    float length = glm::length(diff);
    if (length == 0.0f) return;
    float half_thickness = thickness / 2.0f;
    glm::vec2 normal_thickness = glm::normalize(glm::vec2(-diff.y, diff.x)) * half_thickness; // 顺时针旋转90°垂直于线段的向量
    SDL_Vertex vertices[4] = {
        { { start.x - normal_thickness.x, start.y - normal_thickness.y }, color, { 0.0f, 0.0f } },
        { { start.x + normal_thickness.x, start.y + normal_thickness.y }, color, { 0.0f, 0.0f } },
        { { end.x + normal_thickness.x, end.y + normal_thickness.y }, color, { 0.0f, 0.0f } },
        { { end.x - normal_thickness.x, end.y - normal_thickness.y }, color, { 0.0f, 0.0f } }
    };

    int indices[6] = { 0, 1, 2, 2, 3, 0 };
    SDL_RenderGeometry(renderer, nullptr, vertices, 4, indices, 6);
    SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Graphics::renderFilledPolygon(const std::vector<SDL_FPoint>& points, SDL_FColor color, SDL_Renderer* renderer)
{
    if (renderer == nullptr || points.size() < 3) return;

    SDL_SetRenderDrawColorFloat(renderer, color.r, color.g, color.b, color.a);

    std::vector<SDL_Vertex> vertices(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        vertices[i] = { points[i], color, { 0.0f, 0.0f } };
    }

    std::vector<int> indices;
    for (size_t i = 1; i < points.size() - 1; ++i) {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }

    SDL_RenderGeometry(renderer, nullptr, vertices.data(), static_cast<int>(vertices.size()), indices.data(), static_cast<int>(indices.size()));
    SDL_SetRenderDrawColorFloat(renderer, 0.0f, 0.0f, 0.0f, 0.0f);
}

void Graphics::renderPolygonOutline(const std::vector<SDL_FPoint>& points, SDL_FColor color, float thickness, SDL_Renderer* renderer)
{
    if (renderer == nullptr || points.size() < 3) return;

    std::vector<SDL_Vertex> vertices(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        vertices[i] = { points[i], color, { 0.0f, 0.0f } };
    }

    std::vector<glm::vec2> normals(points.size());
    for (size_t i = 0; i < points.size(); ++i) {
        size_t next = (i + 1) % points.size();
        glm::vec2 edge = glm::vec2(points[i].x - points[next].x, points[i].y - points[next].y);
        normals[i] = glm::normalize(glm::vec2(-edge.y, edge.x)); // 顺时针旋转90°垂直于边的向量
    }

    std::vector<SDL_Vertex> outline_vertices(points.size() * 2);
    for (size_t i = 0; i < points.size(); ++i) {
        size_t next = (i + 1) % points.size();
        glm::vec2 dir = glm::normalize(normals[i] + normals[next]);
        float length = thickness / 2.0f / glm::dot(normals[i], dir);
        glm::vec2 farthest_point = length * dir + glm::vec2(points[next].x, points[next].y);
        glm::vec2 closest_point = -length * dir + glm::vec2(points[next].x, points[next].y);
        outline_vertices[i * 2] = { {farthest_point.x, farthest_point.y}, color, { 0.0f, 0.0f } };
        outline_vertices[i * 2 + 1] = { {closest_point.x, closest_point.y}, color, { 0.0f, 0.0f } };
    }

    std::vector<int> indices;
    for (size_t i = 0; i < points.size(); ++i) {
        size_t next = (i + 1) % points.size();
        indices.push_back(i * 2);
        indices.push_back(next * 2);
        indices.push_back(i * 2 + 1);
        indices.push_back(next * 2);
        indices.push_back(next * 2 + 1);
        indices.push_back(i * 2 + 1);
    }

    SDL_RenderGeometry(renderer, nullptr, outline_vertices.data(), static_cast<int>(outline_vertices.size()), indices.data(), static_cast<int>(indices.size()));
}

TTF_Text* Text::createTTF_Text(const std::string& text, const std::string& font_path, int font_size, TTF_TextEngine* ttf_engine)
{
    auto font = Game::getInstance().getAssetStore()->getFont(font_path, font_size);
    return TTF_CreateText(ttf_engine, font, text.c_str(), 0);
}
