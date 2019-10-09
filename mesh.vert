#version 330 core

layout( location = 0 ) in vec3 vPosition;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;
layout(location=3) in vec3 nor;
uniform mat4 Proj;
uniform mat4 Matrix;
out vec3 ourColor;
out vec2 TexCoord;


void main()
{ //vPosition[3]=1.0f;
//vPosition[2]=0.5f;
	
    //gl_Position =Proj*Matrix*vec4(vPosition,1.0f);
	gl_Position=vec4(vPosition,1.0f);
    //vec4 temp1=Matrix*vec4(nor,0.0f);

//vec3 temp=normalize(vec3(temp1.x,temp1.y,temp1.z));
//vec3 dir=-1*vec3(0.0,0.0,1.0);
//float fac=max(dot(temp,dir),0.1);
    ourColor=vec3(1.0,0.5,0.0)*1;
    TexCoord=aTexCoord;
}
