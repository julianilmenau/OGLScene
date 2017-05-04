// according GLSL version to OpenGL 3.2 core profile
#version 330

// input into vertex shader (configured by vertex array configuration and filled from vertex buffer)
layout(location=0)in vec3 in_vertex;

uniform mat4 modelTransform;
uniform mat4 viewProjection;

// additional color output for this shader; will be interpolated among the 3 vertices building the triangle
out vec2 v_textcoord;

void main()
{
    gl_Position =  viewProjection * vec4(in_vertex, 1.0);
    v_textcoord = vec2(in_vertex.xz);
}
