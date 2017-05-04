// according GLSL version to OpenGL 3.2 core profile
#version 330

// input into vertex shader (configured by vertex array configuration and filled from vertex buffer)
layout(location=0)in vec3 in_vertex;

// second input into vertex shader, used for the fragment color
layout(location=1)in vec3 in_color;

uniform mat4 modelTransform;
uniform mat4 viewProjection;

// additional color output for this shader; will be interpolated among the 3 vertices building the triangle
out vec3 v_color;

void main()
{
    gl_Position =  viewProjection * modelTransform * vec4(in_vertex, 1.0);
    v_color = in_color;
}
