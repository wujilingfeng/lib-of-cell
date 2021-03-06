//#undef LibCell_IO
#include<Mesh_IO/Mesh_IO.h>
#include<string.h>
//#include<sys/sysinfo.h>
//num[3]
void _ReadArray_(template_m*m,double**V,int**F,int**C,int*num,int back_dim,int manifold_dim)
{
#ifdef MANIFOLD_REQUIRE
    m->dimension=manifold_dim;
#endif
	int n=back_dim;
    for(int i=0;i<num[0];i++)
    {
        template_v* v=m->create_vertex(m);
	    v->point_size=n;
        v->point=(double*)malloc(sizeof(double)*n);
        for(int j=0;j<n;j++)
	    {   
            v->point[j]=V[i][j];   
	    }
    }
    int cols;
	if(F==NULL||num[1]==0)
	{
		m->simplex=1;
        for(int i=0;i<num[2];i++)
        {    
            cols=C[i][0];
            template_v* temp_v[cols];
            for(int j=0;j<cols;j++)
	        {
                int id=C[i][j+1];
		        auto it=m->vertices.find(id);
		        template_v* v;
		        if(it!=m->vertices.end())
		        {
		            v=it->second;
		        }
		        else
                {
                    printf("can t find this vertex: %d\r\n",id);
		            return;
		        }
		        temp_v[j]=v;
	        }
	        m->create_cellv(m,temp_v,cols);

            
        }

	}
	else
	{
        m->simplex=0;
        for(int i=0;i<num[1];i++)
        {
            cols=F[i][0];
            template_v* temp_v[cols];
                
            for(int j=0;j<cols;j++)
            {
                int id=F[i][j+1];
                auto it=m->vertices.find(id);
                template_v* v;
                if(it!=m->vertices.end())
                {
                    v=it->second;
                    
                }
                else
                {
                    printf("can t find this vertex\r\n");
                    return ;
                    
                }
                temp_v[j]=v;
                    
                
                
            }
            template_f* temp_f=m->create_facev(m,temp_v,cols);
            m->create_halfface(m,temp_f,temp_v,cols); 
            
            
            
            
        }
        for(int i=0;i<num[2];i++)
        {
                cols=C[i][0];
                
                template_hf* temp_hf[cols];
                for(int j=0;j<cols;j++)
                {
                    int id=C[i][j+1];
                    auto it=m->halffaces.find(id);
                    template_hf * hf;
                    if(it!=m->halffaces.end())
                    {
                        hf=it->second;
                    }
                    else
                    {
                        printf("can t find this halfface\n");
                        return ;
                    
                    }
                
                    temp_hf[j]=hf;
                
                
                }
                m->create_cellf(m,temp_hf,cols);
        }

    
    }
}

