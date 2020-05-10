#include<stdio.h>
#include<Mesh/Mesh_Frame.h>
#include<Mesh/lib_cell_Iterator.h>
#include<Mesh_IO/Mesh_IO.h>
//#include<Algorithm/Algorithm1.h>
#include<Algorithm/Algorithm2.h>
#include<tool/libcell_tools_view.h>
void test_delauny()
{
    srand((unsigned)time(0));
    Mesh mesh;
    Mesh_init(&mesh);
    double **v=(double**)malloc(sizeof(double*)*2000);
    for(int i=0;i<2000;i++)
    {
        v[i]=(double*)malloc(sizeof(double)*3);
    }
    for(int i=0;i<700;i++)
    {
        double r=1,delta=(rand()%2000)/1000.0-1,theta=(rand()%1000)/1000.0;
        //theta=0.5;
        v[i][0]=r*sin(theta*M_PI)*cos(delta*M_PI);
        v[i][1]=r*sin(theta*M_PI)*sin(delta*M_PI);
        v[i][2]=r*cos(theta*M_PI); 
    }

    for(int i=700;i<2000;i++)
    {
        double r=(rand()%1000)/1000.0,delta=(rand()%2000)/1000.0-1,theta=(rand()%1000)/1000.0;
        //theta=0.5;
        v[i][0]=r*sin(theta*M_PI)*cos(delta*M_PI);
        v[i][1]=r*sin(theta*M_PI)*sin(delta*M_PI);
        v[i][2]=r*cos(theta*M_PI);
          
    }
    Tensors_Algebra_System*tas=(Tensors_Algebra_System*)malloc(sizeof(Tensors_Algebra_System));
    Tensors_Algebra_System_mpf_init(tas,4);
    Tensor*t=tas->T_create();
    int ids[3]={0,1,2};
    t->insert(tas->as,t,ids,3,tas->copy_from_double(1));
    tensor_mpf_print_self(t);
    //convex_subdivision(tas,t,&mesh,v,1110,2);
    if(!delauny_subdivision(tas,t,&mesh,v,2000,3))
    {
        printf("liboodfsdferro\n");
    }
    //from_v_createconvex(tas,t,&mesh,v,1200,3);

    //_WriteCell_(&mesh,"surface.cell");
    //mesh.printself(&mesh);
    //要记得删除非流形点
    Node *nmv=mesh.non_manifold_vertices(&mesh);
    for(auto nit=nmv;nit!=NULL;nit=(Node*)(nit->Next))
    {
        mesh.delete_vertex(&mesh,*((template_v*)(nit->value)),true);
    }
    free_node(nmv);
    _WriteCell_(&mesh,"delauny_subdivision3.cell");
    Tensors_Algebra_System_free(tas);
    Mesh_free(&mesh);
/*    from_v_createdelauny_simplex(&mesh,v,2000,3);
    for(auto it=mesh.vertices.begin();it!=mesh.vertices.end();it++)
    {
        it->second->point_size--; 
    }

    Node*re=mesh.isolate_vertices(&mesh);
    Node* n_it=re;
    while(re!=NULL)
    {
        mesh.delete_vertex(&mesh,*((template_v*)(re->value)),true);
        re=(Node*)(re->Next);
    }
    free_node(n_it);
    _WriteCell_(&mesh,"delauny_sphere2.cell");
    
    Mesh_free(&mesh);
*/
    //Mesh_viewer_world mw;
    //Mesh_viewer_world_init(&mw);
    /*char ch[]="faces";
    Node* n=mw.create_something(&mw,ch);
    Mesh_viewer_something*ms=(Mesh_viewer_something*)(n->value);
    Mesh_viewer_faces *mf=(Mesh_viewer_faces*)(ms->evolution);
    mf->color_rows=mesh.num_v(&mesh);
    mf->random_color(mf);
    //mf->normal_rows=mesh.num
    get_data_from_3dim_cell(&mesh,&(mf->Data),&(mf->Data_index),&(mf->Data_rows),&(mf->Data_index_rows));
    mf->normal_rows=mf->Data_rows;
*/
    /*char sp_name[]="faces";
    Node* n=mw.create_something(&mw,sp_name);
    auto ms=(Mesh_viewer_something*)(n->value);
    auto mf=(Mesh_viewer_faces*)(ms->evolution);
    mf->color_rows=mesh.num_c(&mesh);
    mf->random_color(mf);
//    get_data_from_2dim_cell(&mesh,&(mf->Data),&(mf->Data_index));
    mf->normal_rows=mesh.num_c(&mesh);
    mf->Data_rows=mesh.num_v(&mesh);
    mf->Data_index_rows=mesh.num_c(&mesh);
    free_node(n);*/
    //test_camera_and_intera(&mw);
    //Mesh_viewer_opengl_Interpreter moi;
    //Mesh_viewer_opengl_Interpreter_init(&moi);
    //moi.world=&mw;
    //moi.routine_show(&moi);
    
}
void test_area()
{
    Mesh mesh;
    Mesh_init(&mesh);
    double **v=(double**)malloc(sizeof(double*)*8);
    for(int i=0;i<8;i++)
    {
        v[i]=(double*)malloc(sizeof(double)*3);
    }
    v[0][0]=1;v[0][1]=-1;v[0][2]=-1;
    v[1][0]=1;v[1][1]=-1;v[1][2]=1;
    v[2][0]=1;v[2][1]=1;v[2][2]=1;
    v[3][0]=1;v[3][1]=1;v[3][2]=-1;
    v[4][0]=-1;v[4][1]=-1;v[4][2]=-1;
    v[5][0]=-1;v[5][1]=-1;v[5][2]=1;
    v[6][0]=-1;v[6][1]=1;v[6][2]=1;
    v[7][0]=-1;v[7][1]=1;v[7][2]=-1;

    Tensors_Algebra_System*tas=(Tensors_Algebra_System*)malloc(sizeof(Tensors_Algebra_System));
    Tensors_Algebra_System_mpf_init(tas,4);
    Tensor*t=tas->T_create();
    int ids[3]={0,1,2};
    t->insert(tas->as,t,ids,2,tas->copy_from_double(1));
    tensor_mpf_print_self(t);
    convex_subdivision(tas,t,&mesh,v,4,3);

    auto re=compute_convex_area(tas,t,v,4,3);
    gmp_printf("re:%.Ff\n",re);

    
}
int main(int argc,char**argv)
{
    mpf_set_default_prec(200);

    Mesh mesh,mesh1;
    Mesh_init(&mesh);Mesh_init(&mesh1);
   /* FILE* infile=fopen("bone_scan1.off","r");
    fseek(infile,0,SEEK_END);//定位到离文末0字节处
    int len=ftell(infile);//当前处离文首多少字节
    fseek(infile,0,SEEK_SET);//定位到文首
    char* source=(char*)malloc(len+1);
    fread(source,1,len,infile);
    fclose(infile);
    source[len]=0;*/
//    _ReadOff_(&mesh1,"bone_scan1.off",3);
    //_ReadOff_(&mesh,"cube.off",3);
    _ReadCell_(&mesh,"cube.cell");
    template_v v0=mesh.get_vertex(&mesh,0);
    template_f f0=mesh.get_face(&mesh,0);
    //mesh.delete_vertex(&mesh,v0,true);
    mesh.delete_face(&mesh,f0,true);
    double **M=(double**)malloc(sizeof(double*)*3);

    for(int i=0;i<3;i++)
    {
        M[i]=(double*)malloc(sizeof(double)*3);
    }
    M[0][0]=21.0;M[0][1]=-2.012;M[0][2]=-212.2102;
    M[1][0]=1.001;M[1][1]=-0.012;M[1][2]=-2.2102;
    M[2][0]=2.9;M[2][1]=92.02;M[2][2]=12.2102;
    Tensors_Algebra_System*tas=(Tensors_Algebra_System*)malloc(sizeof(Tensors_Algebra_System));
    Tensors_Algebra_System_mpf_init(tas,3);
    __mpf_struct* re=area_simplex(tas,M,3,3);
    gmp_printf("re:%.Ff\n",re);
    test_area();
    test_delauny();
    //printf("%f\n",area_simplex_double(M,3,3));
    //Tensor*t=Anti_tensor_mpf_from_v(tas,M,3,3);
    //tensor_mpf_print_self(t);
    //gmp_printf("%.Ff\n",(__mpf_struct*)tas->T_norm(tas,t));
     
   // mesh.printself(&mesh);
 //   printf("v:%d,f:%d ,c:%d\n",mesh1.num_v(&mesh1),mesh1.num_f(&mesh1),mesh1.num_c(&mesh1));

   /* for(auto it=mesh.cells.begin();it!=mesh.cells.end();it++)
    {
        //printf("d");
    
    }*/
   // _ReadCell_(&mesh,"hand.cell");

    printf("end\n");
    return 0;
}
