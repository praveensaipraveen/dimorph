#include<stdio.h>
#include<string.h>

int main(){
int i,j,x,y;
FILE *fp,*rawfp;
char name[20],buf[110];
float temp;

fprintf(stderr,"Enter filename:\n");
scanf("%s",name);

	fp=fopen(name,"r");
//	fp=fopen("1.pgm","r");
	
	rawfp=fopen("out.raw","w+");

	fgets(buf,100,fp);
	fgets(buf,100,fp);
	fgets(buf,100,fp);
	x=atoi(strtok(buf," "));
	y=atoi(strtok(NULL," "));
//fprintf(stderr,"%d %d\n",x,y);
	fgets(buf,100,fp);
	for(i=0;i<y;i++){
		for(j=0;j<x;j++){
			fgets(buf,10,fp);
//fprintf(stderr,"%s\n",buf);
			temp=atoi(buf);
//fprintf(stderr,"%f\n",temp);
			fwrite(&temp,sizeof(float),1,rawfp);
		}	
	}
	fclose(fp);
	fclose(rawfp);
}
