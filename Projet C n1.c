#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char marque[20];
    char modele[20];
    char description[50];
    int statut; // 0: disponible, 1: en location
} Voiture;

typedef struct {
    int id;
    int idVoiture;
    int dateJour;
    int dateMois;
    int dateAnnee;
} Location;

typedef struct {
    int id;
    int dateJour;
    int dateMois;
    int dateAnnee;
    int idVoiture;
} Retour;

// Ajouter les autres fonctions
int ajouterVoiture() {
    Voiture voiture;
    printf("Entrer l'ID de la voiture: ");
    scanf("%d", &voiture.id);
    printf("Entrer la marque de la voiture: ");
    scanf("%s", voiture.marque);
    printf("Entrer le modele de la voiture: ");
    scanf("%s", voiture.modele);
    printf("Entrer la description de la voiture: ");
    scanf("%s", voiture.description);
    voiture.statut = 0;
    FILE *fichier;

    fichier = fopen("voitures.txt", "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    fprintf(fichier, "%d %s %s %s %d\n", voiture.id, voiture.marque, voiture.modele, voiture.description, voiture.statut);
    fclose(fichier);

    return 0;
}

int louerVoiture() {
    int idVoiture;
    Voiture voiture;
    printf("Entrer l'ID de la voiture à louer: ");
    scanf("%d", &idVoiture);
    FILE* fichier;
    fichier = fopen("voitures.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    int ok=0;
    while (fscanf(fichier, "%d %s %s %s %d", &voiture.id, voiture.marque, voiture.modele, voiture.description, &voiture.statut) != EOF) {
        if (voiture.id == idVoiture) {
            printf("Voiture trouvée:\n");
            ok+=1;
            if(!(voiture.statut)){
                voiture.statut=1;  
                FILE *fichierTemporaire;
                int idSuppression=voiture.id;
                fichierTemporaire = fopen("voitures_temp.txt", "w");
                fprintf(fichierTemporaire, "%d %s %s %s %d\n", idSuppression, voiture.marque, voiture.modele, voiture.description, 1);
                    if (fichierTemporaire == NULL) {
                        perror("Erreur lors de l'ouverture du fichier temporaire");
                        exit(1);
                    }
                   rewind(fichier);
                    while (fscanf(fichier, "%d %s %s %s %d", &voiture.id, voiture.marque, voiture.modele, voiture.description, &voiture.statut) != EOF) {
                        if (voiture.id != idSuppression) {
                            fprintf(fichierTemporaire, "%d %s %s %s %d\n",  voiture.id, voiture.marque, voiture.modele, voiture.description, voiture.statut);
                        }
                    }
                    fclose(fichier);
                    fclose(fichierTemporaire);
                    remove("voitures.txt");
                    rename("voitures_temp.txt", "voitures.txt");

                Location louer;
                printf("Entrer l'ID de la location: ");
                scanf("%d", &louer.id);
                printf("Entrer l'ID de la voiture: ");
                scanf("%d", &louer.idVoiture);
                printf("Entrer le jour de la location:");
                scanf("%d", &louer.dateJour);
                printf("Entrer le mois de la location: ");
                scanf("%d", &louer.dateMois);
                printf("Entrer l'année de la location: ");
                scanf("%d", &louer.dateAnnee);
                fichier = fopen("locations.txt", "a");
                if (fichier == NULL) {
                    perror("Erreur lors de l'ouverture du fichier");
                    exit(1);
                }
                fprintf(fichier, "%d %d %d %d %d\n", louer.id, louer.idVoiture, louer.dateJour, louer.dateMois, louer.dateAnnee);
                fclose(fichier);

                }else{
                    printf("La voiture est non disponible\n");
                }
                break;}
    }
    if(ok==0)printf("La voiture n'existe pas");

    return 0;
}

int afficherHistoriqueLocations() {
    Location louer;
    FILE* fichier;
    fichier = fopen("locations.txt", "r");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }
    while (fscanf(fichier, "%d %d %d %d %d", &louer.id,&louer.idVoiture,&louer.dateJour,&louer.dateMois,&louer.dateAnnee) != EOF) {
        printf("ID:%d  ",louer.id);
        printf("IDVoiture:%d  ",louer.idVoiture);
        printf("Jour:%d  ",louer.dateJour);
        printf("Mois:%d  ",louer.dateMois);
        printf("Annee:%d   ",louer.dateAnnee);
        printf("\n");

    }    
    fclose(fichier);

    return 0;
}

int retourVoiture() {
    Voiture voiture;
    int idVoiture;
    printf("Entrer l'ID de la voiture à retourner: ");
    scanf("%d", &idVoiture);
    FILE* fichier;
    fichier = fopen("voitures.txt","r");
    while (fscanf(fichier, "%d %s %s %s %d", &voiture.id, voiture.marque, voiture.modele, voiture.description, &voiture.statut) != EOF) {
        if (voiture.id == idVoiture) {
            if(voiture.statut==0){
                printf("ERREUR: La voiture n'est pas en location");
                
            }else{
                    
                FILE *fichierTemporaire;
                int idSuppression=voiture.id;
                fichierTemporaire = fopen("voitures_temp.txt", "a");
                fprintf(fichierTemporaire, "%d %s %s %s %d\n", idSuppression, voiture.marque, voiture.modele, voiture.description, 0);
                    if (fichierTemporaire == NULL) {
                        perror("Erreur lors de l'ouverture du fichier temporaire");
                        exit(1);
                    }
                   rewind(fichier);
                    while (fscanf(fichier, "%d %s %s %s %d", &voiture.id, voiture.marque, voiture.modele, voiture.description, &voiture.statut) != EOF) {
                        if (voiture.id != idSuppression) {
                            fprintf(fichierTemporaire, "%d %s %s %s %d\n",  voiture.id, voiture.marque, voiture.modele, voiture.description, voiture.statut);
                        }
                    }
                    fclose(fichier);
                    fclose(fichierTemporaire);
                    remove("voitures.txt");
                    rename("voitures_temp.txt", "voitures.txt");
                int choix;
                printf("Réclamation?\n");
                printf("0: Non.\n");
                printf("1: Oui\n");
                printf("Choix: ");
                scanf("%d",&choix);
                if(choix){
                    FILE *fichierTemporaire;
                    Voiture voitureCourante;
                    int idSuppression= voiture.id;
                    fichier = fopen("voitures.txt", "r");
                    if (fichier == NULL) {
                        perror("Erreur lors de l'ouverture du fichier");
                        exit(1);
                    }
                    fichierTemporaire = fopen("voitures_temp.txt", "w");
                    if (fichierTemporaire == NULL) {
                        perror("Erreur lors de l'ouverture du fichier temporaire");
                        exit(1);
                    }
                    while (fscanf(fichier, "%d %s %s %s %d", &voitureCourante.id, voitureCourante.marque, voitureCourante.modele, voitureCourante.description, &voitureCourante.statut) != EOF) {
                        if (voitureCourante.id != idSuppression) {
                            fprintf(fichierTemporaire, "%d %s %s %s %d\n", voitureCourante.id, voitureCourante.marque, voitureCourante.modele, voitureCourante.description, voitureCourante.statut);
                        }
                    }
                    fclose(fichier);
                    fclose(fichierTemporaire);
                    remove("voitures.txt");
                    rename("voitures_temp.txt", "voitures.txt");
                    printf("Voiture supprimée avec succès.\n");}
                    
            }
        break;
        }  }     
    
    return 0;}


int main() {
    int choix;
    while (1) {
        printf("\nMenu:");
        printf("\n1. Ajouter une voiture");
        printf("\n2. Louer une voiture");
        printf("\n3. Afficher l'historique des locations");
        printf("\n4. Retour d'une voiture");
        printf("\n5. Quitter");
        printf("\n\nChoix: ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterVoiture();
                break;
            case 2:
                louerVoiture();
                break;
            case 3:
                afficherHistoriqueLocations();
                break;
            case 4:
                retourVoiture();
                break;
            case 5:
                return 0;
            default:
                printf("\nChoix invalide, veuillez réessayer.");
        }
    }

    return 0;
}