#include<Mesh/_Func_.h>


void Vertex_init_(template_v* pv)
{
//template_v* pv=(Vertex*)pv_input;
    pv->cells=NULL;
    pv->faces=NULL;
    pv->id=-1;
    pv->point=NULL;
    pv->point_size=0;
    pv->prop=NULL;
}
/*
void Vertex_copy_(const void * pv_input,const void * pv_input1,void* pv_output)
{
Vertex* pv1=(Vertex*)pv_input;
Vertex* pv2=(Vertex*)pv_input1;
pv1->id=pv2->id;
pv1->Point=pv2->Point;
pv1->traits=pv2->traits;
*(bool_t*)pv_output=true;

}
void Vertex_cmp_(const void*pv_input,const void*pv_input1,void* pv_output)
{
*(bool_t*)pv_output=(((Vertex*)pv_input)->id<((Vertex*)pv_input1)->id)?true:false;

}
void Vertex_destroy_(const void* pv_input,void* pv_output)
{
Vertex* pv=(Vertex*)pv_input;
memset(pv,0,sizeof(Vertex));
*(bool_t*)pv_output=true;
}*/
void Cell_init_(template_c *pv)
{
	pv->vertices=NULL;
	pv->halffaces=NULL;
	pv->id=-1;
    pv->vertices_size=0;
    pv->prop=NULL;
	//pv->dimensiof

}
void Face_init_(template_f *f)
{
    f->vertices=NULL;
    f->halffaces=(template_hf**)malloc(sizeof(template_hf*)*2);
    f->halffaces[0]=(template_hf*)malloc(sizeof(template_hf));
    f->halffaces[1]=(template_hf*)malloc(sizeof(template_hf));
    HalfFace_init_(f->halffaces[0]);
    HalfFace_init_(f->halffaces[1]);
    f->halffaces[0]->face=f;
    f->halffaces[1]->face=f;
//f->inverse=(int*)malloc(sizeof(int)*2);
//f->inverse[0]=0;
//f->inverse[1]=0;
//f->halffaces_size=0;
    f->vertices_size=0;
    f->prop=NULL;


}
void HalfFace_init_(template_hf *hf)
{
    hf->vertices=NULL;
    hf->vertices_size=0;
//hf->cell=(void**)malloc(sizeof(void*));
//hf->face=(void**)malloc(sizeof(void*));
    hf->cell=NULL;
    hf->face=NULL;
    hf->prop=NULL;


}
void free_HalfFace(template_hf *hf)
{
	if(hf->vertices!=NULL)
	{
        free(hf->vertices);
	}
free(hf);
hf=NULL;

}
void free_Vertex(template_v*v)
{if(v->point!=NULL)
	{
	
free(v->point);
	}
	if(v->faces!=NULL)
	{
	free_node(v->faces);
	}
//free_node(v->faces);
	if(v->cells!=NULL)
	{
	free_node(v->cells);
	}
free(v);
v=NULL;
//return true;
}
void free_Face(template_f*f)
{
    if(f->vertices!=NULL)
    {
        free(f->vertices);
    }
    free_HalfFace(f->halffaces[0]);
    free_HalfFace(f->halffaces[1]);
    free(f->halffaces);
//free(f->inverse);
    free(f);
    f=NULL;
//return true;

}
void free_Cell(template_c*c)
{
	if(c->vertices!=NULL)
	{
	
           free(c->vertices);
	}
	if(c->halffaces!=NULL)
	{
	
	
         free_node(c->halffaces);
	}
    free(c);
    c=NULL;
//return true;


}
void Face_remove_c(template_f*f ,template_c*c)
{
	if(c==NULL)
	{
	
	return ;
	}

    if((f->halffaces[0])->cell==c)
    {
        ((template_hf*)f->halffaces[0])->cell=NULL;
//f->inverse[0]=f->inverse[1];
//f->cells[1]=NULL;
    }
    else if(((template_hf*)f->halffaces[1])->cell==c)
    {

        ((template_hf*)f->halffaces[1])->cell=NULL;
    }
    else
    {
	    return;
    }

//f->cells_size--;


}
void Vertex_remove_f(template_v*v,template_f*f)
{
    Node* node=node_find(v->faces,(void*)f);
    if(node==NULL)
    {
        return;
    }
    Node* node1=(Node*)node->Prev,*node2=(Node*)node->Next;
    if(node1!=NULL)
    {
        node1->Next=(void*)node2;
    }
    else
    {
        v->faces=node2;

    }
    if(node2!=NULL)
    {
        node2->Prev=(void*)node1;
    }
    free(node);
    node=NULL;
}

