#include<tool/libcell_tools_view.h>
void get_data_from_1dim_cell(Mesh*m,float **v,unsigned int **e)
{
#ifdef MANIFOLD_REQUIRE
    if(m->dimension!=1)
    {
        printf("can't draw\n");
        return ;
    }
#endif
    if(*v!=NULL)
    {
        free(*v);
    }
    *v=(float*)malloc(sizeof(float)*m->num_v(m)*3);
    memset(*v,0,sizeof(float)*m->num_v(m)*3);
    if(*e!=NULL)
    {
        free(*e);
    }
    *e=(unsigned int*)malloc(sizeof(unsigned int)*m->num_c(m)*2);
    memset(*e,0,sizeof(unsigned int)*m->num_c(m)*2);
    int i=0;
    int* temp_v_id=(int*)malloc(sizeof(int)*m->num_v(m));
    for(auto iter=m->vertices.begin();iter!=m->vertices.end();iter++)
    {       
        for(int j=0;j<iter->second->point_size;j++)
        {
            (*v)[i*3+j]=iter->second->point[j];
        }
        temp_v_id[i]=i;
        iter->second->prop=(void*)(&temp_v_id[i]);
//       (*v)[i*3+2]=(float)temp_z/2.0;
 /*       if(iter->second->id==500)
        {
            (*v)[i*3+2]=0.6;
        }*/
        i++; 
    }
    i=0;
    for(auto iter=m->cells.begin();iter!=m->cells.end();iter++)
    {
     
        for(auto iter1=m->cv_begin(m,*(iter->second));iter1!=m->cv_end(m,*(iter->second));iter1++)
        {
            (*e)[i]=*((int*)((*iter1).prop));
            i++;
        }

    }
    free(temp_v_id);
    reset_v_prop(m);

}
//二维流形可视化
void get_data_from_2dim_cell(Mesh* m,float**v,unsigned int**f)
{
#ifdef MANIFOLD_REQUIRE
    if(m->dimension!=2)
    {
        printf("can't draw\n");
        return ;
    }
#endif
    //要重排vertices id
    if((*v)!=0)
    {
        free((*v));
    }
    *v=(float*)malloc(sizeof(float)*m->num_v(m)*3);
    memset(*v,0,sizeof(float)*m->num_v(m)*3);
    int f_size=0;
    for(auto iter=m->cells.begin();iter!=m->cells.end();iter++)
    {
        f_size+=((iter->second)->vertices_size+1);  
    }

	if((*f)!=0)
	{free((*f));
	}
    //int *temp_v_id=(int*)malloc(sizeof(int)*m->num_v(m));
    *f=(unsigned int*)malloc(sizeof(unsigned int)*f_size);
    memset(*f,0,sizeof(unsigned int)*f_size);
    int i=0;
    int* temp_v_id=(int*)malloc(sizeof(int)*m->num_v(m));
    for(auto iter=m->vertices.begin();iter!=m->vertices.end();iter++)
    {       
        for(int j=0;j<iter->second->point_size;j++)
        {
            (*v)[i*3+j]=iter->second->point[j];
        //    temp_z+=(*v)[i*3+j]*(*v)[i*3+j];
        }
        temp_v_id[i]=i;
        iter->second->prop=(void*)(&temp_v_id[i]);
//       (*v)[i*3+2]=(float)temp_z/2.0;
 /*       if(iter->second->id==500)
        {
            (*v)[i*3+2]=0.6;
        }*/
        i++; 
    }
    i=0;
    for(auto iter=m->cells.begin();iter!=m->cells.end();iter++)
    {
        (*f)[i]=iter->second->vertices_size;
        i++;
        for(auto iter1=m->cv_begin(m,*(iter->second));iter1!=m->cv_end(m,*(iter->second));iter1++)
        {
            (*f)[i]=*((int*)((*iter1).prop));
            i++;
        }

    }
    free(temp_v_id);
    reset_v_prop(m);
}
void get_data_from_cell(Mesh* m,float**v,unsigned int**f)
{
#ifdef MANIFOLD_REQUIRE
    if(m->dimension==1)
    {
        get_data_from_1dim_cell(m,v,f);
    }
    else if(m->dimension==2)
    {
        get_data_from_2dim_cell(m,v,f);
    }
#endif 

}
//get boundary data from 3-dim cell
void  get_data_from_3dim_cell(Mesh* m,float** Data,unsigned int** Data_index,unsigned int* Data_rows,unsigned int* Data_index_rows)
{
	m->external_cell_init_(m);
    int f_size=0;
    (*Data)=(float*)malloc(sizeof(float)*3*m->num_v(m));
    int i=0;
    for(auto iter=m->vertices.begin();iter!=m->vertices.end();iter++)
    {
        for(int j=0;j<iter->second->point_size;j++)
        {
            (*Data)[i*3+j]=iter->second->point[j];
        
        }
        i++;
    }
     
    for(Node* node=m->external_cell.halffaces;node!=0;node=(Node*)(node->Next))
    {
        
        f_size+=(((template_hf*)(node->value))->vertices_size+1);
         
    }
   // printf("f_size:%d\n",f_size);
    (*Data_index)=(unsigned int*)malloc(sizeof(unsigned int)*f_size);
    (*Data_index_rows)=node_size(m->external_cell.halffaces);
    (*Data_rows)=m->num_v(m);
    i=0;
    for(Node* node=m->external_cell.halffaces;node!=0;node=(Node*)(node->Next))
    {
        template_hf* hf=(template_hf*)(node->value);
        (*Data_index)[i]=hf->vertices_size;
        i++;
        for(auto iter=m->hfv_begin(m,*hf);iter!=m->hfv_end(m,*hf);iter++)
        {
            (*Data_index)[i]=(*iter).id;
            i++;
        }     
    }

}
