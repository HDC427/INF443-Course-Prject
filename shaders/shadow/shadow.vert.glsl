#version 330 core

// ref https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping

layout (location = 0) in vec4 position;

/** redundant **/
layout (location = 1) in vec4 normal;
layout (location = 2) in vec4 color;
layout (location = 3) in vec2 texture_uv;
/***************/

// model transformation
uniform vec3 translation = vec3(0.0, 0.0, 0.0);                      // user defined translation
uniform mat3 rotation = mat3(1.0,0.0,0.0, 0.0,1.0,0.0, 0.0,0.0,1.0); // user defined rotation
uniform float scaling = 1.0;                                         // user defined scaling
uniform vec3 scaling_axis = vec3(1.0,1.0,1.0);                       // user defined scaling

// view transform of the light source
uniform mat4 view;
// perspective matrix
uniform mat4 perspective;

void main()
{
    // scaling matrix
    mat4 S = mat4(scaling*scaling_axis.x,0.0,0.0,0.0, 0.0,scaling*scaling_axis.y,0.0,0.0, 0.0,0.0,scaling*scaling_axis.z,0.0, 0.0,0.0,0.0,1.0);
    // 4x4 rotation matrix
    mat4 R = mat4(rotation);
    // 4D translation
    vec4 T = vec4(translation,0.0);

    vec4 position_transformed = R*S*position + T;

    gl_Position = perspective * view * position_transformed;
}