void _ReadCell_(template_m*m,char const*filename)
{
#ifdef WIN32
    FILE *infile;
    fopen_s(&infile,filename,"r");
#else
    FILE *infile=fopen(filename,"r");
#endif
    if(!infile)
	{
	    printf("cant't open this file\r\n");
	    return;
	}
    fseek(infile,0,SEEK_SET);
    char off[20];
    fscanf(infile,"%s",off);
    if(strcmp("CELL",off)==0)
    {
        //printf("cell read\n");
        fscanf(infile,"%s",off);
        int n;
        fscanf(infile,"%d",&n);
        fscanf(infile,"%s",off);
        int manifold_dim;
        fscanf(infile,"%d",&manifold_dim);
#ifdef MANIFOLD_REQUIRE
        m->dimension=manifold_dim;
#endif
        fscanf(infile,"%s",off);
        int simplex;
        int num[3];
        fscanf(infile,"%d",&simplex);
        fscanf(infile,"%d %d %d",&num[0],&num[1],&num[2]);
        for(int i=0;i<num[0];i++)
        {
                template_v* v=m->create_vertex(m);
	            v->point_size=n;
                v->point=(double*)malloc(sizeof(double)*n);
                for(int j=0;j<n;j++)
	            {   
                    fscanf(infile,"%lf",&(v->point[j]));
	            }


        
        }
        if(simplex==1)
        {
            int cols=0,id=0;
            for(int i=0;i<num[2];i++)
            {
                fscanf(infile,"%d",&cols);
           
                template_v* temp_v[cols];
                for(int j=0;j<cols;j++)
	            {
                    fscanf(infile,"%d",&id);
		            auto it=m->vertices.find(id);
		            template_v* v;
		            if(it!=m->vertices.end())
		            {
		                v=it->second;
		            }
		            else
                    {
                        printf("can t find this vertex: %d\r\n",id);
		                return;
		            }
		            temp_v[j]=v;
	            }
	            m->create_cellv(m,temp_v,cols);

            
            }
            
        
        
        }
        else
        {   
		m->simplex=0;

//		printf("simplex:%d\n",simplex);
            int cols,id;
            for(int i=0;i<num[1];i++)
            {
                fscanf(infile,"%d",&cols);
                template_v* temp_v[cols];
                
                for(int j=0;j<cols;j++)
                {
                    fscanf(infile,"%d",&id);
                    auto it=m->vertices.find(id);
                    template_v* v;
                    if(it!=m->vertices.end())
                    {
                        v=it->second;
                    
                    }
                    else
                    {
                        printf("can t find this vertex\r\n");
                        return ;
                    
                    }
                    temp_v[j]=v;
                    
                
                
                }
                template_f* temp_f=m->create_facev(m,temp_v,cols);
                m->create_halfface(m,temp_f,temp_v,cols); 
            
            
            
            
            }
            for(int i=0;i<num[2];i++)
            {
                fscanf(infile,"%d",&cols);
                template_hf* temp_hf[cols];
                for(int j=0;j<cols;j++)
                {
                    fscanf(infile,"%d",&id);
                    auto it=m->halffaces.find(id);
                    template_hf * hf;
                    if(it!=m->halffaces.end())
                    {
                        hf=it->second;
                    }
                    else
                    {
                        printf("can t find this halfface\n");
                        return ;
                    
                    }
                
                    temp_hf[j]=hf;
                
                
                }
                m->create_cellf(m,temp_hf,cols);
            }
        }    
    }

}
void _WriteCell_(template_m*m,char const* filename)
{
#ifdef WIN32
    FILE *outfile;
    fopen_s(&outfile,filename,"w");
#else
    FILE *outfile=fopen(filename,"w");
#endif
   if(!outfile)
   {
        printf("cant open this file\n");
        return ;
   }
   fprintf(outfile,"CELL\n");
   int back_ground=m->vertices.begin()->second->point_size;
   fprintf(outfile,"background_dim= %d\n",back_ground);
   fprintf(outfile,"manifold_dim= %d\n",m->dimension);
   fprintf(outfile,"simplex= %d\n",m->simplex);
   int num[3];
   num[0]=m->num_v(m);
   num[1]=m->num_hf(m);
   num[2]=m->num_c(m);
   fprintf(outfile,"%d %d %d\n",num[0],num[1],num[2]);
    for(auto v_it=m->vertices.begin();v_it!=m->vertices.end();v_it++)
    {
        for(int j=0;j<back_ground;j++)
        {
            fprintf(outfile,"%lf ",v_it->second->point[j]);
        }
        fprintf(outfile,"\n");
    
    }
    for(auto f_it=m->halffaces.begin();f_it!=m->halffaces.end();f_it++)
    {
        fprintf(outfile,"%d ",f_it->second->vertices_size);
       for(int j=0;j<f_it->second->vertices_size;j++)
       {
           fprintf(outfile,"%d ",((template_v*)(f_it->second->vertices[j]))->id);
       
       
       }
       fprintf(outfile,"\n");
    
    
    }
    for(auto c_it=m->cells.begin();c_it!=m->cells.end();c_it++)
    {
        int temp_size=node_size(c_it->second->halffaces);
    
        fprintf(outfile,"%d ",temp_size);
        for(auto chf_it=m->chf_begin(m,*c_it->second);chf_it!=m->chf_end(m,*c_it->second);chf_it++)
        {
            fprintf(outfile,"%d ",(*chf_it).id);
        
        
        
        }
        fprintf(outfile,"\n");
    }



}
//只有off文件描述单形时才有效
void _ReadOff_(template_m *m,char const * filename, int n)
{
#ifdef WIN32
	FILE* infile;
	fopen_s(&infile,filename,"r");
#else
	FILE* infile=fopen(filename,"r");
#endif
    if(!infile)
	{
	    printf("cant't open this file\r\n");
	    return;
	}
    m->dimension=2;
	        
    //fseek(infile,0,SEEK_END);
    //int len=ftell(infile);
    //char*source=(char*)malloc(len+1);
    //fread(source,1,len,infile);
    //free(source);
    fseek(infile,0,SEEK_SET);
	char off[6];
	fscanf(infile,"%s",off);
    //printf("off\r\n");
    if(strcmp("OFF",off)==0)
    {
            
	    int num[3];
        if(fscanf(infile,"%d %d %d",&num[0],&num[1],&num[2])==3)
        {
	        int rows=0,cols=0;
	        while(rows<num[0]&&!feof(infile))
	        {
	            template_v* v=m->create_vertex(m);
	            v->point_size=n;
                v->point=(double*)malloc(sizeof(double)*n);
                for(int i=0;i<n;i++)
	            {   
                    fscanf(infile,"%lf",&(v->point[i]));
	            }
	   
	            rows++;
	        }
	   	    //printf("num c%d",m->num_c(m));
		    rows=0;

	        int id;
	        while(!feof(infile)&&rows<num[1])
	        {
		 //  printf("d");      
                fscanf(infile,"%d",&cols);
           
                template_v* temp_v[cols];
                for(int i=0;i<cols;i++)
	            {
                    fscanf(infile,"%d",&id);
		            auto it=m->vertices.find(id);
		            template_v* v;
		            if(it!=m->vertices.end())
		            {
		                v=it->second;
		            }
		            else{
                        printf("can t find this vertex\r\n");
		                return;
		                }
		            temp_v[i]=v;
	            }
	            m->create_cellv(m,temp_v,cols);
	/*   template_c* c=m->create_cell(m);
	  c->vertices=(void**)malloc(sizeof(void*)*cols);
c->vertices_size=cols;
	   for(int i=0;i<cols;i++)
	   {fscanf(infile,"%d",&id);
		   auto it=m->vertices.find(id);
		   template_v* v;
		   if(it!=m->vertices.end())
		{
		v=it->second;
		}
		   else{printf("can t find this vertex\r\n");
		   return;
		   }
		   temp_v[i]=v;
	c->vertices[i]=(void*)v; 
	   Node *node=(Node*)malloc(sizeof(Node));
	   node->Prev=NULL;
	   node->Next=(void*)v->cells;
	   if(v->cells!=NULL)
	   {
	   v->cells->Prev=(void*)node;
	   }
	   node->value=(void*)c;
	   v->cells=node;
	   }
#ifdef SIMPLEX_REQUIRE
for(int i=0;i<cols;i++)
{
template_f* f=m->create_face(m);
f->vertices=(void**)malloc(sizeof(void*)*(cols-1));
f->vertices_size=(cols-1);
int temp_i=0;
for(int j=0;j<cols;j++)
{if(j!=i)
{
f->vertices[temp_i]=(void*)temp_v[j];
Node* node1=(Node*)malloc(sizeof(Node));
node1->Prev=NULL;
node1->Next=(void*)temp_v[j]->faces;
if(temp_v[j]->faces!=NULL)
{temp_v[j]->faces->Prev=(void*)node1;
}
node1->value=(void*)f;
temp_v[j]->faces=node1;
temp_i++;
}
}
Node* node2=(Node*)malloc(sizeof(Node));
node2->Prev=NULL;
node2->Next=(void*)c->faces;
if(c->faces!=NULL)
{c->faces->Prev=(void*)node2;}
node2->value=(void*)f;
c->faces=node2;
f->cells[f->cells_size++]=(void*)c;
}
#endif*/
            rows++; 
	   }

	   //printf("%d\r\n",m->num_f(m));
	   }
           else
           {
	   
	   printf("this file is not complete\r\n"); 

	  return;
	   }
          }
        else
	{
	printf("this is not off\r\n");
	return;
	
	}


}
