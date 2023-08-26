#pragma once

#include <cassert>
#include <iostream>
namespace bana{
#define EPSILON 1e-5f

#define GL_CHECK(f)                                                            \
  f;                                                                           \
  {                                                                            \
    auto error = glGetError();                                                 \
    if (error != 0) {                                                          \
      std::cout << "GL error = " << error << std::endl;                        \
    }                                                                          \
    assert(error == 0);                                                        \
  }
}

