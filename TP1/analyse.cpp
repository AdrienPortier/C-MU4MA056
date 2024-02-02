#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <cmath>
#include <set>
#include <vector>
struct Fiche{
    std::string prenom;
    std::string ville;
    int age;
    double temps;
};
std::vector<Fiche> vdata;
std::ifstream Fichier("smalldata.txt");
void remplir(){
    std::string ligne;
    while(std::getline(Fichier,ligne)){
        std::istringstream iss (ligne);
        Fiche cas;
        iss >> cas.prenom >> cas.ville >> cas.age >> cas.temps;
        vdata.push_back(cas);
    }
}

int main(){
    remplir();
    int habLyon = 0;
    int habLyon30Moins = 0;
    int ageMin = -1;
    std::string nomMin;
    int ageMax = 100000000000000000;
    std::string nomMax;
    bool ToulA = false;
    double moyenneAge = 0.0;

    double moyParis = 0.0;
    double moyMarseille = 0.0;
    int habParis = 0;
    int habMarseille = 0;

    std::ofstream Fichier("toulousains.txt");
    double moyAgeToulouse = 0.0;
    double moyTempsToulouse = 0.0;
    int nbHabitantsToulouse = 0;
    std::set <std::string> Villes;
    for (int i = 0; i < vdata.size(); i++){
        if (vdata[i].ville == "Lyon") {
            habLyon++;
            if (vdata[i].age < 30){
                habLyon30Moins++;
            }
        }
        if (vdata[i].ville == "Toulouse" && vdata[i].prenom[0] == 'A'){
            ToulA = true;
        }
        if (vdata[i].age > ageMin){
            ageMin = vdata[i].age;
            nomMin = vdata[i].prenom; 
        }
        if (vdata[i].age < ageMax){
            ageMax = vdata[i].age;
            nomMax = vdata[i].prenom; 
        }
        if (vdata[i].ville == "Paris"){
            habParis++;
            moyParis += vdata[i].temps;
        }
        if (vdata[i].ville == "Marseille"){
            habMarseille++;
            moyMarseille += vdata[i].temps;
        }
        moyenneAge += vdata[i].age;
        if (vdata[i].ville == "Toulouse"){
            Fichier <<  vdata[i].prenom << ' ' << 2018 - vdata[i].age << ' ' << vdata[i].temps << std::endl;
            moyAgeToulouse += vdata[i].age;
            moyTempsToulouse += vdata[i].temps;
            nbHabitantsToulouse ++;
        }
        Villes.insert(vdata[i].ville);
    }
    moyenneAge = moyenneAge/vdata.size();
    double sdAge = 0.0;
    for (int j = 0; j < vdata.size(); j++){
        sdAge += (vdata[j].age - moyenneAge)*(vdata[j].age-moyenneAge);
    }
    sdAge = sdAge/2499.0;
    sdAge = sqrt(sdAge);

    moyParis /= habParis;
    moyMarseille /= habMarseille;

    moyAgeToulouse /= nbHabitantsToulouse;
    moyTempsToulouse /= nbHabitantsToulouse;

    std::cout << "Le nombre d'habitants de la ville de Lyon est de " << habLyon << std::endl;
    std::cout << "Le pourcentage d'habitants de la ville de Lyon est de " << (static_cast<float>(habLyon)/vdata.size())*100.0 << "%" << std::endl;
    std::cout << "Le nombre d'habitants de moins de 30 ans de la ville de Lyon est de " << habLyon30Moins << std::endl;
    if (ToulA == false){
        std::cout << "Il n'existe pas d'habitant de Toulouse dont le prenom commence par la lettre A" << std::endl;
    }
    else{
        std::cout << "Il existe un habitant de Toulouse dont le prenom commence par la lettre A" << std::endl;
    }
    std::cout << "La personne la plus jeune a " << ageMin << " ans et s'appelle " << nomMin << std::endl;
    std::cout << "La personne la plus agee a " << ageMax << " ans et s'appelle " << nomMax << std::endl;
    std::cout << "La moyenne est de " << moyenneAge << " ans" << std::endl;; 
    std::cout << "L'ecart-type est de " << sdAge << " ans" << std::endl;;

    std::cout << "La moyenne du temps au 100 metres est de " << moyParis << " secondes pour les Parisiens"
    << " tandis qu'elle est de " << moyMarseille << " secondes pour les Marseillais, on en deduit que :" << std::endl; 
    if (moyParis > moyMarseille){
        std::cout << "=> Les habitants de Marseille sont en moyenne plus rapide que les habitants de Paris au 100 metres." << std::endl;
    }
    else if (moyMarseille > moyParis){
        std::cout << "=> Les habitants de Paris sont en moyenne plus rapide que les habitants de Marseille au 100 metres." << std::endl;
    }
    else{
        std::cout << "=> Les habitants de Paris sont en moyenne à egalite avec les habitants de Marseille au 100 metres." << std::endl;
    }

    double covarianceAgeTempsToul = 0.0;
    for (int j = 0; j < vdata.size(); j++){
        if (vdata[j].ville == "Toulouse"){
            covarianceAgeTempsToul += (vdata[j].age - moyAgeToulouse)*(vdata[j].temps - moyTempsToulouse);

        }
    }
    covarianceAgeTempsToul /= (nbHabitantsToulouse - 1);
    std::cout << "La covariance entre l'age et le temps au 100 metres des Toulousains est de " << covarianceAgeTempsToul << std::endl;
    std::cout << "Voici la liste des villes repertoriees au 100 metres : " << std::endl;
    auto it = Villes.begin();
    while(it != Villes.end()){
        std::cout << *it << ' ';
        ++it;
    }


}