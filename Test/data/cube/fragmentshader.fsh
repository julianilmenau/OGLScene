// according GLSL version to OpenGL 3.2 core profile
#version 330

// additional color input for this shader; was interpolated among the 3 vertices building the triangle
in vec3 v_color;

// first color attachment output
out vec4 out_color;

uniform sampler2D skybox;

void main()
{
    // assign the interpolated color from the three vertices as the fragments' final color
    out_color = texture(skybox, vec3(0.5,0.5,0.5));
}
