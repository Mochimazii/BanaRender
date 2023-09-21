//
// Created by akaring on 2023/8/26.
//

#ifndef BANARENDER_PRIMITIVE_H
#define BANARENDER_PRIMITIVE_H

#include "macro.h"
#include "glad.h"
#include <memory>

namespace bana {

class Primitive {
public:
    Primitive(GLuint vao, int type, int count, int componentType,
              int offset = -1);
    void draw();

private:
    GLuint _vao;
    //��Ⱦģʽ
    //0��POINTS�����Ƶ�
    //1��LINES�������߶�
    //2��LINE_LOOP�����Ʒ���߶�
    //3��LINE_STRIP�����������߶�
    //4��TRIANGLES������������
    //5��TRIANGLE_STRIP���������������δ�
    //6��TRIANGLE_FAN��������������
    int _mode;
    //����Ԫ������(Ҫ����Ԫ�ص�����)
    int _count;
    //5120��BYTE���з����ֽڡ�
    //5121��UNSIGNED_BYTE���޷����ֽڡ�
    //5122��SHORT���з��Ŷ�������
    //5123��UNSIGNED_SHORT���޷��Ŷ�������
    //5126��FLOAT����������
    int _componentType;
    // ��������ƫ����
    int _offset;
};

} // bana

#endif //BANARENDER_PRIMITIVE_H
