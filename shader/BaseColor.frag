#version 330
in vec2 v_texCoord0;

out vec4 outColor;

uniform sampler2D u_baseColorTexture;

void main() {
//    outColor = texture(u_baseColorTexture, v_texCoord0);
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
}