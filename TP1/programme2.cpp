#include <iostream>
#include <fstream>
#include <vector>
int main(){
    int n;
    std::cout << "Entrez un nombre entier < 100 :" << std::endl;
    std::cin >> n;
    std::vector<int> tableau(n);
    for(int i = 0; i < n ; i++){
        tableau[i] = i*i;
    }
    std::ofstream fichier("donnees.dat");
    fichier << "Voici les carrés et les cubes des entiers:" << std::endl;
    for(int i = n-1; i >= 0; i--){
        fichier << i << " : " << tableau[i] << " : " << tableau[i]*i << std::endl;
    }
    fichier.close();
    return 0;
}