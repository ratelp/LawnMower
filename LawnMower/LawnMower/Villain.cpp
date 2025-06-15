#include "LawnMower.h"
#include "Villain.h"
#include "Bullet.h"
#include "Level1.h"
#include <sstream>

// ---------------------------------------------------------------------------------

Villain::Villain(Player* currentPlayer)
{
    spriteL = new Sprite("Resources/originalVillain1.png");
    //spriteR = new Sprite("Resources/villain1.png");
    //spriteU = new Sprite("Resources/villain1.png");
    //spriteD = new Sprite("Resources/villain1.png");
    
    spriteL2 = new Sprite("Resources/originalVillain2.png");
    //spriteR2 = new Sprite("Resources/villain2.png");
    //spriteU2 = new Sprite("Resources/villain2.png");
    //spriteD2 = new Sprite("Resources/villain2.png");
    
    spriteL3 = new Sprite("Resources/originalVillain3.png");
    //spriteR3 = new Sprite("Resources/villain3.png");
    //spriteU3 = new Sprite("Resources/villain3.png");
    //spriteD3 = new Sprite("Resources/villain3.png");
    
    spriteL4 = new Sprite("Resources/originalVillain4.png");
    //spriteR4 = new Sprite("Resources/villain4.png");
    //spriteU4 = new Sprite("Resources/villain4.png");
    //spriteD4 = new Sprite("Resources/villain4.png");

    bullet = new Image("Resources/villainBullets.png");

    player = currentPlayer;

    // imagem do pacman é 48x48 (com borda transparente de 4 pixels)
    BBox(new Rect(- (spriteL->Width() / 2.0f), -(spriteL->Width() / 2.0f - 4), (spriteL->Width() / 2.0f), (spriteL->Width() / 2.0f - 2)));
    MoveTo(window->CenterX(), window->CenterY() - 210);
    
    type = VILLAIN;
}

// ---------------------------------------------------------------------------------

Villain::~Villain()
{
    delete spriteL;
    //delete spriteR;
    //delete spriteU;
    //delete spriteD;

    delete spriteL2;
    //delete spriteR2;
    //delete spriteU2;
    //delete spriteD2;

    delete spriteL3;
    //delete spriteR3;
    //delete spriteU3;
    //delete spriteD3;

    delete spriteL4;
    //delete spriteR4;
    //delete spriteU4;
    //delete spriteD4;

    delete bullet;
}

// ---------------------------------------------------------------------------------

void Villain::Stop()
{
}

// ---------------------------------------------------------------------------------

void Villain::Up()
{
}

// ---------------------------------------------------------------------------------

void Villain::Down()
{
}

// ---------------------------------------------------------------------------------

void Villain::Left()
{
}

// ---------------------------------------------------------------------------------

void Villain::Right()
{
}

// ---------------------------------------------------------------------------------

