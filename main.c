#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOITURES 2

struct Voiture {
    char modele[50];
    char plaque[15];
    float kilometrage;
    int estLouee;  // 0 si disponible, 1 si louée
    int estEndommagee; // 0 si en bon état, 1 si en panne
};

void afficher_voiture(const struct Voiture *voiture) {
    printf("Modèle : %s, Plaque : %s, Kilométrage : %.2f, %s, %s\n",
           voiture->modele, voiture->plaque, voiture->kilometrage,
           voiture->estLouee ? "Louée" : "Disponible",
           voiture->estEndommagee ? "En panne" : "En bon état");
}

void louer_voiture(struct Voiture *voiture) {
    if (!voiture->estLouee) {
        voiture->estLouee = 1;
        printf("Voiture louée avec succès.\n");
    } else {
        printf("La voiture est déjà louée.\n");
    }
}

void retourner_voiture(struct Voiture *voiture, float kilometrage) {
    if (voiture->estLouee) {
        voiture->estLouee = 0;
        voiture->kilometrage = kilometrage;
        printf("Voiture retournée avec succès.\n");
    } else {
        printf("La voiture n'est pas louée.\n");
    }
}

int main() {
    struct Voiture voitures[MAX_VOITURES];

    // Initialisation des voitures
    strcpy(voitures[0].modele, "Berline");
    strcpy(voitures[0].plaque, "123ABC");
    voitures[0].kilometrage = 50000.0;
    voitures[0].estLouee = 0;
    voitures[0].estEndommagee = 0;

    strcpy(voitures[1].modele, "SUV");
    strcpy(voitures[1].plaque, "456XYZ");
    voitures[1].kilometrage = 60000.0;
    voitures[1].estLouee = 0;
    voitures[1].estEndommagee = 1;

    int choix;

    do {
        printf("1. Afficher les voitures\n");
        printf("2. Louer une voiture\n");
        printf("3. Retourner une voiture\n");
        printf("4. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                for (int i = 0; i < MAX_VOITURES; ++i) {
                    afficher_voiture(&voitures[i]);
                }
                break;
            case 2:
                printf("Choisissez une voiture à louer (1-%d) : ", MAX_VOITURES);
                int numVoiture;
                scanf("%d", &numVoiture);
                if (numVoiture >= 1 && numVoiture <= MAX_VOITURES) {
                    louer_voiture(&voitures[numVoiture - 1]);
                } else {
                    printf("Numéro de voiture invalide.\n");
                }
                break;
            case 3:
                printf("Choisissez une voiture à retourner (1-%d) : ", MAX_VOITURES);
                int numRetour;
                scanf("%d", &numRetour);
                if (numRetour >= 1 && numRetour <= MAX_VOITURES) {
                    float nouveauKilometrage;
                    printf("Entrez le nouveau kilométrage : ");
                    scanf("%f", &nouveauKilometrage);
                    retourner_voiture(&voitures[numRetour - 1], nouveauKilometrage);
                } else {
                    printf("Numéro de voiture invalide.\n");
                }
                break;
            case 4:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide.\n");
        }
    } while (choix != 4);

    return 0;
}
Ce programme permet d'afficher les informations sur les voitures, de louer une voiture et de la retourner. Vous pouvez étendre le programme en ajoutant plus de fonctionnalités selon vos besoins.

User
Supprimer une voiture qui est en panne.
● Modifier la description et l’état d’une voiture.
● Afficher l’historique des locations.
● Retour d’une voiture en cas de réclamation. ajoutez aussi ces fonction au code fournis 
ChatGPT
D'accord, j'ai ajouté les fonctionnalités demandées au code. Voici la version mise à jour :

c
Copy code
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CARS 100
#define MAX_RENTALS 50

struct Car {
    char model[50];
    char plateNumber[15];
    float mileage;
    int isRented;  // 0 si disponible, 1 si louée
    int isDamaged; // 0 si en bon état, 1 si en panne
};

struct Rental {
    struct Car *car;
    char renterName[50];
    int days;
    float mileageAtRent; // Kilométrage 
};