void Cell_remove_hf(template_c*c,template_hf*f)
{
    Node*node=node_find(c->halffaces,(void*)f);
    if(node==NULL)
    {
        printf("cant find\r\n");
        return;
    }
    Node* node1=(Node*)node->Prev,*node2=(Node*)node->Next;
    if(node1!=NULL)
    {
        node1->Next=(void*)node2;
    }
    else
    {
        c->halffaces=node2;
    }
    if(node2!=NULL)
    {
        node2->Prev=(void*)node1;
    }   
    free(node);
    node=NULL;
}
void Vertex_remove_c(template_v*v,template_c*c)
{
    Node* node=node_find(v->cells,(void*)c);
    if(node==NULL)
    {
        return;
    }
    Node* node1=(Node*)node->Prev,*node2=(Node*)node->Next;
    if(node1!=NULL)
    {
        node1->Next=(void*)node->Next;
    }
    else
    {
        v->cells=node2;
    }
    if(node2!=NULL)
    {
        node2->Prev=(void*)node1;
    }
    free(node);
    node=NULL;

}

//when the sequense of vertices is requ

/*void Cell_copy_(const void*pv_in1,const void *pv_in2,void*pv_ou)
{
Cell* pv1=(Cell*)pv_in1,*pv2=(Cell*)pv_in2;
pv1->id=pv2->id;
pv1->traits=pv2->traits;
*(bool_t*)pv_ou=true;

}
void Cell_cmp_(const void* pv_in1,const void* pv_in2,void*pv_ou)
{
*(bool_t*)pv_ou=(((Cell*)pv_in1)->id<((Cell*)pv_in2)->id)?true:false;
}
void Cell_destroy_(const void*pv_in,void *pv_ou)
{
Cell*pv=(Cell*)pv_in;

memset(pv,0,sizeof(Cell));
*(bool_t*)pv_ou=true;

}*/
/*#ifdef FACE_REQUIRE
void Cell_faces_push_back(struct Cell *own,template_v** temp_v,int size)
{
         //vector_t *temp_v1=create_vector(void*);
	//std::vector<template_v*> temp_v1;
	 //vector_init(temp_v1);

	for(int i=0;i<size;i++)
	{
	vector_push_back(temp_v1,(void*)temp_v[i]);
	}


       vector_push_back(own->faces,temp_v1);
     vector_destroy(temp_v1);
}
#endif*/
/*bool is_equal(vector_t *pv1,vector_t*pv2)
{
	if(vector_size(pv1)!=vector_size(pv2))
	{

	return false;
	
	}

for(iterator_t iter=vector_begin(pv1);!iterator_equal(iter,vector_end(pv1));iter=iterator_next(iter))
{
iterator_t iter1=vector_begin(pv2);
for(;!iterator_equal(iter1,vector_end(pv2));iter1=iterator_next(iter1))
{
if(*(void**)iterator_get_pointer(iter)==*(void**)iterator_get_pointer(iter1))
{
	break;
}

}
if(iterator_equal(iter1,vector_end(pv2)))
{
return false;
}

}

return true;
}
iterator_t find(map_t *pm,vector_t *pv)
{
iterator_t it=map_begin(pm);
for(;!iterator_equal(it,map_end(pm));it=iterator_next(it))
{
if(is_equal(pv,(vector_t*)pair_first(it)))
{
return it;

}
}
return it;

}*/
template_v* Mesh_create_vertex(struct Mesh* own)
{
    template_v* v=(template_v*)malloc(sizeof(template_v));

    Vertex_init_(v);

    v->id=own->vertex_id++;
    own->vertices[v->id]=v;
    return v;


}

