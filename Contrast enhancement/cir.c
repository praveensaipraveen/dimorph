#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

float** read_image(char *);
float cal_cir();
float** cal_mean_mat(float **);
float** find_interm_mean_mat(int);
float find_mean(float *,int);
void padding(float **,int);

float **mat1,**mat2,**padded_mat;
int row,col;

int main()
{
  int i,j;
  char s1[20],s2[20];
  float cir=0.0;                 

  printf("Enter Two images(before enhancement & after enhancement(.raw image))::");
  scanf("%s%s",s1,s2);

  printf("Enter Column & Row::");
  scanf("%d%d",&col,&row);

  mat1=(float **)malloc(row*sizeof(float *));
  for(i=0;i<row;i++)
    mat1[i]=(float *)malloc(col*sizeof(float));

  mat2=(float **)malloc(row*sizeof(float *));
  for(i=0;i<row;i++)
    mat2[i]=(float *)malloc(col*sizeof(float));

  mat1=read_image(s1);
  mat2=read_image(s2);

  mat1=cal_mean_mat(mat1);
  mat2=cal_mean_mat(mat2);

  cir=cal_cir();

  printf("The Contrast Improvement Ratio:: %f",cir);

  return(0);
}

float** read_image(char *s_name)
{
  FILE *fp;
  int i,j;
  float **temp_mat;

  temp_mat=(float **)malloc(row*sizeof(float *));
  for(i=0;i<row;i++)
    temp_mat[i]=(float *)malloc(col*sizeof(float));

  fp=fopen(s_name,"r");
  if(fp==NULL)
    {
      printf("FILE OPEN ERROR...");
      exit(0);
    }

  for(i=0;i<row;i++)
    for(j=0;j<col;j++)
      fread(&temp_mat[i][j],sizeof(float),1,fp);

  fclose(fp);

  return(temp_mat);
}

float cal_cir()
{
  int i,j;
  float temp=0.0,temp1=0.0,temp2=0.0;

  for(i=0;i<row;i++)
    for(j=0;j<col;j++)
      {
	temp1=temp1+fabs(pow((mat1[i][j]-mat2[i][j]),2));                           //printf("%f,",fabs(pow((mat1[i][j]-mat2[i][j]),2)));
	temp2=temp2+mat1[i][j];                            
      }                                                                       
  temp=(float)temp1/temp2;                                                       // printf("%f,%f,%f",temp1,temp2,temp);

  return(temp);
}

float** cal_mean_mat(float **mat)
{
  int i,j;
  float **temp_mat1,**temp_mat2;

  padding(mat,3);
  temp_mat1=find_interm_mean_mat(3);
  padding(mat,7);
  temp_mat2=find_interm_mean_mat(7);

  for(i=0;i<row;i++)
    for(j=0;j<col;j++)
      mat[i][j]=fabs(temp_mat1[i][j]-temp_mat2[i][j])/(0.000001+fabs(temp_mat1[i][j]+temp_mat2[i][j]));

  return(mat);
}

void padding(float **mat,int n)
{
  int i,j,val;

  val=(int)(n/2);

  padded_mat=(float **)malloc((row+2*val)*sizeof(float *));
  for(i=0;i<row+2*val;i++)
    padded_mat[i]=(float *)malloc((col+2*val)*sizeof(float));

  for(i=0;i<row+2*val;i++)
    for(j=0;j<col+2*val;j++)
      padded_mat[i][j]=0.0;

  for(i=0;i<row;i++)
    for(j=0;j<col;j++)
      padded_mat[i+val][j+val]=mat[i][j];

}

float** find_interm_mean_mat(int n)
{
  int i,j,k,l;
  float **temp_mat,*a;

  temp_mat=(float **)malloc(row*sizeof(float *));
  for(i=0;i<row;i++)
    temp_mat[i]=(float *)malloc(col*sizeof(float));

  a=(float *)malloc((n*n)*sizeof(float));

  for(i=0;i<row;i++)
    {
      for(j=0;j<col;j++)
	{
	  for(k=0;k<n;k++)
	    for(l=0;l<n;l++)
	      a[k*n+l]=padded_mat[i+k][j+l];
	  temp_mat[i][j]=find_mean(a,n);
	}
    }

  return(temp_mat);
}

float find_mean(float *a,int x)
{
  int i;
  float sum=0.0,mean=0.0;

  for(i=0;i<x;i++)
    sum=sum+a[i];

  mean=(float)(sum/(x*x));         

  return(mean);
}
