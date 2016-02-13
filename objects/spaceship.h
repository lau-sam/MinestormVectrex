#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "bullet.h"
#include "gameobject.h"

/**
 * @brief La classe SpaceShip représente l'objet SpaceShip
 * Un SpaceShip est défini par sa ligne et son image
 * Elle fournit les services de base pour controler un SpaceShip :
 * - accelerate/breakdown/turnLeft/turnRight
 * - gestion de tire utilisant une liste d'objets de type Bullet
*/
class SpaceShip : public GameObject
{
public:
    /**
     * @brief SpaceShip contruit un vaisseau
     * @param line ligne de direction du vaisseau
     * @param shipImage l'adresse de l'image du vaisseau
     */
    SpaceShip(QLine &line, QImage &shipImage);
    /**
     * @brief SpaceShip contruit un vaisseau vide
     */
    SpaceShip();

    /**
     * @brief ~SpaceShip détruit le vaisseau
     */
    ~SpaceShip();
    void draw(QPainter &painter);
    /**
     * @brief accelerate augmente la vitesse du vaisseau
     * en réduisant la variable _speed
     * 1<_speed<45 , à 1 le vaisseau atteint sa vitesse max
     */
    void accelerate();
    /**
     * @brief breakdown réduit la vitesse du vaisseau
     * en augmentant la variable _speed
     * 1<_speed<45 , à 45 le vaisseau s'arrete
     */
    void breakdown();
    /**
     * @brief turnLeft tourne la ligne _shipLine à gauche d'angle _angle
     */
    void turnLeft();
    /**
     * @brief turnRight tourne la ligne _shipLine à droite d'angle _angle
     */
    void turnRight();
    /**
     * @brief shoot créer un objet Bullet
     * @return l'objet Bullet du vaisseau
     */
    Bullet shoot();
    /**
     * @brief spaceShipOverScreenControle controle si le SpaceShip sort de l'écran.
     * Faire apparaitre sur le coté opposé de l'écran quand le SpaceShip sort de l'écran.
     * @param width la largeur de la zone de jeu
     * @param height la hauteur de la zone de jeu
     */
    void spaceShipOverScreenControle(int width, int height);
    //getters
    int getAngle();
    int getSpeed();
    QPoint getPointSpeed();
    //setters
    void setSpeed(int speed);
    void setAngle(int angle);
    void setPointSpeed(QPoint pointSpeed);

private:
    QPoint _pointSpeed;
    int _angle;
    int _speed;
};

#endif // SPACESHIP_H
