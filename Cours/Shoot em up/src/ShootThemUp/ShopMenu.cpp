#include "ShopMenu.h"
#include "AudioManager.h"

int ShopMenu::speedcost = 100;
int ShopMenu::delaycost = 10;
int ShopMenu::dmgcost = 100;
int ShopMenu::hpcost = 100;


ShopMenu::ShopMenu(SDL_Renderer* renderer, Game* game) : Menu("ShopMenu", renderer, game)
{
    AssetsManager& AM = AssetsManager::getInstance();
    texture = AM.GetTexture("Buttons/DEFAULT.png");
    quitText = AM.GetTexture("Buttons/MAINMENU.png");
    speed_tex = AM.GetTexture("Upgrades/speed.png");
    dmg_tex = AM.GetTexture("Upgrades/damage.png");
    delay_tex = AM.GetTexture("Upgrades/time.png");
    hp_tex = AM.GetTexture("Upgrades/health_points.png");
}


bool ShopMenu::handleInput()
{
    InputManager& IM = InputManager::getInstance();
    if (IM.IsKeyReleased(SDLK_SPACE) || IM.IsKeyReleased(SDLK_RETURN) || IM.IsKeyReleased(SDLK_ESCAPE))
    {
        UIManager::getInstance().popMenu();
        return true;
    }

    int winW = game->windowWidth;
    int winH = game->windowHeight;

    int startX = (int)(winW * 0.05f);
    int spacingX = (int)(winW * 0.1f);
    int startY = (int)(winH * 0.35f);
    int spacingY = (int)(winH * 0.10f);
    int buttonWidth = (int)(winW * 0.15f);
    int buttonHeight = (int)(winH * 0.3f);

    SDL_Rect speedRect = { startX, startY, buttonWidth, buttonHeight };
    SDL_Rect hpRect = { startX + buttonWidth + spacingX, startY, buttonWidth, buttonHeight };
    SDL_Rect dmgRect = { startX + 2 * buttonWidth + 2 * spacingX, startY, buttonWidth, buttonHeight };
    SDL_Rect timeRect = { startX + 3 * buttonWidth + 3 * spacingX, startY, buttonWidth, buttonHeight };

    if (IM.IsMouseReleased(1))
    {
        if (isMouseInRect((int)IM.getMousePos().x, (int)IM.getMousePos().y, speedRect))
        {
            if (game->getPlayerMoney() >= speedcost) {
                game->addPlayerMoney(-speedcost);
                game->playerSpeed *= 1.15f;
                AudioManager::getInstance().playSound("Achat");
                speedcost *= 1.15f;
            }
            else
                std::cout << "Argent insuffisant" << std::endl;
        }
        else if (isMouseInRect((int)IM.getMousePos().x, (int)IM.getMousePos().y, hpRect))
        {
            if (game->getPlayerMoney() >= hpcost) {
                game->addPlayerMoney(-hpcost);
                game->playerMaxHeath = (int)(game->playerMaxHeath * 1.15f + 0.5f);
                AudioManager::getInstance().playSound("Achat");
                hpcost *= 1.15f;
            }
            else
                std::cout << "Argent insuffisant" << std::endl;
        }
        else if (isMouseInRect((int)IM.getMousePos().x, (int)IM.getMousePos().y, dmgRect))
        {
            if (game->getPlayerMoney() >= dmgcost) {
                game->addPlayerMoney(-dmgcost);

                // Augmenter le multiplicateur global
                game->playerDamageMultiplicator *= 1.15f;

                // Mettre à jour le joueur actuel
                Entity* player = game->getEntitieByTag("Player");
                if (player) {
                    ((SpaceShip*)player)->damageMultiplier = game->playerDamageMultiplicator;
                }
                AudioManager::getInstance().playSound("Achat");
                dmgcost *= 1.15f;
            }
            else
                std::cout << "Argent insuffisant" << std::endl;
        }

        else if (isMouseInRect((int)IM.getMousePos().x, (int)IM.getMousePos().y, timeRect))
        {
            if (game->getPlayerMoney() >= delaycost) {
                game->addPlayerMoney(-delaycost);
                game->playerBulletCooldown *= 0.9f;
                AudioManager::getInstance().playSound("Achat");
                delaycost *= 1.15f;
            }
            else
                std::cout << "Argent insuffisant" << std::endl;
        }
    }



    int quitWidth = (int)(winW * 0.34f);
    int quitHeight = (int)(winH * 0.12f);
    int quitX = (int)((winW - quitWidth) / 2);
    int quitY = (int)(winH * 0.825f);
    SDL_Rect quitRect = { quitX, quitY, quitWidth, quitHeight };

    if (IM.IsMouseReleased(1)) {
        if (isMouseInRect((int)IM.getMousePos().x, (int)IM.getMousePos().y, quitRect)) {
            UIManager::getInstance().popMenu();
            return true;
        }
    }

    return false;
}

