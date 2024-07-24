

#include <iostream>
#include <vector>

int main(){
    double dStatic = 0.1; // we can access it instantly
    double *dDynamic = new double; // creates somewhere the space of one double. 
    *dDynamic = 0.1; // this is now the 

    std::cout << dStatic << " " << *dDynamic << std::endl; 

    delete dDynamic; 
    // after deleting dDynamic you can still dereference and access where it was pointing before.  

    std::cout << dStatic << " " << *dDynamic << std::endl; 




    double *v = new double [2]; // allocate array of size 2 in heap
    v[0] = 0.1; 
    v[1] = 0.12; 

    delete [] v; // free memory of entire array; with "delete v" only the first pointer will be deleted! 
    
    
    // task: rewrite ODE solver; new homework. 



    // implement a 3D array n1=2, n2=3, n3=4. fill the array with numbers aijk = i+j+k. 
    // do not forget to free the memory before the program terminates. 

    std::vector<std::vector<std::vector<int>>> vector_dynamic; 
    int n1 = 2, n2=3, n3=4; 
    static int N = 100; 

    for(int i = 0; i< n1; ++i){
        std::vector<std::vector<int>> t2; 
        for(int j = 0; j < n2; ++j){
            std::vector<int> t1; 
            for(int k = 0; k < n3; ++k){
               t1.push_back(i+j+k);  
            }
        t2.push_back(t1);
        }
        vector_dynamic.push_back(t2); 
    }
    for(int i = 0; i< n1; ++i){
        for(int j = 0; j< n2; ++j){
            for(int k = 0; k< n3; ++k){
                std::cout << "i: " << i << "\tj:"  << j << "\tk:" << k; 
                std::cout << "\tv: " << vector_dynamic[i][j][k] << std::endl; 
            }
        }
    }

    return 1; 
}