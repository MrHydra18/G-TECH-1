#include "GameState.h"
#include "Charactere.h"
#include "RandomManager.h"
#include "Marchant.h"
#include "GameManager.h"
#include "Item.h"
#include <iostream>

//Creation du Menu principale pour choisir quoi faire
bool GameState::Menu(Charactere* player, GameManager* gameManager)
{
    int value = gameManager->AskInt(1, 6, "\n Que voulez vous faire\n  1 = Regarder mes stats.\n  2 = Ouvrir l'inventaire.\n  3 = Utiliser un objet.\n  4 = Aller a la boutique.\n  5 = Aller combattre.\n  6 = Quitter");

    //Choix de quoi faire
    switch (value)
    {
    case 1:
        system("cls");
        player->DisplayStatus();
        break;
    case 2:
        system("cls");
        player->DisplayInventory();
        break;
    case 3:
        system("cls");
        UseInventoryItem(player, gameManager);
        break;
    case 4:
        system("cls");
        Shop(player, gameManager);
        break;
    case 5:
        Combat(player, gameManager);
        system("cls");
        break;
    case 6:
        return false;
    }

    return true;
}

//Utilisation des objets
void GameState::UseInventoryItem(Charactere* player, GameManager* gameManager)
{
    //ouvrir inventaire
    player->DisplayInventory();

    std::cout << "\n================================" << std::endl;
    int choice = gameManager->AskInt(0, player->GetInventorySize(),
        "\nQuel objet voulez-vous utiliser? (0 pour annuler)");

    if (choice == 0)
    {
        //Si on veut sortir de l'inventaire
        std::cout << "\nAnnule." << std::endl;
        return;
    }

    system("cls");
    player->UseItem(choice - 1);
}

//Creation de la boutique
void GameState::Shop(Charactere* player, GameManager* gameManager)
{
    Marchant marchant("Baldric le Marchand", 100, 5000, 0);

    //On ajoute les objets au marchand
    marchant.AddItemToShop(Item("Potion de soin", 10, "Restaure 10 PV", ItemType::CONSUMABLE, 10), 10);
    marchant.AddItemToShop(Item("Grande potion", 50, "Restaure 50 PV", ItemType::CONSUMABLE, 50), 25);
    marchant.AddItemToShop(Item("Potion supreme", 100, "Restaure 100 PV", ItemType::CONSUMABLE, 10), 50);
    marchant.AddItemToShop(Item("Epee en fer", 25, "Augmente les degats", ItemType::WEAPON, 0, 15), 50);
    marchant.AddItemToShop(Item("Epee en diamant", 25, "Augmente les degats", ItemType::WEAPON, 0, 25), 100);

    bool inShop = true;

    while (inShop)
    {
        //Affichage de la boutique
        marchant.DisplayShop(player);
        std::cout << "================================" << std::endl;

        //Demande de ce qu'on choisis d'acheter
        int choice = gameManager->AskInt(0, marchant.GetShopSize(), "\nQuel article voulez-vous acheter? (0 pour quitter la boutique)");
        system("cls");

        if (choice == 0)
        {
            //Sortir de la boutique
            std::cout << "\nMerci de votre visite!" << std::endl;
            inShop = false;
        }
        else
        {
            //Appel a la fonction pour acheter un objet
            marchant.SellItem(player, choice - 1);
        }
    }
}

//Fonction de=u combat
void GameState::Combat(Charactere* player, GameManager* game)
{
    inCombat = true;

    //Choisis un ennemi aleatoire parmis la liste d'ennemis
    int randomIndex = RandomManager::GenerateRandomNumber(0, game->GetEnemiesCount() - 1);
    Ennemi* ennemi = game->GetEnemy(randomIndex);

    system("cls");
    std::cout << "\nUn " << ennemi->GetName() << " sauvage de niveau " << ennemi->GetLevel() << " apparait!" << std::endl;

    while (inCombat)
    {
        //Affichage si on meurt
        if (player->GetHp() <= 0)
        {
            system("cls");
            std::cout << "\n T'es mort, ameliore toi et reviens plus tard." << std::endl;
            game->turn = 0;
            player->ResetHp();
            inCombat = false;
        }

        //Affichage et récompense quand on tue un ennemi
        if (ennemi->GetHp() <= 0)
        {
            system("cls");

            int goldReward = ennemi->GetGoldDrop();
            int expReward = ennemi->GetExpDrop();

            std::cout << "\n======================== VICTOIRE! ========================" << std::endl;
            std::cout << "Vous avez obtenu " << goldReward << " pieces d'or et " << expReward << " points d'experience !" << std::endl;
            std::cout << "===========================================================\n" << std::endl;

            player->AddMoney(goldReward);
            player->AddExp(expReward);
            game->turn = 0;
            ennemi->ResetHp();
            inCombat = false;
        }

        //Compteur pour les tours lors du combat
        std::cout << "\n Tour " << game->turn++ << ".\n";
        std::cout << "Vos PV: " << player->GetHp() << " | PV " << ennemi->GetName() << " : " << ennemi->GetHp() << std::endl;
        int choix = game->AskInt(1, 4, "Que veux tu faire? 1 = Attaquer / 2 = Ouvrir Inventaire / 3 = Fuir");

        switch (choix)
        {
        case 1:
        {
            system("cls");
            int dmg = player->Attack();
            ennemi->TakeDamage(dmg);
            break;
        }
        case 2:
        {
            system("cls");
            player->DisplayInventory();

            //Verification que l'inventaire n'est pas vide
            if (player->GetInventorySize() > 0)
            {
                std::cout << "\n================================" << std::endl;
                int itemChoice = game->AskInt(0, static_cast<int>(player->GetInventorySize()),
                    "\nQuel objet voulez-vous utiliser? (0 pour annuler)");

                //choix de l'item a utiliser
                if (itemChoice > 0)
                {
                    system("cls");
                    bool itemUsed = player->UseItem(itemChoice - 1);
                    //si on utilise pas d'item le tour ne compte pas
                    if (!itemUsed)
                    {
                        game->turn--;
                    }
                }
                else
                {
                    system("cls");
                    game->turn--;
                }
            }
            else
            {
                system("cls");
                std::cout << "\nVous n'avez aucun objet a utiliser!" << std::endl;
                game->turn--;
            }
            break;
        }
        case 3:
            system("cls");
            std::cout << "\nVous prenez la fuite!" << std::endl;
            inCombat = false;
            return;
        }

        //Verification que le combat peut continuer
        if (inCombat && ennemi->GetHp() > 0)
        {
            int enemyDamage = ennemi->Attack();
            player->TakeDamage(enemyDamage);
            std::cout << ennemi->GetName() << " vous attaque et inflige " << enemyDamage << " degats!" << std::endl;
        }
    }
}