void addCar(struct Car fleet[], int *carCount, const char *model, const char *plateNumber, float mileage)
{
    struct Car newCar;
    strcpy(newCar.model, model);
    strcpy(newCar.plateNumber, plateNumber);
    newCar.mileage = mileage;
    newCar.isRented = 0;
    newCar.isDamaged = 0;

    fleet[*carCount] = newCar;
    (*carCount)++;

    printf("Voiture ajoutée avec succès\n");
}

void displayCar(const struct Car *car)
{
    printf("Modèle : %s, Plaque : %s, Kilométrage : %.2f, %s, %s\n",
           car->model, car->plateNumber, car->mileage,
           car->isRented ? "Louée" : "Disponible",
           car->isDamaged ? "En panne" : "En bon état");
}

void removeDamagedCar(struct Car fleet[], int *carCount, const char *plateNumber)
{
    for (int i = 0; i < *carCount; i++) 
    {
        if (strcmp(fleet[i].plateNumber, plateNumber) == 0) 
        {
            if (fleet[i].isDamaged)
            {
                for (int j = i; j < (*carCount - 1); j++)
                {
                    fleet[j] = fleet[j + 1];
                }
                (*carCount)--;
                printf("Voiture supprimée\n");
                return;
            } else 
            {
                printf("La voiture n'est pas en panne\n");
                return;
            }
        }
    }
    printf("Voiture non trouvée\n");
}

void modifyCar(struct Car fleet[], int carCount, const char *plateNumber, float newMileage, int isDamaged)
{
    for (int i = 0; i < carCount; i++)
    {
        if (strcmp(fleet[i].plateNumber, plateNumber) == 0)
        {
            fleet[i].mileage = newMileage;
            fleet[i].isDamaged = isDamaged;
            printf("Modification de la voiture avec succès\n");
            return;
        }
    }
    printf("Voiture non trouvée\n");
}

void displayRentals(const struct Rental rentals[], int rentalCount)
{
    printf("Historique des locations :\n");
    for (int i = 0; i < rentalCount; i++)
    {
        printf("Voiture : %s, Loueur : %s, Jours : %d\n",
               rentals[i].car->model, rentals[i].renterName, rentals[i].days);
    }
}

void returnCar(struct Car fleet[], int carCount, struct Rental rentals[], int *rentalCount, const char *plateNumber)
{
    for (int i = 0; i < *rentalCount; i++)
    {
        if (strcmp(rentals[i].car->plateNumber, plateNumber) == 0)
        {
            fleet[carCount].isRented = 0; 
            float mileageAtReturn = rentals[i].car->mileage;
            int daysRented = rentals[i].days;

            float cost = calculateRentalCost(mileageAtReturn - rentals[i].mileageAtRent, daysRented);

            printf("Voiture retournée\n");
            printf("Coût de la location : %.2f euros\n", cost);
            (*rentalCount)--;
            return;
        }
    }
    printf("Voiture introuvable\n");
}

float calculateRentalCost(float mileage, int days)
{
    const float costPerKilometer = 0.2;
    const float dailyRentalRate = 30.0;

    float mileageCost = mileage * costPerKilometer;
    float dailyCost = days * dailyRentalRate;

    return mileageCost + dailyCost;
}

void rentCar(struct Car fleet[], int carCount, struct Rental rentals[], int *rentalCount)
{
    int carIndex;
    displayCars(fleet, carCount);

    printf("Donner le numéro de la voiture à louer : ");
    scanf("%d", &carIndex);

    if (carIndex >= 0 && carIndex < carCount)
    {
        if (fleet[carIndex].isRented)
        {
            printf("La voiture est louée\n");
        }
         else
         {
            struct Rental newRental;
            newRental.car = &fleet[carIndex];

            printf("Nom du locataire : ");
            scanf("%s", newRental.renterName);

            printf("Nombre de jours de location : ");
            scanf("%d", &newRental.days);

            newRental.mileageAtRent = fleet[carIndex].mileage;

            fleet[carIndex].isRented = 1;
            rentals[*rentalCount] = newRental;
            (*rentalCount)++;

            printf("Voiture louée\n");
        }
    } else
    {
        printf("Numéro de voiture introuvable\n");
    }
}

