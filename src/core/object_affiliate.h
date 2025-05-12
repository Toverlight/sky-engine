#pragma once

#include <glm/glm.hpp>
#include "object_screen.h"
#include "def.h"

class ObjectAffiliate : public Object
{
protected:
    ObjectScreen* _parent = nullptr; // 父节点
    glm::vec2 _offset = glm::vec2(0, 0); // 偏移量
    glm::vec2 _size = glm::vec2(0, 0); // 尺寸
    glm::vec2 _scale = glm::vec2(1, 1); // 缩放
    Anchor _anchor = Anchor::CENTER; // 锚点
    bool _is_offset_dirty = false; // 偏移量是否脏

public:
    ObjectAffiliate() = default;
    virtual ~ObjectAffiliate() = default;

    void setParent(ObjectScreen* parent) { _parent = parent; }
    ObjectScreen* getParent() { return _parent; }
    void setOffset(const glm::vec2& offset);
    glm::vec2 getOffset();
    void setSize(const glm::vec2& size);
    glm::vec2 getSize() { return _size; }
    void setScale(const glm::vec2& scale);
    glm::vec2 getScale() { return _scale; };
    void setAnchor(Anchor anchor);
    Anchor getAnchor() { return _anchor; }
};