#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void read_image(char *);
float cal_eme();
void find_maxmin(float *,int);

int row,col;
float **mat,max,min;
char s_name[20];

int main()
{
  float eme=0.0;

  printf("Enter Enhanced image name(.raw file)::");
  scanf("%s",s_name);

  printf("Enter Column and Row Value::");
  scanf("%d%d",&col,&row);

  read_image(s_name);
  eme=cal_eme();

  printf("Measure of Enhancement:: %f ",eme);

  return(0);
}

void read_image(char *s_name)
{
  FILE *fp;
  int i,j;

  mat=(float **)malloc(row*sizeof(float *));
  for(i=0;i<row;i++)
    mat[i]=(float *)malloc(col*sizeof(float));

  fp=fopen(s_name,"r");
  if(fp==NULL)
    {
      printf("FILE OPEN ERROR...");
      exit(0);
    }

  for(i=0;i<row;i++)
    for(j=0;j<col;j++)
      fread(&mat[i][j],sizeof(float),1,fp);

  fclose(fp);
}

float cal_eme()
{
  int i,j,k,l,m,n,cnt=0;
  float sum=0.0,*arr,ans=0.0;

  printf("Enter the size of mask block(m,n)::");
  scanf("%d%d",&m,&n);

  arr=(float *)malloc((m*n)*sizeof(float));

  for(i=0;i<m*n;i++) arr[i]=0.0;

  for(i=0;i<row;)
    {
      for(j=0;j<col;)
	{
	  for(k=0;k<m;k++)
	    {
	      if(i+k>=row)
		break;
	      for(l=0;l<n;l++)
		{
		  if(j+l<col)
		    arr[cnt++]=mat[i+k][j+l];
		  else
		    break;
		}
	    }
	  find_maxmin(arr,cnt);
	  //fprintf(stderr,"check here1:%f ::::::::::::::::::max:%f    min:%f\n",(20*log2((max+1)/(min+1))),max,min);
	  sum=sum+(20*log2((max+1)/(min+1)));
	  cnt=0;
	  j=j+n;
	}
      i=i+m;
    }

  ans=sum/(ceil(row/m)*ceil(col/n));
  return(ans);
}

void find_maxmin(float *a,int n)
{
  int i,j;
  float temp;

  max=-32768.0;
  min=32767.0;

  for(i=0;i<n;i++)
    {
      if(max < a[i])
	max=a[i];
      if(min > a[i])
	min=a[i];
    }
}