void ShopMenu::render()
{
    int winW = game->windowWidth;
    int winH = game->windowHeight;

    int titleWidth = (int)(winW * 0.17f);
    int titleHeight = (int)(winH * 0.12f);
    int titleX = (int)((winW - titleWidth) / 2);
    int titleY = (int)(winH * 0.06f);
    SDL_Rect titleRect = { titleX, titleY, titleWidth, titleHeight };

    SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
    SDL_RenderFillRect(renderer, &titleRect);

    if (texture)
        SDL_RenderCopy(renderer, texture, nullptr, &titleRect);

    SDL_Color titleColor = { 255, 255, 255, 255 };
    int titleFontSize = (int)(winH * 0.06f);
    UIManager::getInstance().renderTitle("SHOP", (int)(titleX + titleWidth * 0.21f), (int)(titleY + titleHeight * 0.25f), titleColor, titleFontSize);

    
    int moneyWidth = (int)(winW * 0.15f);
    int moneyHeight = (int)(winH * 0.12f);
    int moneyX = (int)(winW * 0.8f);
    int moneyY = (int)(winH * 0.06f);
    SDL_Rect moneyRect{ moneyX, moneyY, moneyWidth, moneyHeight };
    SDL_SetRenderDrawColor(renderer, 40, 40, 50, 255);
    SDL_RenderFillRect(renderer, &moneyRect);

    if (texture)
        SDL_RenderCopy(renderer, texture, nullptr, &moneyRect);

    
    int money = game->getPlayerMoney();
    UIManager::getInstance().renderNum(money, Vector2D(moneyRect.x + moneyRect.w - std::to_string(money).size() * (winW / 37.5f) - (winW / 37.5f) / 5, moneyRect.y + moneyRect.h / 2 - ((winW / 37.5f) / 2)), winW / 37.5f);

    int startX = (int)(winW * 0.05f);
    int spacingX = (int)(winW * 0.1f);
    int startY = (int)(winH * 0.35f);
    int buttonWidth = (int)(winW * 0.15f);
    int buttonHeight = (int)(winH * 0.3f);


    int levelFontSize = (int)(winH * 0.04f);
    SDL_Color levelColor = { 255, 255, 255, 255 };

    int priceRectHeight = (int)(winH * 0.06f);
    int priceFontSize = (int)(winH * 0.035f);
    SDL_Color priceColor = { 255, 215, 0, 255 };
    

    Vaisseau* player = (Vaisseau*)(game->getEntitieByTag("Player"));

    // Speed upgrade
    SDL_Rect speedRect = { startX, startY, buttonWidth, buttonHeight };
    if (speed_tex)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &speedRect);
        SDL_SetRenderDrawColor(renderer, 211, 211, 211, 125);
        SDL_RenderFillRect(renderer, &speedRect);
        SDL_RenderCopy(renderer, speed_tex, nullptr, &speedRect);

        // Afficher le niveau
        int playerSpeedLevel = 1;
        float speed = 500.f;
        while (speed < game->playerSpeed) {
            speed *= 1.15f;
            playerSpeedLevel++;
        }

        std::string levelText = "Lvl " + std::to_string(playerSpeedLevel);
        UIManager::getInstance().renderTitle(levelText.c_str(),
            startX + 10, startY + buttonHeight - 40, levelColor, levelFontSize);
    }

    // Rectangle de prix pour Speed
    SDL_Rect speedPriceRect = { startX, startY + buttonHeight + 5, buttonWidth, priceRectHeight };
    SDL_SetRenderDrawColor(renderer, 40, 40, 50, 200);
    SDL_RenderFillRect(renderer, &speedPriceRect);
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    SDL_RenderDrawRect(renderer, &speedPriceRect);
    std::string speedPriceText = std::to_string(speedcost) + " $";
    UIManager::getInstance().renderTitle(speedPriceText.c_str(),
        startX + (int)(buttonWidth * 0.3f), startY + buttonHeight + 10, priceColor, priceFontSize);

    // HP upgrade
    SDL_Rect hpRect = { startX + buttonWidth + spacingX, startY, buttonWidth, buttonHeight };
    if (hp_tex)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &hpRect);
        SDL_SetRenderDrawColor(renderer, 211, 211, 211, 125);
        SDL_RenderFillRect(renderer, &hpRect);
        SDL_RenderCopy(renderer, hp_tex, nullptr, &hpRect);

        int playerHpLevel = 1;
        int hp = 100;
        while (hp < game->playerMaxHeath) {
            hp *= 1.15f;
            playerHpLevel++;
        }

        std::string levelText = "Lvl " + std::to_string(playerHpLevel);
        UIManager::getInstance().renderTitle(levelText.c_str(),
            startX + buttonWidth + spacingX + 10, startY + buttonHeight - 40, levelColor, levelFontSize);
    }

    // Rectangle de prix pour HP
    SDL_Rect hpPriceRect = { startX + buttonWidth + spacingX, startY + buttonHeight + 5, buttonWidth, priceRectHeight };
    SDL_SetRenderDrawColor(renderer, 40, 40, 50, 200);
    SDL_RenderFillRect(renderer, &hpPriceRect);
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    SDL_RenderDrawRect(renderer, &hpPriceRect);
    std::string hpPriceText = std::to_string(hpcost) + " $";
    UIManager::getInstance().renderTitle(hpPriceText.c_str(),
        startX + buttonWidth + spacingX + (int)(buttonWidth * 0.3f), startY + buttonHeight + 10, priceColor, priceFontSize);

    // Damage upgrade
    SDL_Rect dmgRect = { startX + 2 * buttonWidth + 2 * spacingX, startY, buttonWidth, buttonHeight };
    if (dmg_tex)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &dmgRect);
        SDL_SetRenderDrawColor(renderer, 211, 211, 211, 125);
        SDL_RenderFillRect(renderer, &dmgRect);
        SDL_RenderCopy(renderer, dmg_tex, nullptr, &dmgRect);

        int playerDamageLevel = 1;
        float damage = 1.f;
        while (damage < game->playerDamageMultiplicator) {
            damage *= 1.15f;
            playerDamageLevel++;
        }


        std::string levelText = "Lvl " + std::to_string(playerDamageLevel);
        UIManager::getInstance().renderTitle(levelText.c_str(),
            startX + 2 * buttonWidth + 2 * spacingX + 10, startY + buttonHeight - 40, levelColor, levelFontSize);
    }

    // Rectangle de prix pour damage
    SDL_Rect dmgPriceRect = { startX + 2 * buttonWidth + 2 * spacingX, startY + buttonHeight + 5, buttonWidth, priceRectHeight };
    SDL_SetRenderDrawColor(renderer, 40, 40, 50, 200);
    SDL_RenderFillRect(renderer, &dmgPriceRect);
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    SDL_RenderDrawRect(renderer, &dmgPriceRect);
    std::string dmgPriceText = std::to_string(dmgcost) + " $";
    UIManager::getInstance().renderTitle(dmgPriceText.c_str(),
        startX + 2 * buttonWidth + 2 * spacingX + (int)(buttonWidth * 0.3f), startY + buttonHeight + 10, priceColor, priceFontSize);

    // Bullet delay upgrade
    SDL_Rect timeRect = { startX + 3 * buttonWidth + 3 * spacingX, startY, buttonWidth, buttonHeight };
    if (delay_tex)
    {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &timeRect);
        SDL_SetRenderDrawColor(renderer, 211, 211, 211, 125);
        SDL_RenderFillRect(renderer, &timeRect);
        SDL_RenderCopy(renderer, delay_tex, nullptr, &timeRect);

        int playerCooldownLevel = 1;
        float cooldown = 100.f;
        while (cooldown > game->playerBulletCooldown) {
            cooldown *= 0.9f;
            playerCooldownLevel++;
        }

        std::string levelText = "Lvl " + std::to_string(playerCooldownLevel);
        UIManager::getInstance().renderTitle(levelText.c_str(),
            startX + 3 * buttonWidth + 3 * spacingX + 10, startY + buttonHeight - 40, levelColor, levelFontSize);
    }

    // Rectangle de prix pour bullet delay
    SDL_Rect timePriceRect = { startX + 3 * buttonWidth + 3 * spacingX, startY + buttonHeight + 5, buttonWidth, priceRectHeight };
    SDL_SetRenderDrawColor(renderer, 40, 40, 50, 200);
    SDL_RenderFillRect(renderer, &timePriceRect);
    SDL_SetRenderDrawColor(renderer, 255, 215, 0, 255);
    SDL_RenderDrawRect(renderer, &timePriceRect);
    std::string timePriceText = std::to_string(delaycost) + " $";
    UIManager::getInstance().renderTitle(timePriceText.c_str(),
        startX + 3 * buttonWidth + 3 * spacingX + (int)(buttonWidth * 0.3f), startY + buttonHeight + 10, priceColor, priceFontSize);

    int quitWidth = (int)(winW * 0.34f);
    int quitHeight = (int)(winH * 0.12f);
    int quitX = (int)((winW - quitWidth) / 2);
    int quitY = (int)(winH * 0.825f);
    SDL_Rect quitRect = { quitX, quitY, quitWidth, quitHeight };

    SDL_SetRenderDrawColor(renderer, 80, 120, 200, 255);
    SDL_RenderFillRect(renderer, &quitRect);
    SDL_SetRenderDrawColor(renderer, 150, 180, 255, 255);
    SDL_RenderDrawRect(renderer, &quitRect);

    if (quitText) {
        SDL_RenderCopy(renderer, quitText, nullptr, &quitRect);
    }
}