template_v* Mesh_create_vertexv(struct Mesh*own,double* p,int size)
{

    template_v*v= Mesh_create_vertex(own);
    v->point_size=size;
   v->point=(double*)malloc(sizeof(double)*size);
    for(int i=0;i<size;i++)
    {
        v->point[i]=p[i];
    
    }
    return v;


}
template_f * Mesh_create_face(struct Mesh* own)
{
    template_f* f=(template_f*)malloc(sizeof(template_f));
    Face_init_(f);
    f->id=own->face_id++;
    own->faces[f->id]=f;
    return f;

}


template_c* Mesh_create_cell(struct Mesh* own)
{
    template_c *c=(template_c*)malloc(sizeof(template_c));

    Cell_init_(c);
    c->id=own->cell_id++;
    own->cells[c->id]=c;
    return c;

}
template_hf * Mesh_create_halfface(struct Mesh* own,template_f* f,template_v** temp_v,int size)
{
	//f==NULL情况也要写
    template_hf *hf=NULL;
    if(f->halffaces[0]->vertices==NULL)
    {
        hf=f->halffaces[0];
    }
    else if(f->halffaces[1]->vertices==NULL)
    {

        hf=f->halffaces[1];
    }
    else
    {
        if(f->halffaces[0]->cell==NULL)
        {
            hf=f->halffaces[0];
        }
        else if(f->halffaces[1]->cell==NULL)
        {
            hf=f->halffaces[1];
        }
        else
        {
            printf("没办法，错误在这里\n"); 
            return NULL;
        }
    }
    hf->id=own->halfface_id++;
    own->halffaces[hf->id]=hf;
    if(hf->vertices==NULL)
    {

        hf->vertices=(void**)malloc(sizeof(void*)*size);
    }
    for(int i=0;i<size;i++)
    {
        hf->vertices[i]=(void*)temp_v[i];
    }
    hf->vertices_size=size;
    return hf;


}
//以下程序表明点到face的遍历没有不能保证顺(逆)时针(当cell是曲面)
template_f* Mesh_create_facev(struct Mesh*own,template_v** temp_v,int size)
{
//	template_f*f=own->create_face(own);
	template_f*f=own->get_facev(own,temp_v,size);
	//template_f* f=NULL;
	if(f==NULL)
	{
	//printf("create_face\r\n");
	    f=own->create_face(own);
	}
	else
	{

//	printf("create_face\r\n");
	    return f;
	}
	f->vertices_size=size;
	f->vertices=(void**)malloc(sizeof(void*)*size);
    for(int i=0;i<size;i++)
    {

        f->vertices[i]=(void*)temp_v[i];
        temp_v[i]->faces=node_overlying(temp_v[i]->faces,(void*)f);

    }


    return f;

}

