#include <iostream>
#include <math.h>
#include <cmath>

using namespace std;

const int dim_matrix = 100;

void inputMatrix(int *n, int *m, double x[dim_matrix][dim_matrix]){
    int i,j;
    for(i = 0; i < *n; i++){
        cout << "v" << i + 1 << ":";
        cout << endl;
        for(j = 0; j < *m; j++){
            cin >> x[i][j];
        }
    }

}

void outputMatrixF(int *n, int *m, double x[dim_matrix][dim_matrix]){
    int i, j;
    for(i = 0; i < *n; i++){
        cout << "f" << i + 1 << ":" ;
        cout << "(";
        for(j = 0; j < *m; j++){
            if(abs(x[i][j]) < 1.e-14){
                x[i][j] = 0;
            }
            if(j == *m-1){  
                cout << x[i][j];       
            }
            else{
                cout << x[i][j] << ", ";
            }
        }
        cout << ");";
        cout << endl;
    }
}

void outputMatrixE(int *n, int *m, double x[dim_matrix][dim_matrix]){
    int i, j;
    for(i = 0; i < *n; i++){
        cout << "e" << i + 1 << ":";
        cout << "(";
        for(j = 0; j < *m; j++){
            if(abs(x[i][j]) < 1.e-14){
                x[i][j] = 0;
            }
            if(j == *m-1){  
                cout << x[i][j];       
            }
            else{
                cout << x[i][j] << ", ";
            }
        }
        cout << ");";
        cout << endl;
    }
}

void initialize(int *m,double v[dim_matrix]){
    int i;
    for(i = 0; i < *m; i++){
        v[i] = 0;
    }
}

int main(){
    double v[dim_matrix][dim_matrix], f[dim_matrix][dim_matrix], 
    e[dim_matrix][dim_matrix],p1,p2,a[dim_matrix], div = 0, dist;
    int n, m, i, j, z;
    cout << "-----------------------------------------------" << endl;
    cout << "Input the number of vectors: ";
    cin >> n;
    cout << "Input the number of elements: ";
    cin >> m;
    cout << "-----------------------------------------------" << endl;
    inputMatrix(&n,&m,v); 
    for(i = 0; i < m; i++){
        f[0][i] = v[0][i];
    }
    for(i = 1;i < n; i++){
        z = 0;
        initialize(&m,a);
        do{
        p1 = 0;
        p2 = 0;
        for(j = 0; j < m; j++){
            p1 = f[z][j] * v[i][j] + p1;
            p2 = f[z][j] * f[z][j] + p2;
        }
        div = p1 / p2;
        for(j = 0; j < m; j++){
            a[j] = f[z][j] * div + a[j];
        }
        z++;
        } while(z < i);
            for(j = 0; j < m; j++){
                f[i][j] = v[i][j] - a[j];
            }
    }
    cout << "------The orthogonal form of the vectors-------" << endl;
    outputMatrixF(&n,&m,f);
    cout << "-----------------------------------------------" << endl;

    for(i = 0; i < n; i++){
        dist = 0;
        for(j = 0; j < m; j++){
            dist = dist + pow(f[i][j], 2);
        }
        dist = sqrt(dist);
        for(j = 0; j < m; j++)
            e[i][j] = f[i][j] / dist;
    }
    cout << endl;
    cout << "------The orthonormal form of the vectors------" << endl;
    outputMatrixE(&n,&m,e);
    cout << "-----------------------------------------------" << endl;
    return 0;
}
