#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"

/**
 * @author Tuan Nguyen <nguyen.tuan.contact@gmail.com>
 * @brief La classe Bullet représente l'objet Bullet (balle)
 * Une balle est définie par sa ligne et une image de balle
*/

class Bullet : public GameObject
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
    void draw(QPainter &painter);
    void bang();
};

#endif // BULLET_H