template_c* Mesh_create_cellf(struct Mesh* own,template_hf**temp_hf,int size)
{
    template_c* c=own->create_cell(own);
    
    Node* node=NULL,*node_v=NULL;
    for(int i=0;i<size;i++)
    {
        temp_hf[i]->cell=(void*)c;
        node=node_overlying(node,(void*)temp_hf[i]);
        for(int j=0;j<temp_hf[i]->vertices_size;j++)
        {
            if(node_find(node_v,temp_hf[i]->vertices[j])==NULL)
            {
             node_v=node_overlying(node_v,temp_hf[i]->vertices[j]); 
            
            }
        
        
        }
        
    }
    //还差free掉node_v
    c->halffaces=node;
    int le=node_size(node_v);
    Node* temp_nodev=node_v;
    c->vertices=(void**)malloc(sizeof(void*)*le);
    c->vertices_size=le;
    int i=0;
    while(node_v!=NULL)
    {       c->vertices[i]=node_v->value;

        
        ((template_v*)(node_v->value))->cells=node_overlying(((template_v*)(node_v->value))->cells,(void*)c);
        node_v=(Node*)node_v->Next;
    i++;
    }
    free_node(temp_nodev);
    return c;
}
//应该写 Mesh_get_cellv，并用在下面判断(但速度会变慢)
//以下程序也不能保证点到cell的遍历是顺(逆)时针(当cell表示面时)
//这个表示create simplex
template_c* Mesh_create_cellv(struct Mesh* own,template_v** temp_v,int size)
{
    template_c* c=own->create_cell(own);
    c->vertices=(void**)malloc(sizeof(void*)*size);
    c->vertices_size=size;
    for(int i=0;i<size;i++)
    {

        c->vertices[i]=(void*)temp_v[i];
//
        
        temp_v[i]->cells=node_overlying(temp_v[i]->cells,(void*)c);

//#ifdef SIMPLEX_REQUIRE
        template_v* temp_v1[size-1];
        int temp_i=0;
        for(int j=0;j<size;j++)
        {

            if(j!=i)
            {

                temp_v1[temp_i]=temp_v[j];
	            temp_i++;
            }

        }
    //这样排顺序，是为了给一个单形的face,和另一个顶点p0,那么p0,face_i就是这个cell的点顺序
        if(i%2==0)
        {}
        else if(size>2)
        {
            template_v* vv=temp_v1[0];
            temp_v1[0]=temp_v1[1];
            temp_v1[1]=vv;
        }
        template_f* f=own->create_facev(own,temp_v1,size-1);
        template_hf* hf=own->create_halfface(own,f,temp_v1,size-1);

        hf->cell=(void*)c;
        c->halffaces=node_overlying(c->halffaces,(void*)hf);

//
//f->cells[f->cells_size++]=(void*)c;

//#endif
    }
    return c;
}
int Mesh_num_c(struct Mesh* own)
{

return own->cells.size();
}
int Mesh_num_f(struct Mesh* own)
{

return own->faces.size();
}
int Mesh_num_v(struct Mesh* own)
{
	return own->vertices.size();
}
int Mesh_num_hf(struct Mesh* own)
{

    return own->halffaces.size();
}
template_v Mesh_get_vertex(struct Mesh* own,int id)
{
	template_v v;
    auto it=own->vertices.find(id);
    if(it!=own->vertices.end())
    {
        v=*(it->second);
//return *(it->second);
    }
    return v;
//return NULL;
}
template_c Mesh_get_cell(struct Mesh* own,int id)
{
	template_c c;
    auto it=own->cells.find(id);
    if(it!=own->cells.end())
    {
        c= *(it->second);
    }
    return c;
//return NULL;

}
template_f Mesh_get_face(struct Mesh*own,int id)
{
    template_f f;
    auto it=own->faces.find(id);
    if(it!=own->faces.end())
    {
        f=*(it->second);
    }
    return f;
}
template_f* Mesh_get_facev(struct Mesh*own,template_v** temp_v,int size)
{
    Node* node=temp_v[0]->faces;
    bool b=false;
    while(node!=NULL)
    {   b=true;
        for(int i=1;i<size;i++)
        {
            if(node_find(temp_v[i]->faces,node->value)==NULL)
            {
                b=false;
                break;
            }

        }
        if(b)
        {

            break;
        }
        node=(Node*)node->Next;
    }

    if(b)
    {
        return (template_f*)node->value;
//printf("chenggong\r\n");
    }

    return NULL;
}
template_c* Mesh_get_cellv(struct Mesh*own,template_v** temp_v,int size)
{
    Node* node=temp_v[0]->cells;
    bool b=false;
    while(node!=NULL)
    {
        b=true;
        for(int i=1;i<size;i++)
        {
            if(node_find(temp_v[i]->cells,node->value)==NULL)
            {
            b=false;
            break;
            }
        
        }
        if(b)
        {
            break;
        
        }
        node=(Node*)node->Next;
    
    }
    if(b)
    {
        return (template_c*)node->value;
    
    }
    return NULL;

}
template_c* Mesh_get_cellf(struct Mesh* own,template_f** temp_f,int size)
{
    bool b=false;
    int i=0;
    for(i=0;i<2;i++)
    {   if(temp_f[0]->halffaces[i]->cell==NULL)
        {
            //b=false;
            continue;
        
        }
        b=true;
        for(int j=1;j<size;j++)
        {
            if(temp_f[j]->halffaces[0]->cell==temp_f[0]->halffaces[i]->cell||temp_f[j]->halffaces[1]->cell==temp_f[0]->halffaces[i]->cell)
            {
                continue;
            
            
            }
            else
            {
            b=false;
            break;
            }
        
        
        }
        if(b)
        {
        break;
        }
    
    
    }
    if(b)
    {
        return (template_c*)temp_f[0]->halffaces[i]->cell;
    }
    return NULL;


}
bool Mesh_delete_vertex(struct Mesh*own,template_v &v_,bool burning)
{
    template_v*v;
    auto it=own->vertices.find(v_.id);
    if(it!=own->vertices.end())
    {
        own->vertices.erase(it);
        v=it->second;
    }
    else
    {
        return false;
    }
//handle with cells
//printf("nihao\r\n");
    template_c*c;
	Node* node=node_copy(v->cells),*node1,*node2;
	node1=node;
	while(node1!=NULL)
	{node2=(Node*)node1->Next;
	c=(template_c*)node1->value;
	own->delete_cell(own,*c,true);
	node1=node2;
	//printf("cells size%d\r\n",node_size(v->cells));
	}
	free_node(node);
#ifndef MANIFOLD_REQUIRE
	node=node_copy(v->faces);
	template_f*f;
	node1=node;
	//printf("nihao2\r\n");
	while(node1!=NULL)
        {node2=(Node*)node1->Next;
		f=(template_f*)node1->value;
        own->delete_face(own,*f,true);
	node1=node2;
        }
free_node(node);
	if(burning)
        {
 	free_Vertex(v);       
	}
	

#endif
    return true;
}
bool Mesh_delete_face(struct Mesh*own,template_f &f_,bool burning)
{
    template_f*f;
    auto it=own->faces.find(f_.id);
    if(it!=own->faces.end())
    {
        own->faces.erase(it);
        f=it->second;
    }
    else
    {
        return false;
    }
    if(f->halffaces[0]->cell!=NULL)
    {
	    own->delete_cell(own,*((template_c*)f->halffaces[0]->cell),burning);
//Cell_remove_f((template_c*)f->cells[0],f);
    }
    if(f->halffaces[1]->cell!=NULL)
    {
//Cell_remove_f((template_c*)f->cells[1],f);
    own->delete_cell(own,*((template_c*)f->halffaces[1]->cell),burning);
    }
#ifndef MANIFOLD_REQUIRE
//应该修改放到外面
    for(int i=0;i<f->vertices_size;i++)
    {
        Vertex_remove_f((template_v*)f->vertices[i],f);

    }

    if(burning)
    {
        free_Face(f);
    }


#endif
    return true;
}
bool Mesh_delete_cell(struct Mesh* own,template_c &c_,bool burning)
{
    template_c* c;
    auto it=own->cells.find(c_.id);
    if(it!=own->cells.end())
    {
        own->cells.erase(it);
        c=it->second;
    }
    else
    {
        return false;
    }
    //handle with face
    template_f*f;
    Node* node=c->halffaces,*node1;
    while(node!=NULL)
    {
        node1=(Node*)node->Next;
        f=(template_f*)((template_hf*)node->value)->face;
        //face要甩掉cell
        Face_remove_c(f,c);
        node=node1;
    }
    template_v*v;
    for(int i=0;i<c->vertices_size;i++)
    {
        v=(template_v*)c->vertices[i];
        Vertex_remove_c(v,c);
    }
#ifdef MANIFOLD_REQUIRE
    Node* node_f=c->halffaces;
    while(node_f!=NULL)
    {
        f=(template_f*)((template_hf*)node_f->value)->face;
        if(f->halffaces[0]->cell==NULL&&f->halffaces[1]->cell==NULL)
        {
            for(int i=0;i<f->vertices_size;i++)
            {
                Vertex_remove_f((template_v*)f->vertices[i],f);

            }
            auto fit=own->faces.find(f->id);
            if(fit!=own->faces.end())
            {
                own->faces.erase(fit);

            }
            printf("face is removed\r\n");
            free_Face(f);
        }
        node_f=(Node*)node_f->Next;

    }
    for(int i=0;i<c->vertices_size;i++)
    {
	    v=(template_v*)c->vertices[i];
        if(v->cells==NULL)
        {
	        auto vit=own->vertices.find(v->id);
	        if(vit!=own->vertices.end())
	        {
	            own->vertices.erase(vit);
	        }
	        free_Vertex(v);
        }

    }
#endif

    if(burning)
    {
        free_Cell(c);

    }
    return true;
}
bool Mesh_face_is_boundary(struct Mesh* own,template_f *f)
{

    if(f->halffaces[0]->cell==NULL||f->halffaces[1]->cell==NULL)
    {   return true;}
    return false;
}

