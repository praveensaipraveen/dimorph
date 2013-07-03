#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>

//float sigx=1.0,sigy=1.0;
float **original,**temp,**out,**se,gama,sigma,theta,lambda,py=3.14159,orientation[]={90,78.75,67.5,56.25,45,33.75,22.5,11.25,0,-11.25,-22.5,-33.75,-45,-56.25,-67.5,-78.75};
int O_X,O_Y,h,v,P_Y,P_X,dx,dy;
char first[50],second[50],third[50],fourth[50];



void se_toImage(float **,char*,int,int);
void copy(float**,float**);
float setvalue(float **,int,int);
void gabor(float **,float **);
int abs(int);
void display_se(int,int);
void create_se(float,float);
void toImage(float **,char[]);
void load_original(char []);



void se_toImage(float **img,char nm[],int hh,int vv){
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
		for(i=0;i<vv;i++)
			for(j=0;j<(hh);j++){
				sprintf(buf,"%d\n",(int)img[i][j]);
//				fputs(buf,out);
				fwrite(&img[i][j],sizeof(float),1,outraw);
			}

}



void copy(float **d,float **s){
int i,j;
	for(i=0;i<O_Y;i++){
		for(j=0;j<O_X;j++){
			d[i][j]=s[i][j];
		}
	}
}


float setvalue(float **a,int x,int y){
	int i,j;
	float sum=0;

	for(i=0;i<v;i++)
		for(j=0;j<h;j++){
			sum=sum+(se[i][j]*a[x-h/2+j][y-v/2+i]);
		}
	return sum;
}



void gabor(float **dest,float **source){
	int i,j;	
	
	for(i=v/2;i<(O_Y-(v/2));i++)
		for(j=h/2;j<(O_X-(h/2));j++){
			dest[i][j]=setvalue(source,i,j);
		}
}


int abs(int x){
	if(x<0)
		x=(-x);
	return x;
}




void display_se(int x,int y){
	int i,j;
		
	for(i=0;i<y;i++){
		for(j=0;j<x;j++)
			fprintf(stderr,"%f ",se[i][j]);;
		fprintf(stderr,"\n");
	}
}




void create_se(float sigma,float theta){
	int i,j;
	float xx,yy,sum=0;	
	
	se=(float **)malloc(v*sizeof(float *));
	for(i=0;i<v;i++)
		se[i]=(float *)malloc(h*sizeof(float));

	for(i=0;i<v;i++)
		for(j=0;j<h;j++){
			xx=(j-h/2)*cosf(theta*py/180)+(i-v/2)*sinf(theta*py/180);
			yy=-(j-h/2)*sinf(theta*py/180)+(i-v/2)*cosf(theta*py/180);
			se[i][j]=expf(-((xx*xx)+(gama*gama*yy*yy))/(2*sigma*sigma))*cosf(2*py*xx*py/(lambda*180));
//			se[i][j]=expf(-((xx*xx)/(2*sigx*sigx)+(yy*yy)/(2*sigy*sigy)))*cosf(2*py*xx*py/(lambda*180));
			sum=sum+se[i][j];
		}

	for(i=0;i<v;i++)
		for(j=0;j<h;j++){
			se[i][j]=se[i][j]/sum;			
		}
	
	
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
/*
	first=(char*)malloc(10*sizeof(char));
	second=(char*)malloc(10*sizeof(char));
	third=(char*)malloc(10*sizeof(char));	
	fourth=(char*)malloc(10*sizeof(char));
*/
	org=fopen(name,"r+");
	fgets(buf,50,org);
	sprintf(first,"%s",buf);

	fgets(buf,50,org);
	sprintf(second,"%s",buf);

//	fgets(buf,50,org);

	fgets(buf,50,org);
	sprintf(third,"%s",buf);
	strcpy(value,buf);
	O_X=atoi(strtok(value," "));
	O_Y=atoi(strtok(NULL," "));

	original=(float **)malloc(O_Y*sizeof(float *));
	for(i=0;i<O_Y;i++)
		original[i]=(float *)malloc(O_X*sizeof(float));
		

	fgets(buf,50,org);
	sprintf(fourth,"%s",buf);

	for(i=0;i<O_Y;i++)	
		for(j=0;j<O_X;j++){
			fgets(buf,10,org);
			original[i][j]=atof(buf);
		}
	fclose(org);

}



int main(){
int i,ii,j,k,x,y,l;
float xx;
FILE *i_fp;
char name[20],outname[20];
/*
printf("Enter Sigma:");
scanf("%f",&sigma);
printf("Enter theta:");
scanf("%f",&theta);
printf("Enter lambda:");
scanf("%f",&lambda);
printf("Enter gamma:");
scanf("%f",&gama);


printf("Enter the input file name:");
scanf("%s",name);

	fprintf(stderr,"\n-------Enter filter size------");		
	fprintf(stderr,"Enter mXn(odd sized)");
	scanf("%d%d",&v,&h);


load_original(name);
*/
printf("Enter the input file name:");
scanf("%s",name);
sigma=1;lambda=2;gama=0.2;
h=5;v=5;
//printf("Enter theta:");
//scanf("%f",&theta);



for(ii=0;ii<16;ii++){
	load_original(name);
	//load_original("lena512.pgm");
		out=(float **)malloc(O_Y*sizeof(float *));
		for(i=0;i<O_Y;i++)
			out[i]=(float *)malloc(O_X*sizeof(float));
	
		for(i=0;i<O_Y;i++)
			for(j=0;j<O_X;j++)
				out[i][j]=original[i][j];


	create_se(sigma,orientation[ii]);
	if(ii==4)
	se_toImage(se,"structure",h,v);
	display_se(h,v);
	copy(out,original);
	gabor(out,original);
	sprintf(outname,"gout_%f",orientation[ii]);
	toImage(out,outname);
	free(out);
	free(original);


}

	return 0;

}