void Villain::Update()
{
    if (player->playerLife == ALIVEP)
    {
        bulletsCooldownTimer -= gameTime;
        bulletBurstCooldownTimer -= gameTime;
        

        if (bulletsCooldownTimer <= 0.0f) {
            bulletsToShootInBurst = 1;
            bulletsCooldownTimer = bulletsCooldownMaxTimer;
            bulletBurstCooldownTimer = 0.0f;
        }
        if (bulletsToShootInBurst > 0 && bulletBurstCooldownTimer <= 0.0f) {

            // LOCALIZA LOCAL PARA SER FEITO O TIRO (ponto final)
            Rect* playerBBox = static_cast<Rect*>(player->BBox());
            float whereX = playerBBox->Left() + (playerBBox->Right() - playerBBox->Left()) / 2.0f;
            float whereY = playerBBox->Top() + (playerBBox->Bottom() - playerBBox->Top()) / 2.0f;

            switch (currSprite) {
            case VILLAIN1:
                FireBullet(bullet, whereX, whereY);
                break;
            case VILLAIN2:
                if (player->X()>=480) {
                FireBullet(bullet, whereX-30, whereY+30);
                FireBullet(bullet, whereX+30, whereY-30);
                }
                else {
                    FireBullet(bullet, whereX + 30, whereY + 30);
                    FireBullet(bullet, whereX - 30, whereY - 30);
                }
                break;
            case VILLAIN3:
                if (player->X() >= 480) {
                    FireBullet(bullet, whereX - 50, whereY + 50);
                    FireBullet(bullet, whereX, whereY);
                    FireBullet(bullet, whereX + 50, whereY - 50);
                }
                else {
                    FireBullet(bullet, whereX - 50, whereY - 50);
                    FireBullet(bullet, whereX, whereY);
                    FireBullet(bullet, whereX + 50, whereY + 50);
                }
                
                break;
            case VILLAIN4:
                if (player->X() >= 480) {
                    FireBullet(bullet, whereX - 50, whereY + 50);
                    FireBullet(bullet, whereX - 10, whereY + 10);
                    FireBullet(bullet, whereX + 10, whereY - 10);
                    FireBullet(bullet, whereX + 50, whereY - 50);
                }
                else {
                    FireBullet(bullet, whereX + 50, whereY + 50);
                    FireBullet(bullet, whereX + 10, whereY + 10);
                    FireBullet(bullet, whereX - 10, whereY - 10);
                    FireBullet(bullet, whereX - 50, whereY - 50);
                }
                
                break;
            default:
                break;
            }   

            bulletsToShootInBurst--;
            if (bulletsToShootInBurst > 0) {
                bulletBurstCooldownTimer = bulletBurstCooldownMax;
            }
            else if (Level1::grassCut) {
                    spriteChangeCounter--;
            
                    if (spriteChangeCounter <= 0) {
                        currSprite++;
                        spriteChangeCounter = maxSpriteChangeCounter;
                    }
                }
        }
        //bulletsCooldownTimer -= gameTime;
        //bulletBurstCooldownTimer -= gameTime;
        //
        //if (bulletsCooldownTimer <= 0.0f) {
        //    if (currSprite == VILLAIN1) {
        //        bulletsToShootInBurst = 1;
        //    } else if (currSprite == VILLAIN2) {
        //        bulletsToShootInBurst = 2;
        //    } else if (currSprite == VILLAIN3) {
        //        bulletsToShootInBurst = 3;
        //    } else if (currSprite == VILLAIN4) {
        //        bulletsToShootInBurst = 4;
        //    }
        //
        //    bulletsCooldownTimer = bulletsCooldownMaxTimer;
        //    bulletBurstCooldownTimer = 0.0f;
        //}
        //
        //if (bulletsToShootInBurst > 0 && bulletBurstCooldownTimer <= 0.0f) {
        //    // Calcula para onde a bala deve ir (ponto final)
        //    Rect* playerBBox = static_cast<Rect*>(player->BBox());
        //    float whereX = playerBBox->Left() + (playerBBox->Right() - playerBBox->Left()) / 2.0f;
        //    float whereY = playerBBox->Top() + (playerBBox->Bottom() - playerBBox->Top()) / 2.0f;
        //    Bullet* b = new Bullet(bullet, whereX, whereY);
        //    b->MoveTo(x, y + spriteL->Height() / 2.0f, Layer::FRONT);
        //    Level1::scene->Add(b, MOVING);
        //
        //    bulletsToShootInBurst--;
        //
        //    if (bulletsToShootInBurst > 0) {
        //        bulletBurstCooldownTimer = bulletBurstCooldownMax;
        //    } else if (Level1::grassCut) {
        //        spriteChangeCounter--;
        //
        //        if (spriteChangeCounter <= 0) {
        //            currSprite++;
        //            spriteChangeCounter = maxSpriteChangeCounter;
        //        }
        //    }}
    }
}

// ---------------------------------------------------------------------------------

void Villain::OnCollision(Object * obj)
{
}

// ---------------------------------------------------------------------------------

void Villain::Draw()
{
    switch (currSprite) {
        case VILLAIN1:
            spriteL->Draw(x, y, Layer::UPPER);
            break;
        case VILLAIN2:
            spriteL2->Draw(x, y, Layer::UPPER);
            break;
        case VILLAIN3:
            spriteL3->Draw(x, y, Layer::UPPER);
            break;
        case VILLAIN4:
            spriteL4->Draw(x, y, Layer::UPPER);
            break;
        default:
            Level1::scene->Delete(this, STATIC);
            Level1::villainDead = true;
            break;
    }
}

// ---------------------------------------------------------------------------------

void Villain::FireBullet(Image* bulletImage, float targetX, float targetY) {
    Bullet* b = new Bullet(bulletImage, targetX, targetY);
    b->MoveTo(x, y + spriteL->Height()/ 2.0f, Layer::FRONT);
    Level1::scene->Add(b, MOVING);
}