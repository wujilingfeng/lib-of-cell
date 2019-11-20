#version 450 core

layout( location = 0 ) in vec3 vPosition;
layout(location=1) in vec3 aColor;
layout(location=2) in vec2 aTexCoord;
layout(location=3) in vec3 nor;
layout(location=4) in float vertices_id;
uniform mat4 Proj;
uniform mat4 Matrix;
uniform float Mesh_or_Edge;
uniform int Mesh_or_Edge_id;
out vec3 ourColor;
out vec2 TexCoord;
out vec4 id_in;
out float depth;
out vec4 real_position;
float compute_specular(vec3 light_dir,vec3 eye_dir,vec3 obj_nor)
{
	float temp=dot(obj_nor,light_dir);
    
	vec3 light_dir_new=light_dir-2*obj_nor*min(dot(obj_nor,light_dir),0);
	return max(-dot(eye_dir,light_dir_new),0);


}
void main()
{ //vPosition[3]=1.0f;
//vPosition[2]=0.5f;
   vec3 posi=vPosition;
	real_position=Matrix*vec4(posi,1.0f);
    vec4 my_real_position=real_position;
    gl_Position =Proj*real_position;
//	gl_Position/=gl_Position.w;
	
    vec4 temp1=-Matrix*vec4(nor,0.0f);

    vec3 temp=normalize(vec3(temp1.x,temp1.y,temp1.z));
	
    vec3 dir=vec3(0.0,0.0,1.0);
 	//vec3 dir1=dir-2*temp*dot(temp,dir);
	
   	float fac=max(-dot(temp,dir),0.1)+compute_specular(dir,normalize(vec3(real_position.x,real_position.y,real_position.z)),temp);
//float fac=max(compute_specular(dir,normalize(vec3(real_position.x,real_position.y,real_position.z)),temp),0.1);
	//aColor=vec3(1.0,0.0,0.0);

	vec3 lightcolor=vec3(0.2,0.5,0.1),objcolor=vec3(0.3,0.3,0.3);
    if(Mesh_or_Edge==1)
    {
        ourColor=vec3(0.2,0.8,0.3);

    }
    else
    { 
        ourColor=aColor*fac;
    }
    //id_in.z=vertices_id;
    id_in.z=floor(gl_VertexID/3);
    id_in.x=abs(sin(gl_VertexID));

    id_in.y=abs(cos(gl_VertexID));
    //id_in.w=pow(gl_VertexID,4);
    depth=gl_Position.z/gl_Position.w;
    TexCoord=aTexCoord;
}
