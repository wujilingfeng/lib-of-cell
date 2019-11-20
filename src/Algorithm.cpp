#include<Algorithm.h>

//#include<Cell_Traits.h>
double  factorial(int n)
{
	int result=1;
    for(int i=2;i<=n;i++)
    {
        result=result*i;
    }
    return (double)result;
}
//rows代表点数，cols代表背景空间，比如3,7表示7维背景空间下三角形(单形))
double area_simplex(double**M,int rows,int cols)
{
	//rows respect point size
    if(rows>(cols+1))
    {
	    printf("points are too much\r\n");
        return 0;
    }
    Eigen::MatrixXd A(rows-1,rows-1);
    for(int i=0;i<(rows-1);i++)
    {
        for(int j=0;j<cols;j++)
        {
            A.coeffRef(i,j)=M[i][j]-M[rows-1][j];

        }
    }
    return sqrt((A*A.transpose()).determinant())/factorial(rows-1);
}
//rows代表点数，cols代表背景空间
double ori_area_simplex(double ** M,int rows,int cols)
{
    if((rows-1)!=cols)
    {
        printf("rows is not corresponse to cols\r\n");
        return 0;
    }
    Eigen::MatrixXd A(rows,rows);
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<rows;j++)
        {

            if(j!=0)
            {
                A.coeffRef(i,j)=M[i][j-1];
            }
            else
            {
                A.coeffRef(i,j)=1;
            }
        }
    }
    return A.determinant()/factorial(rows-1);

}
Eigen::MatrixXd orthogonal_complementation(Eigen::MatrixXd A)
{
    //Eigen::EigenSolver<Eigen::MatrixXd> egs(A);
    //Eigen::LLT<Eigen::MatrixXd> llt;
    Eigen::FullPivLU<Eigen::MatrixXd> lu_decomp(A);
    Eigen::MatrixXd k=lu_decomp.kernel();
   //lu_decomp.image(A) 
    //std::cout<<A.lu().matrixLU();

    return k;


}

void set_cell_normal(template_m*mesh)
{
    Eigen::MatrixXd A;

    Eigen::VectorXd temp_A;
    int n=(mesh->vertices.begin())->second->point_size;
    A.resize(n,n);
    A.setZero();
    
    
    for(auto cit=mesh->cells.begin();cit!=mesh->cells.end();cit++)
    {
        int length=0;    
        if(mesh->simplex==1)
        {
            length=cit->second->vertices_size;
        }
        else
        {
            length=n;
        
        }
        for(int i=1;i<length;i++)
        {
            template_v* temp_v=(template_v*)cit->second->vertices[0],*temp_v1=(template_v*)cit->second->vertices[i];
            for(int j=0;j<n;j++)
            {
                A.coeffRef(i-1,j)=temp_v1->point[j]-temp_v->point[j];
                
                
            }
            
            
        } 
        double *nor=(double*)malloc(sizeof(double)*n),sum=0;
        //Eigen::MatrixXd k=A.adjoint();
        //Eigen::MatrixXd temp_A(n-1,n-1);
        for(int i=0;i<n;i++)
        {
            temp_A=A.col(i);
            A.col(i)=A.col(0);
            nor[i]=-A.block(0,1,n-1,n-1).determinant();
            A.col(i)=temp_A;
            sum+=nor[i]*A.coeff(0,i);
            
           // printf("%lf  ",nor[i]);
        }
       // printf("sum:%lf\n",sum);
       // printf("\n");
        nor[0]=-nor[0];
        cit->second->prop=(void*)nor;
    }

}

