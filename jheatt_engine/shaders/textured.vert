#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texcoord;

out vec3 Normal;
out vec2 Texcoord;
out vec3 FragPos;  

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    /* 
    Transposing & inversing here allows us to scale our models without skewing the normals,
    However note that inversing matrices is a costly operation for shaders, so wherever possible 
    we need to try to avoid doing inverse operations since they have to be done on each vertex 
    of the scene. For now this is fine, but for an efficient application we'll likely want to
    calculate the normal matrix on the CPU and send it to the shaders via a uniform before
    drawing (just like the model matrix). 
    */
    Normal =  mat3(transpose(inverse(model))) * normal;
    
    
    Texcoord = texcoord;

    FragPos = vec3(model * vec4(position, 1.0));
    // Multiplication from right to left:
    gl_Position = projection * view * model * vec4(position, 1.0);
}