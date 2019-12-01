#include<Mesh_view/Mesh_Viewer_data.h>
void Mesh_viewer_world_registe1(Mesh_viewer_world*m,char**c,int size)
{
	for(int i=0;i<size;i++)
	{
		int species_id=m->species_id++;
		int le=strlen(c[i]);
		char *cp=(char*)malloc(sizeof(char)*(le+1));
		cp[le]='\0';
		strcpy(cp,c[i]);
		m->something_name_id[species_id]=0;
		m->species_name_registe[species_id]=cp;
		m->species[species_id]=NULL;

	}

}
void Mesh_viewer_world_registe(Mesh_viewer_world*m,char*c)
{
	int i=0;j=0;
	while(c[i]!='\0')
	{

		while(c[j]!=','||c[j]!='\0')
		{
			j++;

		}
		char* temp_c=(char*)malloc(sizeof(char)*(j-i+1));
		temp_c[j-i]='\0';
		for(int k=0;k<j-i;k++)
		{
			temp_c[k]=c[i+k];

		}
		int species_id=m->species_id++;
		m->something_name_id[species_id]=0;
		m->species_name_registe[species_id]=temp_c;
		m->species[species_id]=NULL;
		if(c[j]=='\0')
		{
			break;
		}
		i=j+1;
		j=j+1;
	}

}
void Mesh_viewer_world_init(Mesh_viewer_world*m)
{
	//m->things_id=0;
	//char str[]="points,edges,faces";
	m->species_id=0;
}
void Mesh_view_something_init(Mesh_view_something*ms,int id)
{
	//gldeletevertexarray
	//gldeletebuffer



}