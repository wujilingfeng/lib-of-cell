#include<Mesh/Mesh.h>
bool operator==(const Node& node1,const Node& node2)
{

    return (node1.value==node2.value);

}
Node operator++(Node& node)
{
    if(node.Next==NULL)
    {
        Node node2;
        node=node2;
        return node2;
    }

    node=*((Node*)node.Next);
    return node;
}
Node operator++(Node &node,int)
{
    Node node1=node;
    if(node.Next==NULL)
    {
        Node node2;
        node=node2;
        return node1;
    }

    node=*((Node*)node.Next);
    return node1;
}
Node operator--(Node&node)
{
    if(node.Prev==NULL)
    {
        Node node2;
        node=node2;
        return node2;
    }

    node=*((Node*)node.Prev);
    return node;

}
Node operator--(Node&node,int)
{
    Node node1=node;
    if(node.Prev==NULL)
    {
        Node node2;
        node=node2;
        return node1;
    }

    node=*((Node*)node.Prev);
    return node1;


}
void* operator*(Node& node)
{
    return node.value;

}
std::map<int,template_f*>::iterator Mesh_faces_begin(struct Mesh* own)
{
    return own->faces.begin();

}
std::map<int,template_f*>::iterator Mesh_faces_end(struct Mesh* own)
{
    return own->faces.end();
}
std::map<int,template_v*>::iterator Mesh_vertices_begin(struct Mesh* own)
{
    return own->vertices.begin();

}
std::map<int,template_v*>::iterator Mesh_vertices_end(struct Mesh* own)
{
    return own->vertices.end();

}
std::map<int,template_c*>::iterator Mesh_cells_begin(struct Mesh* own)
{
    return own->cells.begin();
}
std::map<int,template_c*>::iterator Mesh_cells_end(struct Mesh* own)
{
    return own->cells.end();
}
iterator_v operator++(iterator_v& vv_)
{

    (vv_.i++);
    return vv_;
}
iterator_v operator++(iterator_v&vv_,int)
{
    iterator_v vv=vv_;
    vv_.i++;
    return vv;


}
template_v* quote(iterator_v &vv_)
{

return ((template_v*)vv_.value[vv_.i]);


}
template_v operator*(iterator_v &vv_)
{
    return *quote(vv_);

}
bool operator!=(const iterator_v&v_1,const iterator_v& v_2)
{
    if(v_1.value!=v_2.value)
    {
        return true;
    }
    if(v_1.i!=v_2.i)
    {
        return true;
    }
    return false;

}
iterator_f operator++(iterator_f& f_)
{
    f_.node--;
    return f_;

}
iterator_f operator++(iterator_f&f_,int)
{
    iterator_f f1=f_;
    f_.node--;
    return f1;

}
template_f* quote(iterator_f&f_)
{

    return ((template_f*)(*(f_.node)));

}
template_f operator*(iterator_f&f_)
{

    return *quote(f_);
}
bool operator!=(const iterator_f& f_1,const iterator_f& f_2)
{
    if(f_1.node.value!=f_2.node.value)
    {
        return true;
    }
    return false;
}
iterator_c operator++(iterator_c& c_)
{

    c_.node++;
    return c_;
}
iterator_c operator++(iterator_c &c_,int)
{
    iterator_c c_1=c_;
    c_.node++;
    return c_1;

}

template_c operator*(iterator_c&c_)
{

    return *quote(c_);
}
template_c* quote(iterator_c&c_)
{
    return (template_c*)(*(c_.node));

}
bool operator!=(const iterator_c& c_1,const iterator_c& c_2)
{
    if(c_1.node.value!=c_2.node.value)
    {

    return true;
    }
    return false;
}
iterator_v Mesh_fv_begin(struct Mesh* own,const template_f& f_)
{

    iterator_v it;
    it.value=f_.vertices;
    return it;

}

iterator_v Mesh_fv_end(struct Mesh* own,const template_f& f_)
{
    iterator_v it;
    it.value=f_.vertices;
    it.i=f_.vertices_size;
    return it;

}
iterator_v Mesh_hfv_begin(struct Mesh* own,template_hf *hf)
{
    iterator_v it;
    it.value=hf->vertices;
    return it;

}
iterator_v Mesh_hfv_end(struct Mesh* own,template_hf *hf)
{
    iterator_v it;
    it.value=hf->vertices;
    it.i=hf->vertices_size;

    return it;
}
iterator_v Mesh_cv_begin(struct Mesh* own,const template_c& c)
{
    iterator_v it;
    it.value=c.vertices;
    return it;
}
iterator_v Mesh_cv_end(struct Mesh* own,const template_c& c)
{
    iterator_v it;
    it.value=c.vertices;
    it.i=c.vertices_size;
    return it;
}


iterator_f Mesh_vf_begin(struct Mesh* own,const template_v& v)
{
    iterator_f iff;
    iff.node=*(node_reverse(v.faces));
    return iff;

}
iterator_f Mesh_vf_end(struct Mesh* own,const template_v& v)
{
    iterator_f iff;
    return iff;

}
iterator_f Mesh_chf_begin(struct Mesh* own,const template_c& c)
{

    iterator_f iff;

    iff.node=*(node_reverse(c.halffaces));
    return iff;

}
iterator_f Mesh_chf_end(struct Mesh* own,const template_c&c)
{
    iterator_f iff;
    return iff;

}
iterator_c Mesh_vc_begin(struct Mesh* own,const template_v&v)
{
    iterator_c it;
    it.node=*(v.cells);
    return it;

}
iterator_c Mesh_vc_end(struct Mesh* own,const template_v&v)
{

    iterator_c it;
    return it;

}
Node* Mesh_vv_begin(struct Mesh* own,const template_v&v)
{
    Node* node=NULL;
    for(iterator_f fit=Mesh_vf_begin(own,v);fit!=Mesh_vf_end(own,v);fit++)
    {
        for(auto vit=Mesh_fv_begin(own,*fit);vit!=Mesh_fv_end(own,*fit);vit++)
        {
            if((*vit).id!=v.id)
            {

                if(node_find(node,(void*)quote(vit))==NULL)
                {
                    node=node_overlying(node,(void*)quote(vit));
                }
            }

        }

    }
    return node;


}


