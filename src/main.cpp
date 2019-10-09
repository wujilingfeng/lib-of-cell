//#include<Python.h>
//
//#include "Dense"

//#include<Mesh_viewer.h>
//
//#include<glad/glad.h>
//#include<GLFW/glfw3.h>
#include<Mesh_viewer.h>
#include<Mesh_IO.h>
#include<Algorithm.h>
#include<iostream>
int main()
{


    Mesh mesh;
    _ReadCell_(&mesh,"cube.cell");
   // _ReadOff_(&mesh,"cube_.off",3);
    int num_c=mesh.num_c(&mesh);
    printf("num_c : %d num_v : %d num_f: %d num_hf: %d\n",num_c,mesh.num_v(&mesh),mesh.num_f(&mesh),mesh.halfface_id);
    //set_cell_normal(&mesh);

    Eigen::MatrixXf V(mesh.num_v(&mesh),3);
    Eigen::MatrixXi F(mesh.num_c(&mesh)*2,3);
    int i=0;
    for(auto vit=mesh.vertices.begin();vit!=mesh.vertices.end();vit++)
    {
        for(int j=0;j<3;j++)
        {
        
        
            V.coeffRef(i,j)=vit->second->point[j];
        
        }

    
    i++;
    }
    i=0;
    
    for(auto cit=mesh.cells.begin();cit!=mesh.cells.end();cit++)
    {
        //printf("cit v size : %d\n",cit->second->vertices_size); 
        for(int j=1;j<cit->second->vertices_size-1;j++)
        {   
            F.coeffRef(i,0)=((template_v*)(cit->second->vertices[0]))->id;
            F.coeffRef(i,1)=((template_v*)(cit->second->vertices[j]))->id;
            F.coeffRef(i,2)=((template_v*)(cit->second->vertices[j+1]))->id;

            i++;

    
           // F.coeffRef(i,j)=((template_v*)(cit->second->vertices[j]))->id;    
        }


    }
    //reset_c_prop(&mesh);
     
//b=eyem();
    //sin(8);
    //Node node1,node2;
    //std::cout<<V<<std::endl;
    //std::cout<<F<<std::endl;
    //printf("%d %d\n",F.coeff(0,0),F.coeff(0,1));
    
    printf("d");
    draw_mesh(V,F);
    printf("d");
    return 0;
}
