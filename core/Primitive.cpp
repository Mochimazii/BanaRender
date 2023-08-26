//
// Created by akaring on 2023/8/26.
//

#include "Primitive.h"

namespace bana {

Primitive::Primitive(GLuint vao, int type, int count, int componentType, int offset)
        : _vao(vao), _mode(type), _count(count), _componentType(componentType), _offset(offset) {}

void Primitive::draw() {
    GL_CHECK(glBindVertexArray(_vao));
    if (_offset >= 0) {
        GL_CHECK(glDrawElements(_mode, _count, _componentType, (void *) _offset));
    } else {
        GL_CHECK(glDrawArrays(_mode, 0, _count))
    }
    GL_CHECK(glBindVertexArray(0));
}

} // bana