bool Mesh_vertex_is_boundary(struct Mesh* own,template_v &v)
{
    Node* node=v.faces;
    while(node!=NULL)
    {
        if(own->face_is_boundary(own,(template_f*)node->value))
        {   return true;}
        node=(Node*)node->Next;
    }
    return false;
}
//给它一个初始面，他会返回boundary的node链
//这个函数需要修改
Node* Mesh_node_of_boundary_face(struct Mesh* own,template_f *f_)
{
//Node* node=(Node*)malloc(sizeof(Node));
    if(f_==NULL)
    {
        return NULL;
    }
    Node* node=NULL,*node3=NULL;
    template_f *f;

    template_hf* hf;
    auto it=own->faces.find(f_->id);
    if(it==own->faces.end())
    {   printf("没找到\n");
        return NULL;
    }
    else
    {
	//printf("it\r\n");
        f=it->second;
    }
    if(!own->face_is_boundary(own,f_))
    {return NULL;}
    else
    {
        //printf("shi\n");
//printf("boundary\r\n");
        node=node_overlying(node,(void*)f);
        
        if(f->halffaces[1]->cell==NULL)
        {
            hf=f->halffaces[1];
            node3=node_overlying(node3,(void*)hf);
        }
        if(f->halffaces[0]->cell==NULL)
        {
            hf=f->halffaces[0];
             node3=node_overlying(node3,(void*)hf);
        }
//node1->value=(void*)f;
        
//node1->value=
    }

    //std::map<int,int> temp_faces;
    //for(auto fit=own->faces.begin();fit!=own->faces.end();fit++)
    //{
      //  temp_faces[fit->first]=0;

   // }
   // 深度优先的遍历
//   printf("shendu\n");
   int* temp_faces=(int*)malloc(sizeof(int));
   *temp_faces=1;
    template_v *v;
    Node* node2;
    while(node!=NULL)
    {   
        push:
        f=(template_f*)node->value;
//        printf("f : %d\n",f->id);
        if(f->halffaces[0]->cell!=NULL)
        {
            hf=f->halffaces[0];
        }
        else
        {
            hf=f->halffaces[1];
        }
        f->prop=(void*)temp_faces;
        for(int i=0;i<hf->vertices_size;i++)
        {
            v=(template_v*)hf->vertices[i];
            node2=v->faces;

            while(node2!=NULL)
            {
                if(own->face_is_boundary(own,(template_f*)node2->value))
                {
                    if(((template_f*)node2->value)->prop==NULL)
                    {
                        node=node_overlying(node,node2->value);
                       void* temp_value=NULL;
                        if(((template_f*)node2->value)->halffaces[0]->cell==NULL)
                        {

                           temp_value=(void*)(((template_f*)node2->value)->halffaces[0]);
                            node3=node_overlying(node3,temp_value);
                        }
                         if(((template_f*)node2->value)->halffaces[1]->cell==NULL)
                        {
                            temp_value=(void*)(((template_f*)node2->value)->halffaces[1]);
                             node3=node_overlying(node3,temp_value);
                        }
                       
                        goto push;
                    
                    }
                }
                node2=(Node*)node2->Next;

            }
        }
    
        Node *node1=node;
        node=(Node*)node->Next;
        
        free(node1);
        node1=NULL;
    }
    free(temp_faces);
    
    return node3;
}
void Mesh_external_cell_init_(struct Mesh* own)
{
    free_node(own->external_cell.halffaces);
    own->external_cell.halffaces=NULL;
//own->external_cell=(template_c*)malloc(sizeof(template_c));
    for(auto it=own->faces.begin();it!=own->faces.end();it++)
    {   if(own->face_is_boundary(own,it->second))
        {
            own->external_cell.halffaces=own->node_of_boundary_face(own,it->second);
            break;
        }
    }
    
    template_hf* hf1,hf2;

    Node* node=own->external_cell.halffaces;
    if(node==NULL)
    {
    
        return;
    }

    reset_f_prop(own);
    while(node!=NULL)
    {
        hf1=(template_hf*)node->value;
        if(hf1->vertices==NULL)
        {
            hf2=own->opposite_halfface(*hf1);
            hf1->vertices=(void**)malloc(sizeof(void*)*hf2.vertices_size);
            hf1->vertices_size=hf2.vertices_size;
           
                for(int i=0;i<hf2.vertices_size;i++)
                {
                    hf1->vertices[i]=hf2.vertices[i];
                  //  printf("test id:%d\n",((template_v*)(hf1->vertices[i]))->id);
                }
                if(hf1->vertices_size>=2)
                {
                 void * temp=hf1->vertices[0];
                  hf1->vertices[0]=hf1->vertices[1];
                     hf1->vertices[1]=temp;
                }
           
              //  printf("youyige\n");
            
            
        }

         node=(Node*)node->Next;
    }

}
template_hf Mesh_opposite_halfface(template_hf &hf)
{
    template_f*f=(template_f*)hf.face;
    if(f->halffaces[0]->cell==hf.cell)
    {
        return *f->halffaces[1];
    }
    else
    {
        return *f->halffaces[0];

    }


}
void lib_cell_init()
{
//type_register(Vertex,Vertex_init_,Vertex_copy_,Vertex_cmp_,Vertex_destroy_);
//type_register(Cell,Cell_init_,Cell_copy_,Cell_cmp_,Cell_destroy_);

}

void reset_c_prop(struct Mesh* mesh)
{
    for(auto cit=mesh->cells.begin();cit!=mesh->cells.end();cit++)
    {
	
    cit->second->prop=NULL;

    }
}
void reset_v_prop(struct Mesh* mesh)
{
    for(auto vit=mesh->vertices.begin();vit!=mesh->vertices.end();vit++)
    {
        vit->second->prop=NULL;    
    
    }

}
void reset_f_prop(struct Mesh* mesh)
{
    for(auto fit=mesh->faces.begin();fit!=mesh->faces.end();fit++)
    {
    
        fit->second->prop=NULL;
    
    }

}

