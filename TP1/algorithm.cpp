#include <iostream>
#include <fstream>
#include <sstream> 
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>


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
bool triAge(Fiche cas1, Fiche cas2){
        return(cas1.age < cas2.age);
    }
int main(){
    remplir();
    auto est_de_Lyon = [](Fiche f){
        return (f.ville == "Lyon");
    };
    int nb_Lyon = std::count_if(vdata.begin(), vdata.end(), est_de_Lyon);
    std::cout << "Le nombre de Lyonnais est de " << nb_Lyon << std::endl;
    std::cout << "Le nombre de Lyonnais est de " << 100.0*(nb_Lyon)/vdata.size() << "%" << std::endl;
    auto est_de_Lyon_30 = [](Fiche f){
        return (f.ville == "Lyon" &&  f.age < 30);
    };
    int nb_Lyon30m = std::count_if(vdata.begin(), vdata.end(), est_de_Lyon_30);
    std::cout << "Le nombre de Lyonnais ages de strictement de moins de 30 ans est de " << nb_Lyon30m << std::endl;
    auto est_de_Toulouse_A = [](Fiche F){
        return (F.ville == "Toulouse" && F.prenom[0] == 'A');
    };
    int nb_Toulouse_A = std::count_if(vdata.begin(), vdata.end(), est_de_Toulouse_A);
    if (nb_Toulouse_A > 0){
        std::cout << "Il existe un Toulousain dont le prenom commence par 'A' " << std::endl;
    }
    else{
        std::cout << "Il n'existe pas de Toulousain dont le prenom commence par 'A' " << std::endl;
    }
    std::sort(vdata.begin(), vdata.end(), triAge);
    std::cout << "La personne la plus jeune a " << vdata.front().age << " ans et s'appelle " << vdata.front().prenom << std::endl;
    std::cout << "La personne la plus agee a " << vdata.back().age << " ans et s'appelle " << vdata.back().prenom << std::endl;
    // Bien sûr, ce n'est VRAIMENT PAS la méthode la plus efficace, jouer avec le min/max //
    double ageMoyen = 0.0;
    auto ajout_Moy = [&ageMoyen](Fiche F){
        ageMoyen += F.age;
    };
    std::for_each(vdata.begin(), vdata.end(), ajout_Moy);
    ageMoyen /= vdata.size();
    std::cout << "L'age moyen est de " << ageMoyen << " ans" << std::endl;
    double sd = 0.0;
    auto ajout_sd = [&](Fiche F){
        sd += (F.age - ageMoyen)*(F.age - ageMoyen);
    };
    std::for_each(vdata.begin(), vdata.end(), ajout_sd);
    sd /= vdata.size()-1;
    sd = std::sqrt(sd);
    std::cout << "L'ecart-type de l'age est de " << sd << " ans" << std::endl;
    // Bon, pour le reste, même principe que dans analyse, on voit bien que c'est plus facile
    // pour la question f, faire la moyenne des parisiens et marseillais, il y aura 
    // deux lambda fonctions à créer, question g rien de spécial, on pourrait copier notre vdata
    // et ensuite supprimer les éléments qui ne sont pas toulousains, question h, encore 
    // une facilité par les sommes etc. 
    // Question i, pas de grosse différence, on pourrait utiliser la fonction unique et ainsi avoir
    // un élément unique par ville et ensuite itérer sur les villes pour les expliciter.
    auto compareVit = [&](Fiche f1, Fiche f2){
        return f1.temps < f2.temps;
    };
    std::sort(vdata.begin(), vdata.end(), compareVit);
    std::vector<Fiche> SousListe;
    SousListe.resize(100);
    std::copy_n(vdata.begin(), 100, SousListe.begin());
    std::ofstream fichier("data_tri.txt");
    fichier << "Voici les 100 personnes les plus rapides au 100 mètres triées par vitesse décroissante :" << std::endl;
    auto it = SousListe.begin();
    int i = 1;
    while(it != SousListe.end()){
        Fiche cas = *it;
        fichier << i << ".  " << cas.prenom << ' ' << cas.ville << ' ' << cas.age << ' ' << cas.temps << std::endl;
        ++it;
        i++;
    }
    fichier.close();




}