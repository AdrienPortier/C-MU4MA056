#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

double aire_du_cercle(double x) {
    return M_PI*x*x;
}
double aire_du_carre(double x){
    return x*x;
}
int main(){
    double r;
    double c;
    std::cout << "Entrez le rayon du cercle:" << std::endl;
    std::cin >> r;
    std::cout << "Son aire est " << aire_du_cercle(r) << std::endl;
    std::cout << "Entrez le cote du carre:" << std::endl;
    std::cin >> c;
    std::cout << "Son aire est " << aire_du_carre(c) << std::endl;
    return 0;
}