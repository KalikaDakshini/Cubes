#version 330 core
out vec4 fragColour;

uniform vec3 objColour;

void main()
{
    fragColour = vec4(objColour, 1.0f);
}
