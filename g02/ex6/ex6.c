#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>

#define MAT_COLS    1024 * 20
#define MAT_LIN     1024 * 20
#define FORKS 3

long getDiffMilis (struct timespec tpi, struct timespec tpf){
    long secs  = (tpf.tv_sec - tpi.tv_sec)*1000;
    long milis = (tpf.tv_nsec - tpi.tv_nsec)/(1000 * 1000);
    return (secs+milis);
}
int mtest (int **mat, int li, int lf, int targ){
    for (; li < lf; li++)
        for (int j = 0; j < MAT_COLS; j++)
            if (mat[li][j] == targ)
                return 1;
    return 0;
}

void mfill (int **mat){
    srand(time(NULL));
    for (int i=0; i<MAT_LIN; i++)
        for (int j=0; j<MAT_COLS; j++){
            mat[i][j] = 1; //rand ();
        }
}

int **minit () {
    int **mat = calloc (MAT_LIN, sizeof(int*));
    for (int i=0; i<MAT_LIN; i++)
        mat[i] = calloc (MAT_COLS, sizeof(int));
    return mat;
}

int main (){
    int searchnum = 0;
    puts ("ALLOCATING MATRIX");
    int **mat = minit();
    puts ("FILLING MATRIX.");
    mfill (mat);
    printf ("%ld MiB FILLED.\n", (MAT_COLS * MAT_LIN * sizeof(int)) / (1024 * 1024));
    int workload = (int)(((float)MAT_LIN)/((float)FORKS));
    int is_child;
    int i;
    puts ("FORKING PROGRAM.");
    struct timespec tpi;
    struct timespec tpf;
    clock_gettime(CLOCK_REALTIME, &tpi); 

    for (i = 0; i < FORKS; i++){
        is_child = !fork ();
        if (is_child){
            int li = i * workload;
            int lf = (i+1) * workload;
            int test = mtest (mat, li, lf, searchnum);
            _exit (test);
        }
    }

    int status;
    int r = 0;
    pid_t p;
    puts ("WAITING FOR FORKS.");
    do {
        p = wait (&status);
        r = r || WEXITSTATUS(status);
    } while (!r && p != -1);

    clock_gettime(CLOCK_REALTIME, &tpf);
    long milis = getDiffMilis (tpi, tpf);
    r ? puts ("VALUE FOUND.") : puts ("VALUE NOT FOUND.");
    printf ("Time needed for search %ld milisecs\n", milis);
	return 0;
}

