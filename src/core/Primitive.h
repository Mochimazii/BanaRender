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
    //渲染模式
    //0：POINTS，绘制点
    //1：LINES，绘制线段
    //2：LINE_LOOP，绘制封闭线段
    //3：LINE_STRIP，绘制连续线段
    //4：TRIANGLES，绘制三角形
    //5：TRIANGLE_STRIP，绘制连续三角形带
    //6：TRIANGLE_FAN，绘制三角形扇
    int _mode;
    //数据元素数量(要绘制元素的数量)
    int _count;
    //5120：BYTE，有符号字节。
    //5121：UNSIGNED_BYTE，无符号字节。
    //5122：SHORT，有符号短整数。
    //5123：UNSIGNED_SHORT，无符号短整数。
    //5126：FLOAT，浮点数。
    int _componentType;
    // 索引数据偏移量
    int _offset;
};

} // bana

#endif //BANARENDER_PRIMITIVE_H
