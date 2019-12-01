//#include<Mesh_IO/Mesh_IO.h>
#ifndef MESH_VIEWERER_DATA
#define MESH_VIEWERER_DATA
#include<Mesh_view/OpenglAlg.h>
#include <map>
#include<string.h>
//strcmp 比较字符串跟整数比较类似
typedef struct Mesh_view_something{
char* name;
int name_id;
int id;
int create_date;
Eigen::MatrixXf *Data;
Eigen::MatrixXi* Data_index;
GLuint VAO,*Buffers;
bool disappear;
void* prop;
void* mesh;
Node* avatar;
void* evolution;
}Mesh_view_something;
typedef struct Mesh_viewer_world{
std::map<int,Node*>species;
std::map<int,char*>species_name_registe;
//use for give a single name
int species_id;
std::map<int,int>something_name_id;
}Mesh_viewer_world;
void Mesh_viewer_world_registe1(Mesh_viewer_world*,char**,int);
void Mesh_viewer_world_registe(Mesh_viewer_world*,char*);
void Mesh_view_something_init(Mesh_view_something*,int);
void Mesh_viewer_world_init(Mesh_viewer_world*);
#endif