#include<Mesh_view/Mesh_Viewer_data.h>
//glDeleteVertexArrays;
//glDeleteBuffers
void Mesh_viewer_world_registe1(Mesh_viewer_world*m,char**c,int size)
{
	for(int i=0;i<size;i++)
	{
		int species_id=m->species_id++;
		int le=strlen(c[i]);
		char *cp=(char*)malloc(sizeof(char)*(le+1));
		cp[le]='\0';
		strcpy(cp,c[i]);
		m->something_id[species_id]=0;
		m->species_name_registe[species_id]=cp;
		m->species[species_id]=NULL;
	}

}
Node* Mesh_viewer_world_registe(Mesh_viewer_world*m,char*c)
{
	if(c==0)
	{return 0;}
	if(c[0]=='\0')
	{return 0;}
	Node* re=0;
	int i=0,j=0;
	while(c[i]!='\0')
	{

		while(c[j]!=','&&c[j]!='\0')
		{
			//printf("%d ",j);
			j++;

		}
		char* temp_c=(char*)malloc(sizeof(char)*(j-i+1));
		temp_c[j-i]='\0';
		for(int k=0;k<j-i;k++)
		{
			temp_c[k]=c[i+k];

		}
		
		Node* id=Mesh_viewer_world_find_species(m,temp_c);
		if(id==0)
		{break;}
		else if(*((int*)(id->value))!=-1)
		{
			free(temp_c);
			re=node_overlying(re,id->value);
			

		}
		else
		{
			int species_id=m->species_id++;
			m->something_id[species_id]=0;
			m->species_name_registe[species_id]=temp_c;
			m->species[species_id]=NULL;
			int *temp_id=(int*)malloc(sizeof(int));
			*temp_id=species_id;
			re=node_overlying(re,(void*)temp_id);
			free(id->value);
		}
		free_node(id);
		if(c[j]=='\0')
		{
			break;
		}
		i=j+1;
		j=j+1;
	}
	printf("\n");
	for(auto it=m->species_name_registe.begin();it!=m->species_name_registe.end();it++)
	{
		printf("id:%d,name:%s   ",it->first,it->second);
	}
	printf("\n");
	return re;
}
void Mesh_viewer_world_init(Mesh_viewer_world*m)
{
	//m->things_id=0;
	//char str[]="points,edges,faces";
	m->species_id=0;
	char str[]="points,edges,faces";
	Mesh_viewer_world_registe(m,str);
}
void Mesh_view_something_init(Mesh_view_something*ms)
{
	//gldeletevertexarray
	//gldeletebuffer
	time_t timep;
    struct tm *p;
    time(&timep);
    p = localtime(&timep); //取得当地时间
  //  printf ("%d%d%d ", (1900+p->tm_year), (1+p->tm_mon), p->tm_mday);
 //   printf("%d:%d:%d\n", p->tm_hour, p->tm_min, p->tm_sec);
    ms->create_date=p->tm_sec+p->tm_min*100+p->tm_hour*10000+p->tm_mday*1000000+(1+p->tm_mon)*100000000;
   // printf("create_date:%d\n",ms->create_date);
	ms->name=NULL;
	ms->name_id=-1;
	ms->id=-1;
	//ms->create_date=-1;
	ms->disappear=1;
	ms->prop=NULL;
	ms->mesh=NULL;
	ms->history_avatar=NULL;
	ms->evolution=NULL;
}
Node* Mesh_viewer_world_find_species(Mesh_viewer_world*mw,char* c)
{
	if(c==0)
	{
		return 0;
	}
	if(c[0]=='\0')
	{return 0;}
	//int num=0;
	Node * re=0;
	int i=0,j=0;
	while(c[i]!='\0')
	{

		while(c[j]!=','&&c[j]!='\0')
		{
			//printf("%d ",j);
			j++;

		}
		char temp_c[j-i+1];
		//char* temp_c=(char*)malloc(sizeof(char)*(j-i+1));
		temp_c[j-i]='\0';
		for(int k=0;k<j-i;k++)
		{
			temp_c[k]=c[i+k];

		}
		int* id=(int *)malloc(sizeof(int));
		*id=-1;
		for(auto it=mw->species_name_registe.begin();it!=mw->species_name_registe.end();it++)
		{
			if(strcmp(temp_c,it->second)==0)
			{
				*id=it->first;
				break;

			}
		}
		re=node_overlying(re,(void*)id);
		
		if(c[j]=='\0')
		{
			break;
		}
		i=j+1;
		j=j+1;
	}
	
	return re;
}

Node* Mesh_viewer_world_create_something(struct Mesh_viewer_world*mw,char *c)
{
	Node* id_list=Mesh_viewer_world_registe(mw,c),*re=0;
	Node* iter_n=node_reverse(id_list);
	if(id_list==0)
	{return 0;}
	int i=0,j=0;
	while(c[i]!='\0')
	{

		while(c[j]!=','&&c[j]!='\0')
		{
			//printf("%d ",j);
			j++;

		}
		char* temp_c=(char*)malloc(sizeof(char)*(j-i+1));
		temp_c[j-i]='\0';
		for(int k=0;k<j-i;k++)
		{
			temp_c[k]=c[i+k];

		}
		Mesh_view_something* ms=(Mesh_view_something*)malloc(sizeof(Mesh_view_something));
		Mesh_view_something_init(ms);
		ms->name=temp_c;
		ms->name_id=*((int*)iter_n->value);
		free(iter_n->value);
		ms->id=mw->something_id[ms->name_id]++;
		re=node_overlying(re,(void*)ms);
		if(c[j]=='\0')
		{
			break;
		}
		iter_n=(Node*)iter_n->Prev;
		
		i=j+1;
		j=j+1;
	}
	free_node(id_list);

	Node* temp_node=Mesh_viewer_from_something_evolute(re);
	free_node(temp_node);
	return re;

}
Node* Mesh_viewer_from_something_evolute(Node*lis)
{
	Node* re=0;
	if(lis==0)
	{
		return re;
	}
	if(lis->value==0)
	{
		return re;
	}
	Node* iter=lis;
	while(iter!=0)
	{
		Mesh_view_something* ms=(Mesh_view_something*)iter->value;
		void *value=0;
		if(strcmp(ms->name,"points")==0)
		{
			Mesh_viewer_points* temp_e=(Mesh_viewer_points*)malloc(sizeof(Mesh_viewer_points));
			value=(void*)temp_e;
		}
		else if(strcmp(ms->name,"edges")==0)
		{
			Mesh_viewer_edges* temp_e=(Mesh_viewer_edges*)malloc(sizeof(Mesh_viewer_edges));
			value=(void*)temp_e;

		}
		else if(strcmp(ms->name,"faces")==0)
		{

			Mesh_viewer_faces* temp_e=(Mesh_viewer_faces*)malloc(sizeof(Mesh_viewer_faces));
			value=(void*)temp_e;
		}
		ms->evolution=value;
		re=node_overlying(re,value);
		iter=(Node*)iter->Next;
	}
	return re;
}
void Mesh_viewer_edges_init(struct Mesh_viewer_edges* me)
{


}