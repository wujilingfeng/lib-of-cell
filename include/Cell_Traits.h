#ifndef LIB_CELL_TRAITS
#define LIB_CELL_TRAITS
//#define FACE_REQUIRE
//表示我要处理的是单形cell
#define SIMPLEX_REQUIRE
#define MANIFOLD_REQUIRE
#define template_v Vertex
#define template_f Face
#define template_c Cell
#define template_hf HalfFace

#define template_m Mesh
#include<stdlib.h>
#ifdef SIMPLEX_REQUIRE

#endif

typedef struct VertexT{}VertexT;
typedef struct CellT{}CellT;
typedef struct MeshT{}MeshT;
typedef struct FaceT{}FaceT;
typedef struct HalfT{}HalfT;
typedef struct Node{
void* Prev=NULL;
void* value=NULL;
void* Next=NULL;//point to node*
void* traits;
}Node;
void free_node(Node*);
Node* node_find(Node*,void*);
void Node_init(Node*);
Node* node_copy(Node*);
int node_size(Node*);
Node* node_overlying(Node*,void*);
//Node operator++(Node);
#endif
