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
    if(mesh->simplex==1)
    {
        for(auto cit=mesh->cells.begin();cit!=mesh->cells.end();cit++)
        {
            
            for(int i=1;i<cit->second->vertices_size;i++)
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
    else
    {

     for(auto cit=mesh->cells.begin();cit!=mesh->cells.end();cit++)
        {
            
            for(int i=1;i<n;i++)
            {
                template_v* temp_v=(template_v*)cit->second->vertices[0],*temp_v1=(template_v*)cit->second->vertices[i];
                for(int j=0;j<n;j++)
                {
                    A.coeffRef(i-1,j)=temp_v1->point[j]-temp_v->point[j];
                
                
                }
            
            
            }

        double *nor=(double*)malloc(sizeof(double)*n);
    
        for(int i=0;i<n;i++)
        {
            temp_A=A.col(i);
            A.col(i)=A.col(0);
            nor[i]=-A.block(1,1,n-1,n-1).determinant();
            
            A.col(i)=temp_A;
        }
        nor[0]=-nor[0];

        cit->second->prop=(void*)nor;
    

    


        
        }
       
    
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
//
//
//
//find firstly
    int *temp_int=(int*)malloc(sizeof(int));
    *temp_int=1;
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
            Node* node1=(Node*)malloc(sizeof(Node));
            Node_init(node1);
            node1->Next=(void*)node;
            if(node!=NULL)
            {
                node->Prev=(void*)node1;
            }
            cit->second->prop=(void*)temp_int;
            node1->value=(void*)cit->second;
            node=node1;
            break;
        }
     

    }
    while(node->value!=NULL)
    {
        Node * temp_node=node_copy(node);
        free_node(node);
        node=(Node*)malloc(sizeof(Node));
        Node_init(node);
        for(Node node_it=*temp_node;*node_it!=NULL;node_it++)
        {
//

            for(iterator_v cv_it=mesh->cv_begin(mesh,*((template_c*)*node_it));cv_it!=mesh->cv_end(mesh,*((template_c*)*node_it));cv_it++)
            {
                for(iterator_c vc_it=mesh->vc_begin(mesh,*cv_it);vc_it!=mesh->vc_end(mesh,*cv_it);vc_it++)
                {
                    if(((*vc_it).prop)==temp_int)
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
                            Node* node1=(Node*)malloc(sizeof(Node));
                            Node_init(node1);
                            node1->Next=(void*)node;
                            if(node!=NULL)
                            {
                                node->Prev=(void*)node1;
                            }
                            node1->value=*(vc_it.node);

                            ((template_c*)(node1->value))->prop=(void*)temp_int;
                            node=node1;
            
                        }            
            //Node*node1=(Node*)malloc(sizeof(Node));
            //Node_init(node1);
                    }
                }
            }

        }
    }

/*
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
	Node* node1=(Node*)malloc(sizeof(Node));
	Node_init(node1);
        node1->Next=(void*)node;
	if(node!=NULL)
	{
	node->Prev=(void*)node1;
	}
	node1->value=(void*)cit->second;
	node=node1;
	}
	//

}
*/
    Node* node1=node;
    while(node!=NULL)
    {
	    mesh->delete_cell(mesh,*(template_c*)node->value,true);
	    node=(Node*)node->Next;
//delete_cell


    }
    free_node(node1);

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

for(int i=0;i<rows;i++)
{
free(M[i]);

}
free(M);
*/

}
#endif
#endif
