//#include<Python.h>
//#include "Dense"
#include<Mesh_view/Mesh_viewer.h>
#include<Mesh_view/Mesh_Viewer_data.h>
#include<Mesh_IO/Mesh_IO.h>
#include<Algorithm.h>
//#include<iostream>
#include<tool/tools_view.h>
#include<tool/tools_algrithm.h>

void libo_test(struct Mesh* mesh,template_c* c,double* p)
{
    if(c==NULL)
    {
    
        return ;
    }
    int size=c->vertices_size,p_size=((template_v*)c->vertices[0])->point_size;
    if(size!=4)
    {
        printf("this cell is not fit to this algrithm\n");
    
    }
    for(int j=0;j<p_size;j++)
    {
            p[j]=0;    
        
    }


    for(int i=0;i<size;i++)
    {
        for(int j=0;j<p_size;j++)
        {
            p[j]+=(((template_v*)c->vertices[i])->point[j])/size;
        
        }
    }
    template_v* v1=Mesh_create_vertexv(mesh,p,p_size),*v0=NULL;
    Node* node_v=NULL;
    iterator_v v_it=mesh->cv_begin(mesh,*c),v_it1;
    v_it++;
    for(v_it1=mesh->cv_begin(mesh,*c);v_it!=mesh->cv_end(mesh,*c);v_it++)
    {

        for(int j=0;j<p_size;j++)
        {
           p[j]=((*v_it1).point[j]+(*v_it).point[j])/2; 
        
        }
        v0=Mesh_create_vertexv(mesh,p,p_size);
        node_v=node_overlying(node_v,(void*)v0);
   //     printf("%d\n",v0->id);
        node_v=node_overlying(node_v,(void*)quote(v_it));
 
        v_it1++;
    
    }
    v_it=mesh->cv_begin(mesh,*c);
    for(int j=0;j<p_size;j++)
    {
        p[j]=((*v_it1).point[j]+(*v_it).point[j])/2; 
        
    }
    v0=Mesh_create_vertexv(mesh,p,p_size);
    node_v=node_overlying(node_v,(void*)v0);
    node_v=node_overlying(node_v,(void*)quote(v_it));
    node_v=node_reverse(node_v);
    Node n_it=*node_v;
    for(int i=0;i<4;i++)
    {
        printf("%d %d ",v1->id,((template_v*)(*n_it))->id);
        n_it--;
        printf("%d ", ((template_v*)(*n_it))->id);
        n_it--;
        if((*n_it)==NULL)
        {
           n_it=*node_v; 
        }
        printf("%d ", ((template_v*)(*n_it))->id);
    printf("\n");                             


    }


    /*for(Node n_it=*node_v;*n_it!=NULL;n_it++)
    {
        printf("f");
    }
    */
   
}
void divi()
{
    Mesh mesh;
    _ReadCell_(&mesh,"cube.cell");
   _WriteCell_(&mesh,"ouffi.cell"); 
    auto c_it=mesh.cells.begin();
    template_c* c=c_it->second;
    int p_size=((template_v*)c->vertices[0])->point_size;
    double p[p_size];

    for(;c_it!=mesh.cells.end();c_it++)
    {
        c=c_it->second;

        libo_test(&mesh,c,p);
        
    }
   for(auto vit=mesh.vertices.begin();vit!=mesh.vertices.end();vit++)
    {

        for(int j=0;j<vit->second->point_size;j++)
        {
            printf("%lf ",vit->second->point[j]);     
    
        }
        printf("\n");
    } 
}
void test_mesh_viewer_data()
{
    Mesh_viewer_world m_world;
    Mesh_viewer_world_init(&m_world); 
    printf("species id:%d\n",m_world.species_id);
    Node* node=Mesh_viewer_world_create_something(&m_world,"points");
     printf("species id:%d\n",m_world.species_id);
     if(node==0)
     {
        printf("huaile\n");
     }
    int id=((Mesh_view_something*)node->value)->name_id;
    printf("species id:%d\n",m_world.species_id);
    Node* node1=Mesh_viewer_world_find_species(&m_world,"points");
   // id=2;
    printf("points id:%d %d\n",id,*((int*)(node1->value)));
    id=((Mesh_view_something*)node->value)->id;
    printf("ms id:%d %d\n",id,m_world.something_id[*((int*)(node1->value))]);
    //Mesh_view_something ms;
    //Mesh_view_something_init(&ms);
   
    


}

