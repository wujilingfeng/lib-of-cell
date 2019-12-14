//#include<Mesh_IO/Mesh_IO.h>
#ifndef MESH_VIEWERER_DATA
#define MESH_VIEWERER_DATA
#include<Mesh_view/OpenglAlg.h>
#include<map>
#include<string.h>
#include<time.h>
//strcmp 比较字符串跟整数比较类似

void Mesh_view_something_init(struct Mesh_view_something*);
typedef struct Mesh_view_something{
	char* name;
	int name_id;
	int id;
	unsigned int create_date;
	int disappear;
	void* prop;
	void* mesh;
	//分身
	Node* avatar;
	void* evolution;
}Mesh_view_something;
Node* Mesh_viewer_world_create_something(struct Mesh_viewer_world*,char *);
void Mesh_viewer_world_registe1(Mesh_viewer_world*,char**,int);
Node* Mesh_viewer_world_registe(Mesh_viewer_world*,char*);
void Mesh_viewer_world_init(Mesh_viewer_world*);
Node* Mesh_viewer_world_find_species(Mesh_viewer_world*,char*);
typedef struct Mesh_viewer_world{
	int species_id;
	std::map<int,Node*>species;
	std::map<int,char*>species_name_registe;
//use for give a single name
	std::map<int,int>something_id;

	//Mesh_view_something*(*create_something)(struct Mesh_viewer_world*,char*)=Mesh_viewer_world_create_something;
}Mesh_viewer_world;

typedef struct Mesh_viewer_points
{
	double *Data,*color;
	int* Data_index;
	GLuint VAO,*Buffers;
	void *prop;
	void* evolution;
}Mesh_viewer_points;
typedef struct Mesh_viewer_edges
{

}Mesh_viewer_edges;
typedef struct Mesh_viewer_faces
{

}Mesh_viewer_faces;
#endif