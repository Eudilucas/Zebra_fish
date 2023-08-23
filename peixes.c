// includes, system
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>



int main( int argc, char** argv )
{
    FILE *ptr, *pont;
    int i, j, k, Ndata, Delta, visible, d;
    float t;
    
    i = sscanf (argv[1],"%d",&Ndata); 
    i = sscanf (argv[2],"%d",&Delta);



    int *deg = (int *) calloc(Ndata,sizeof(int)); 
    float *data = (float *) calloc(Ndata,sizeof(float));
    
    pont=fopen("Polarization_2.dat","r");
    for(i=0;i<Ndata;++i)fscanf(pont,"%f", &data[i]);
    fclose(pont);
    
    ptr = fopen("arestas_fish.txt","w");
    for (i=0; i<Ndata; ++i) deg[i] = 0;
    for (d=1; d<=Delta; ++d) {
	for (i=0; i<Ndata-d; ++i) {
	    j = i+d;
	    visible = 1;
	    t = (data[i]-data[j])/ (float) d;
	    for (k=i+1; k<j; ++k)
		visible = visible && ( data[k] < (data[j] + t*(j-k)) );
	    if ( visible ) {
		++deg[i];
		++deg[j];
		fprintf(ptr,"%d %d\n",i,j);
	    }
	}
    }
    fclose(ptr);
    ptr = fopen("hist_fish.dat","w");
    for (i=0; i<Ndata; ++i) fprintf(ptr,"%d %d\n",i,deg[i]);
    fclose(ptr);
    int *hist = (int *) calloc(100,sizeof(int));
    for (i=0; i<100; ++i) hist[i] = 0;
    for (i=0; i<Ndata; ++i) ++hist[deg[i]];
    ptr = fopen("deg_dist_fish.dat","w");
    double n = 0.0;
    for (i=0; i<100; ++i) n += hist[i];
    for (i=0; i<100; ++i)
	if ( hist[i] ) fprintf(ptr,"%d, %f\n",i,hist[i]/n);
    fclose(ptr);

    return 0;
}