#ifdef SIMPLEX_REQUIRE
#ifdef MANIFOLD_REQUIRE
void increasing_convex_hull(template_m* mesh,template_v* v)
{
//template_v*v=mesh->create_vertex();

	int rows=v->point_size+1,cols=v->point_size;
	double **M=(double**)malloc(sizeof(double*)*rows);
	for(int i=0;i<rows;i++)
	{
	    M[i]=(double*)malloc(sizeof(double)*cols);	
	}
	for(int j=0;j<cols;j++)
	{
	    M[0][j]=v->point[j];
	
	}
    Node* node=(Node*)malloc(sizeof(Node)),*node2=(Node*)malloc(sizeof(Node));
    
    Node_init(node);
    Node_init(node2);
//find first
    int *temp_int=(int*)malloc(sizeof(int)),*temp_int1=(int*)malloc(sizeof(int));
    *temp_int=1;*temp_int1=0;
    for(auto cit=mesh->cells.begin();cit!=mesh->cells.end();cit++)
    {
        for(int i=0;i<rows-1;i++)
	    {
	        for(int j=0;j<cols;j++)
	        {
	
                M[i+1][j]=((template_v*)(cit->second->vertices[i]))->point[j];	
		
	
	        }
	    }
       	if(ori_area_simplex(M,rows,cols)<0)
        {
            node=node_overlying(node,(void*)cit->second);
            cit->second->prop=(void*)temp_int;
            node2=node_overlying(node2,(void*)cit->second);
            break;
        }
        else
        {
            cit->second->prop=(void*)temp_int1;
        }
     

    }
    //广度优先
    while(node->value!=NULL)
    {
        Node * temp_node=node_copy(node);
        free_node(node);
        node=(Node*)malloc(sizeof(Node));
        Node_init(node);
        for(Node node_it=*temp_node;*node_it!=NULL;node_it++)
        {
            for(iterator_v cv_it=mesh->cv_begin(mesh,*((template_c*)*node_it));cv_it!=mesh->cv_end(mesh,*((template_c*)*node_it));cv_it++)
            {
                for(iterator_c vc_it=mesh->vc_begin(mesh,*cv_it);vc_it!=mesh->vc_end(mesh,*cv_it);vc_it++)
                {
                    if(((*vc_it).prop)!=NULL)
                    {
                        continue;
                    }
                    else
                    {
            
                        for(int i=0;i<rows-1;i++)
	                    {
	                        for(int j=0;j<cols;j++)
	                        {
	
                                M[i+1][j]=((template_v*)((*vc_it).vertices[i]))->point[j];	
		
	
	                        }
	                    }
       	                if(ori_area_simplex(M,rows,cols)<0)
                        {
                            node=node_overlying(node,*(vc_it.node));
                            node2=node_overlying(node2,*(vc_it.node)); 
                            (quote(vc_it))->prop=(void*)temp_int;
                        
            
                        }
                        else
                        {
                            quote(vc_it)->prop=(void*)temp_int1;
                        
                        }

                    }
                }
            }

        }
        free_node(temp_node);
    }
    Node *node1=node2;
    /*while(node2->value!=NULL)
    {
	    mesh->delete_cell(mesh,*(template_c*)node->value,true);
	    node=(Node*)node->Next;
//delete_cell
    }*/
    free_node(node1);
    for(auto cit=mesh->cells.begin();cit!=mesh->cells.end();cit++)
    {
        if((cit->second->prop)==(void*)temp_int)
        {
        
            mesh->delete_cell(mesh,*(cit->second),true); 
        }
        else
        {
        } 
        (cit->second->prop)=NULL;
    
    }
    mesh->external_cell_init_(mesh);
   template_v* temp_v[cols];
   temp_v[0]=v;
    for(auto hfit=*mesh->external_cell.halffaces;*hfit!=NULL;hfit++)
    {

        
        for(int i=0;i<((template_hf*)(*hfit))->vertices_size;i++)
        {
            temp_v[i+1]=(template_v*)((template_hf*)(*hfit))->vertices[i];
        }
        mesh->create_cellv(mesh,temp_v,cols);
    
    
    }
//node1=m.node_of_boundary_face(&m,)
/*for(auto fit=mesh->faces.begin();fit!=mesh->faces.end();fit++)
{
if(mesh->face_is_boundary(mesh,*fit->second))
{
node1=mesh->node_of_boundary_face(mesh,*fit->second);
break;
}

}
node=node1;
template_c *c=NULL;
template_f *f=NULL;
while(node!=NULL)
{
f=(template_f*)node->value;
if(f->cells[0]!=NULL)
{
//c=

}
    else
    {

    }
node=(Node*)node->Next;
}
*/
    for(int i=0;i<rows;i++)
    {
        free(M[i]);
    }
    free(M);

    free(temp_int);
    free(temp_int1);
}
void  from_v_createconvex(template_m* mesh,double** VV,int rows,int cols)
{
    mesh->simplex=1;
    for(int i=0;i<cols+1;i++)
    {
        mesh->create_vertexv(mesh,VV[i],cols);

    }
    int index[cols+1];
    for(int i=0;i<cols+1;i++)
    {
        index[i]=i;
    }
    if(ori_area_simplex(VV,cols+1,cols)<0)
    {
        index[0]=1;
        index[1]=0;
   
    }
    for(int i=0;i<cols+1;i++)
    {
        int k=0;
        template_v *temp_v[cols];
        for(int j=0;j<cols+1;j++)
        {
            if(j!=i)
            {
                temp_v[k]=mesh->vertices.find(index[j])->second;
                k++;
            }

        }
        if(i%2!=0)
        {
            template_v* temp_v1=temp_v[0];
            temp_v[0]=temp_v[1];
            temp_v[1]=temp_v1;
        }
        mesh->create_cellv(mesh,temp_v,cols);
    }
    for(int i=cols+1;i<rows;i++)
    {
        template_v* v=mesh->create_vertexv(mesh,VV[i],cols);
        increasing_convex_hull(mesh,v);
    
    }
}
 
#endif
#endif
