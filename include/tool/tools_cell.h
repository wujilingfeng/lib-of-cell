#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void offtocell(char const* filename)
{
    int filenamesize=strlen(filename);
    char *outfilename=(char*)malloc(filenamesize+2);
    for(int i=0;i<filenamesize;i++)
    {
        outfilename[i]=filename[i];
    
    }
    outfilename[filenamesize-3]='c';
    outfilename[filenamesize-2]='e';
    outfilename[filenamesize-1]='l';
    outfilename[filenamesize]='l';
    outfilename[filenamesize+1]='\0';
    printf("%s\n",outfilename);
#ifdef WIN32
    FILE* infile,*outfile;
    fopen_s(&infile,filename,"r");
    fopen_s(&outfile,outfilename,'w')
#else
    FILE* infile=fopen(filename,"r");
    FILE* outfile =fopen(outfilename,"w");
#endif
    if(!infile)
    {
        printf("can't open this file %s\n",filename);
        return ;
    
    }
    if(!outfile)
    {
    
        printf("can't open this file %s\n",outfilename);
        return;
    
    }
    char off[6];
    fscanf(infile,"%s",off);
    int num_el[3],background_dim=0;int simplex=1;
    if(strcmp("OFF",off)==0)
    {
        //fwrite("CELL\n",1,5,ourfile);
        fscanf(infile,"%d %d %d",&num_el[0],&num_el[2],&num_el[1]);
        char a;int flag=0;
        for(fscanf(infile,"%c",&a);a!='\n'||background_dim==0;fscanf(infile,"%c",&a))
        {
            if(a==' ')
            {
                if(flag==1)
                {
                    background_dim++;
    
                }
                flag=0;

            }
            else
            {
                flag=1;

            }
            
        printf("a :%c\n",a);
        }
        if(flag==1){
        background_dim++;
        }
       // printf("background_dim:%d\n",background_dim);
        //fscanf(infile,"%c",&a);
        double b=0;
        for(int i=1;i<num_el[0];i++)
        {
            for(int j=0;j<background_dim;j++)
            {
        
                fscanf(infile,"%lf ",&b);
                //printf("%lf\n",b);
        
            }
        
        
        }
        int max_min[2];
        //这里的num_face是半面的个数
        int num_face=0; 
        int face_index[(background_dim+2)*num_el[2]];
        int face_temp=0;

        for(int i=0;i<num_el[2];i++)
        {   
            fscanf(infile,"%d",&max_min[0]);
            num_face+=max_min[0];
            face_index[face_temp]=max_min[0];
            face_temp++;

            if(max_min[0]>3)
            {
                simplex=0;
               // break;
            
            }
            for(int j=0;j<max_min[0];j++)
            {
            
            //    fscanf(infile,"%d",&max_min[1]);
                fscanf(infile,"%d",&face_index[face_temp]);
                face_temp++;

            }
            
        
        }
        //以上分析获取数据，以下写数据
        //printf("simplex: %d\n",simplex);
        fprintf(outfile,"CELL\n");
        fprintf(outfile,"background_dim= %d\n",background_dim);
        fprintf(outfile,"simplex= %d\n",simplex);
        if(simplex==1)
        {
            fprintf(outfile,"%d %d %d\n",num_el[0],0,num_el[2]); 
        
        }
        else
        {
        
        
            fprintf(outfile,"%d %d %d\n",num_el[0],num_face,num_el[2]);
        }
       
        fseek(infile,0,SEEK_SET);
        fscanf(infile,"%s %d %d %d",off,&max_min[1],&max_min[1],&max_min[1]);
         
        for(int i=0;i<num_el[0];i++)
        {
            for(int j=0;j<background_dim;j++)
            {
                fscanf(infile,"%lf",&b);
                fprintf(outfile,"%lf ",b);
            
            }
            fprintf(outfile,"\n"); 
        }
        /*for(int i=0;i<num_el[2];i++)
        {   
            fscanf(infile,"%d",&max_min[0]);
            face_index[face_temp]=max_min[0];
            face_temp++;
            for(int j=0;j<max_min[0];j++)
            {
            
                fscanf(infile,"%d",&face_index[face_temp]);
                face_temp++;
            
            }
            
        
        }*/

        if(simplex==0)
        {
            int i=0;
            while(i<face_temp)
            {
                int tmp_num=face_index[i];
                for(int j=0;j<tmp_num;j++)
                {
                    fprintf(outfile,"%d %d %d\n",2,face_index[i+(j)%tmp_num+1],face_index[i+(j+1)%tmp_num+1]);  
                    
               
                }
                i=i+tmp_num+1;
            }
            i=0;int tmp_id=0;
            while(i<face_temp)
            {
                int tmp_num=face_index[i];
                fprintf(outfile,"%d ",tmp_num);
                for(int j=0;j<tmp_num;j++)
                {
                    fprintf(outfile,"%d ",tmp_id);
                    tmp_id++;
                     
                }
                fprintf(outfile,"\n");
                i=i+tmp_num+1;
            }
           
        }
        else
        {
         
            int i=0;
            while(i<face_temp)
            {
                int tmp_num=face_index[i];
                fprintf(outfile,"%d ",tmp_num);
                for(int j=0;j<tmp_num;j++)
                {
                    fprintf(outfile,"%d ",face_index[i+j+1]);  
                    
               
                }
                fprintf(outfile,"\n");
                i=i+tmp_num+1;
            }
 

        }

       /* 
               for(int i=0;i<num_el[1];i++)
        {
            for(int j=0;j<)
            {
            
            
            }
        }
        */
        /*fwrite("CELL\n",1,5,outfile);
        char temp_s[100];
        sprintf(temp_s,"background_dim=%d\n",background_dim);
        fwrite(temp_s,1,5,outfile);*/



    
    
    
    
    }


}

