#version 450 core
out vec4 fColor;
in vec3 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
void main()
{

fColor=vec4(ourColor,1.0);
//fColor=texture(ourTexture,TexCoord);
//fColor=vec4(1.0,0.5,0.4,1.0);
}
