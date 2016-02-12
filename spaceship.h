#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <QLine>
#include <QPoint>
#include <math.h>
#include <QImage>
#include <iostream>
#include "bullet.h"

/**
 * @brief La classe SpaceShip représente l'objet SpaceShip
 * Un SpaceShip est défini par sa ligne et son image
 * Elle fournit les services de base pour controler un SpaceShip :
 * - accelerate/breakdown/turnLeft/turnRight
 * - gestion de tire utilisant une liste d'objets de type Bullet
*/
class SpaceShip
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
     * @brief turnLeft tourne la ligne _shipLine à gauche d'angle _directionAngle
     */
    void turnLeft();
    /**
     * @brief turnRight tourne la ligne _shipLine à droite d'angle _directionAngle
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
    QLine getShipLine();
    QImage getShipImage();
    int getDirectionAngle();
    int getSpeed();
    QPoint getPointSpeed();
    //setters
    void setSpeed(int speed);
    void setShipImage(QImage shipImage);
    void setDirectionAngle(int directionAngle);
    void setShipLine(QLine shipLine);
    void setPointSpeed(QPoint pointSpeed);

private:
    /**
     * @brief rotatePoint faire une rotation du QPoint ptRotate autour du QPoint origin un angle degree
     * @param degree l'angle de rotation
     * @param origin QPoint representant le point central
     * @param ptRotate QPoint representant le point à appliquer la rotation
     * @return QPoint représentant les nouvelles coordonnées du QPoint ptRotate
     */
    QPoint rotatePoint(int degree, QPoint origin, QPoint ptRotate);

    QLine _shipLine;
    QImage _shipImage;
    QPoint _pointSpeed;
    int _directionAngle;
    int _speed;
};

#endif // SPACESHIP_H