void test()
{
    /*
    for(int i=0;i<20;i++)
    {
        Mesh mesh1;
        _ReadCell_(&mesh1,"face.cell");

    
    }*/
     
     /* char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep); //取得当地时间
    printf ("%d%d%d ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
    printf("%s%d:%d:%d\n", wday[p->tm_wday], p->tm_hour, p->tm_min, p->tm_sec);
*/
    test_mesh_viewer_data();
       
    Mesh mesh;
    _ReadCell_(&mesh,"cube.cell");
   // _ReadOff_(&mesh,"cube_.off",3);
    int num_c=mesh.num_c(&mesh);
    printf("num_c : %d num_v : %d num_f: %d num_hf: %d\n",num_c,mesh.num_v(&mesh)*2,mesh.num_f(&mesh),mesh.halfface_id);

    double temp_p[3]={0,0,0};
    //Mesh_division_face(&mesh,mesh.faces[0],temp_p);

    //set_cell_normal(&mesh);
/*    for(auto cit=mesh.cells.begin();cit!=mesh.cells.end();cit++)
    {
        for(auto cvit=mesh.cv_begin(&mesh,*cit->second);cvit!=mesh.cv_end(&mesh,*cit->second);cvit++)
        {
            printf("%d ",quote(cvit)->id);
        }
        printf("\n");
    
    }*/
/*    for(auto fit=mesh.faces.begin();fit!=mesh.faces.end();fit++)
    {
        if(mesh.face_is_boundary(&mesh,fit->second))
        {
            printf("fid: %d\n",fit->second->id);
            for(auto fvit=mesh.fv_begin(&mesh,*fit->second);fvit!=mesh.fv_end(&mesh,*fit->second);fvit++)
            {
                printf("%d ",quote(fvit)->id);       
            }
            printf("\n");
        
        } 
    }*/
    /*for(auto hf_it=mesh.halffaces.begin();hf_it!=mesh.halffaces.end();hf_it++)
    {
        for(int j=0;j<hf_it->second->vertices_size;j++)
        {
            printf("%d ",((template_v*)(hf_it->second->vertices[j]))->id);

        }
        printf("\n");

    }*/
    mesh.external_cell_init_(&mesh);
    
   
    Eigen::MatrixXf V(mesh.num_v(&mesh),3);
    Eigen::MatrixXi F(mesh.num_c(&mesh),3);
    Eigen::MatrixXi E;
    m_v_data.F_V=node_overlying(m_v_data.F_V,(void*)(&V));
    m_v_data.F_F=node_overlying(m_v_data.F_F,(void*)(&F));
   // m_v_data.E_V=node_overlying(m_v_data.E_V,(void*)(&V));
  //  m_v_data.E_E=node_overlying(m_v_data.E_E,(void*)(&E));
    // node_overlying(m_v_data.F_F,(void*)(&F));
    
    set_MatrixV_F(&mesh,&V,&F);
  
   // set_MatrixE(&mesh,&E);
  

    show();


}
void testreadpixel()
{
   for(int k=2;k<8;k++)
   {
       for(int j=1;j<k;j++)
       {
       
            for(int i=0;i<j;i++)
            {
                printf("%d %d %d\n",i,j,k);
            }
       
       }
   
   }
       //glReadPixels(globalinfo.mouse_coord[0],y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,readpixelcolor);
}
int main()
{
    int rows=8,cols=3;
    double temp_V[24]={0,0,-0.5,1,0,-0.5,0,1,-0.5,0,0,1,1,1,-0.5,1,0,1,0,1,1,1,1,1};
    double **V=(double**)malloc(sizeof(double*)*rows);
    for(int i=0;i<rows;i++)
    {
        V[i]=(double*)malloc(sizeof(double)*cols);
    }
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
        //V[i][j]=1;
            V[i][j]=temp_V[cols*i+j];
       // printf("%lf  ",temp_V[cols*i+j]);
        }

    }
    //printf("te:%d\n",te.rows());
    //Eigen::MatrixXf te;
    //te.resize(0,0);
    printf("\n");
    //int te[0]; 
    unsigned char a=255;
    printf("ttest:%d\n",a/3);
 //   divi();
    //Mesh mesh;
    //_ReadCell_(&mesh,"bunny.cell");

    //printf("num_c : %d num_v : %d num_f: %d num_hf: %d\n",mesh.num_c(&mesh),mesh.num_v(&mesh),mesh.num_f(&mesh),mesh.halfface_id);
    //test();
    /*Mesh mesh;
    from_v_createconvex(&mesh,V,rows,cols); 
//test1(V,rows,cols);
    printf("num_c : %d num_v : %d num_f: %d num_hf: %d\n",mesh.num_c(&mesh),mesh.num_v(&mesh),mesh.num_f(&mesh),mesh.halfface_id);

    Eigen::MatrixXf VV;
    Eigen::MatrixXi F;
    Eigen::MatrixXi E;

    m_v_data.F_V=node_overlying(m_v_data.F_V,(void*)(&VV));
    m_v_data.F_F=node_overlying(m_v_data.F_F,(void*)(&F));
    m_v_data.E_V=node_overlying(m_v_data.E_V,(void*)(&VV));
    m_v_data.E_E=node_overlying(m_v_data.E_E,(void*)(&E));
    set_MatrixV_F(&mesh,&VV,&F);

    set_MatrixE(&mesh,&E);
    testreadpixel();
//printf("size %d %dsize\n",c,sizeof(GLbyte));
    show();
*/

    test();

    return 0;
}
