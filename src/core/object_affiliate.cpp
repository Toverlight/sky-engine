#include "object_affiliate.h"

void ObjectAffiliate::setOffset(const glm::vec2 &offset)
{
    _offset = offset;
    _is_offset_dirty = true;
}

glm::vec2 ObjectAffiliate::getOffset()
{
    if (_is_offset_dirty) {
        _is_offset_dirty = false;
        auto newSize = _size * _scale;
        switch (_anchor) {
        case Anchor::TOP_LEFT:
            _offset = glm::vec2(0.0f, 0.0f);
            break;
        case Anchor::TOP_CENTER:
            _offset = glm::vec2(-newSize.x / 2.0f, 0.0f);
            break;
        case Anchor::TOP_RIGHT:
            _offset = glm::vec2(-newSize.x, 0.0f);
            break;
        case Anchor::CENTER_LEFT:
            _offset = glm::vec2(0.0f, -newSize.y / 2.0f);
            break;
        case Anchor::CENTER:
            _offset = glm::vec2(-newSize.x / 2.0f, -newSize.y / 2.0f);
            break;
        case Anchor::CENTER_RIGHT:
            _offset = glm::vec2(-newSize.x, -newSize.y / 2.0f);
            break;
        case Anchor::BOTTOM_LEFT:
            _offset = glm::vec2(0.0f, -newSize.y);
            break;
        case Anchor::BOTTOM_CENTER:
            _offset = glm::vec2(-newSize.x / 2.0f, -newSize.y);
            break;
        case Anchor::BOTTOM_RIGHT:
            _offset = glm::vec2(-newSize.x, -newSize.y);
            break;
        default:
            break;
        }

    }
    return _offset;
}

void ObjectAffiliate::setSize(const glm::vec2 &size)
{
    _size = size;
    _is_offset_dirty = true;
}

void ObjectAffiliate::setScale(const glm::vec2 &scale)
{
    _scale = scale;
    _is_offset_dirty = true;
}

void ObjectAffiliate::setAnchor(Anchor anchor)
{
    _anchor = anchor;
    _is_offset_dirty = true;
}
