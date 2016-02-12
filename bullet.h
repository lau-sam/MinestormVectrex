#ifndef BULLET_H
#define BULLET_H

#include <QPoint>
#include <QImage>
#include <iostream>
#include <QLine>

/**
 * @author Tuan Nguyen <nguyen.tuan.contact@gmail.com>
 * @brief La classe Bullet représente l'objet Bullet (balle)
 * Une balle est définie par sa ligne et une image de balle
*/

class Bullet
{
public:
    /**
     * @brief Bullet construit l'objet Bullet
     * @param bulletLine ligne de direction de l'objet Bullet
     * @param bulletImage l'adresse de l'image de l'objet Bullet
     */
    Bullet(QLine &bulletLine,QImage &bulletImage);
    /**
     * @brief Bullet contructeur vide de Bullet
     */
    Bullet();
    /**
     * @brief ~Bullet destructeur de Bullet
     */
    ~Bullet();
    /**
     * @brief collideWithSpaceShip test s'il y a une collision entre la balle et un vaisseau
     * @param spaceShip to test
     * @return true if collision
     */
    bool collideWithSpaceShip(QLine spaceShipLine);
    //getters
    QLine getBulletLine();
    QImage getBulletImage();
    //setters
    void setBulletLine(QLine bulletLine);
    void setBulletImage(QImage bulletImage);

private:
    QLine _bulletLine;
    QImage _bulletImage;
};

#endif // BULLET_H
