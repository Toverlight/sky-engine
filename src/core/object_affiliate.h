#pragma once

#include <glm/glm.hpp>
#include "object.h"
#include "def.h"

class ObjectAffiliate : public Object
{
protected:
    Object* _parent = nullptr; // 父节点
    glm::vec2 _offset = glm::vec2(0, 0); // 偏移量
    glm::vec2 _size = glm::vec2(0, 0); // 尺寸
    Anchor _anchor = Anchor::CENTER; // 锚点
    bool _is_offset_dirty = false; // 偏移量是否脏

public:
    ObjectAffiliate() = default;
    virtual ~ObjectAffiliate() = default;

    virtual void setParent(Object* parent) { _parent = parent; }
    virtual Object* getParent() { return _parent; }
    virtual void setOffset(const glm::vec2& offset);
    virtual glm::vec2 getOffset();
    virtual void setSize(const glm::vec2& size);
    virtual glm::vec2 getSize() { return _size; }
    virtual void setAnchor(Anchor anchor);
    virtual Anchor getAnchor() { return _anchor; }
};