void displayCars(const struct Car fleet[], int carCount)
{
    printf("Liste des voitures :\n");
    for (int i = 0; i < carCount; i++)
    {
        displayCar(&fleet[i]);
    }
}

void displayInvoice(const struct Rental rentals[], int rentalCount, const char *plateNumber)
{
    for (int i = 0; i < rentalCount; i++)
    {
        if (strcmp(rentals[i].car->plateNumber, plateNumber) == 0)
        {
            float mileageAtReturn = rentals[i].car->mileage;
            int daysRented = rentals[i].days;

            float cost = calculateRentalCost(mileageAtReturn - rentals[i].mileageAtRent, daysRented);

            printf("Facture pour la location de la voiture %s :\n", plateNumber);
            printf("Kilométrage au début : %.2f\n", rentals[i].mileageAtRent);
            printf("Kilométrage à la fin : %.2f\n", mileageAtReturn);
            printf("Nombre de jours : %d\n", daysRented);
            printf("Coût total : %.2f euros\n", cost);

            return;
        }
    }
    printf("Voiture introuvable\n");
}

int main()
{
    struct Car carFleet[MAX_CARS];
    struct Rental currentRentals[MAX_RENTALS];
    int numberOfCars = 0;
    int numberOfRentals = 0;

    int choice;

    do
    {
        printf("1. Ajouter une voiture\n");
        printf("2. Afficher les voitures\n");
        printf("3. Louer une voiture\n");
        printf("4. Retourner une voiture\n");
        printf("5. Supprimer une voiture en panne\n");
        printf("6. Modifier la description d'une voiture\n");
        printf("7. Afficher l'historique des locations\n");
        printf("8. Afficher la facture pour une location\n");
        printf("9. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                {
                    char model[50];
                    char plateNumber[15];
                    float mileage;

                    printf("Modèle de la voiture : ");
                    scanf("%s", model);

                    printf("Plaque d'immatriculation : ");
                    scanf("%s", plateNumber);

                    printf("Kilométrage : ");
                    scanf("%f", &mileage);

                    addCar(carFleet, &numberOfCars, model, plateNumber, mileage);
                }
                break;
            case 2:
                displayCars(carFleet, numberOfCars);
                break;
            case 3:
                rentCar(carFleet, numberOfCars, currentRentals, &numberOfRentals);
                break;
            case 4:
                {
                    char plateNumber[15];
                    printf("Plaque d'immatriculation de la voiture à retourner : ");
                    scanf("%s", plateNumber);
                    returnCar(carFleet, numberOfCars, currentRentals, &numberOfRentals, plateNumber);
                }
                break;
            case 5:
                {
                    char plateNumber[15];
                    printf("Plaque d'immatriculation de la voiture en panne : ");
                    scanf("%s", plateNumber);
                    removeDamagedCar(carFleet, &numberOfCars, plateNumber);
                }
                break;
            case 6:
                {
                    char plateNumber[15];
                    float newMileage;
                    int isDamaged;
                    printf("Plaque d'immatriculation de la voiture à modifier : ");
                    scanf("%s", plateNumber);
                    printf("Nouveau kilométrage : ");
                    scanf("%f", &newMileage);
                    printf("La voiture est-elle en panne ? (1 pour oui, 0 pour non) : ");
                    scanf("%d", &isDamaged);
                    modifyCar(carFleet, numberOfCars, plateNumber, newMileage, isDamaged);
                }
                break;
            case 7:
                displayRentals(currentRentals, numberOfRentals);
                break;
            case 8:
                {
                    char plateNumber[15];
                    printf("Plaque d'immatriculation de la voiture pour afficher la facture : ");
                    scanf("%s", plateNumber);
                    displayInvoice(currentRentals, numberOfRentals, plateNumber);
                }
                break;
            case 9:
                printf("Au revoir !\n");
                break;
            default:
                printf("Option invalide.\n");
        }

    } while (choice != 9);

    return 0;
}
