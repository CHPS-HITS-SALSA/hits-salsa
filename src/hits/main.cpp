#include <nlohmann/json.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <math.h>

#include "csr.hpp"

using json = nlohmann::json;

//Returns the norm of a vector
template <typename T>
T normVec(std::vector<T> const& v){
    T res = 0;
    for (int i = 0; i < v.size(); ++i)
        res += v[i] * v[i];
    return sqrt(res);
}

//Hits algorithm
template <typename T>
void hits(/* Inputs */ Csr<T> const& csr_mtx, /* Outputs */ std::vector<T> authority, std::vector<T> hub){

    double eps = 1e-3;

    //Stock number of cols
    int n = csr_mtx.getRow().back();

    std::vector<T> a(n,1);  //Authority scoring
    std::vector<T> h(n,1);  //Hub scoring

    std::vector<T> a_(n,1); //Previous iteration vector authority
    std::vector<T> h_(n,1); //Previous iteration vector hub

    //a=Ah

    double norm_a = normVec(a);
    for(int i = 0; i < n; ++i)
        a[i] = a[i] / norm_a;

    //h=A^Ta

    double norm_h = normVec(h);
    for(int i = 0; i < n; ++i)
        h[i] = h[i] / norm_h;

    //norm(a - a_)
    std::vector<T> tmp_a = a;
    for(int i = 0; i < n; ++i)
        tmp_a[i] -= a_;
    double norm_tmp_a = normVec(tmp_a);

    //norm(h - h_)
    std::vector<T> tmp_h = h;
    for(int i = 0; i < n; ++i)
        tmp_h[i] -= h_;
    double norm_tmp_h = normVec(tmp_h);

    while(norm_tmp_a < eps and norm_tmp_h < eps){

        //Stores previous iteration
        a_ = a;
        h_ = h;

        //a=Ah

        norm_a = normVec(a);
        for(int i = 0; i < n; ++i)
            a[i] = a[i] / norm_a;

        //h=A^Ta

        norm_h = normVec(h);
        for(int i = 0; i < n; ++i)
            h[i] = h[i] / norm_h;
    }

    //Returns
    authority = a;
    hub = h;
}

int main() {
    std::string s = "Hello, world!";
    json js = s;
    std::cout << js << std::endl;

    return 0;
}