#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>


float **original,**out,**final,orientation[]={90,78.75,67.5,56.25,45,33.75,22.5,11.25,0,-11.25,-22.5,-33.75,-45,-56.25,-67.5,-78.75};
int O_X,O_Y,h,v,P_Y,P_X,dx,dy;
char first[50],second[50],third[50],fourth[50];

void threshold();
void toImage(float **,char *);
void load_original(char *);



void threshold(){
int i,j;

	for(i=0;i<O_Y;i++)
		for(j=0;j<O_X;j++)
			if(final[i][j]<0)
				final[i][j]=0;

}

void toImage(float **img,char nm[]){
	int i,j;
	FILE *out,*outraw;
	char buf[10],outname[20];
//	sprintf(outname,"%s.pgm",nm);
//	out=fopen(outname,"w+");
	sprintf(outname,"%s.raw",nm);
	outraw=fopen(outname,"w+");
/*
		fputs(first,out);
		fputs(second,out);
//		fputs(third,out);
		sprintf(buf,"%d %d\n",O_X,O_Y);
		fputs(buf,out);
		fputs(fourth,out);
*/
		for(i=0;i<O_Y;i++)
			for(j=0;j<(O_X);j++){
				sprintf(buf,"%d\n",(int)img[i][j]);
//				fputs(buf,out);
				fwrite(&img[i][j],sizeof(float),1,outraw);
			}

}


void load_original(char name[]){
	int i,j,k;
	FILE *org;
	char buf[50],value[50];

	org=fopen(name,"r+");

	original=(float **)malloc(O_Y*sizeof(float *));
	for(i=0;i<O_Y;i++)
		original[i]=(float *)malloc(O_X*sizeof(float));


	for(i=0;i<O_Y;i++)
		for(j=0;j<O_X;j++){
			fread(&original[i][j],sizeof(float),1,org);
		}
	fclose(org);

}






int main(){

int i,j,ii,lambda;
char name[20],outname[20];

printf("Ensure that all outputs of gabor.c are in this directory\nEnter the original file name (.raw file):");
scanf("%s",name);

fprintf(stderr,"Enter X and Y of image\n");
scanf("%d%d",&O_X,&O_Y);

//printf("Enter lambda, (of enhance operation)\n");
//scanf("%d",&lambda);
lambda=1;
		out=(float **)malloc(O_Y*sizeof(float *));
		for(i=0;i<O_Y;i++)
			out[i]=(float *)malloc(O_X*sizeof(float));

		for(i=0;i<O_Y;i++)
			for(j=0;j<O_X;j++)
				out[i][j]=0;


		final=(float **)malloc(O_Y*sizeof(float *));
		for(i=0;i<O_Y;i++)
			final[i]=(float *)malloc(O_X*sizeof(float));

		for(i=0;i<O_Y;i++)
			for(j=0;j<O_X;j++)
				final[i][j]=0;


for(ii=0;ii<16;ii++){
fprintf(stderr,"image-%d loaded...\n",ii+1);

	sprintf(outname,"gout_%f.raw",orientation[ii]);
	load_original(outname);

	for(i=0;i<O_Y;i++)
		for(j=0;j<O_X;j++)
			out[i][j]=out[i][j]+original[i][j];

	free(original);
}

	for(i=0;i<O_Y;i++)
		for(j=0;j<O_X;j++)
			out[i][j]=(float)out[i][j]/16;

	toImage(out,"mean_gabor");
	load_original(name);
	toImage(original,"aftermean");
	for(i=0;i<O_Y;i++)
		for(j=0;j<O_X;j++)
			final[i][j]=original[i][j]+lambda*(original[i][j]-out[i][j]);
//			final[i][j]=lambda*(original[i][j]-out[i][j]);
    threshold();
	toImage(final,"g_result");
	return 0;

}


