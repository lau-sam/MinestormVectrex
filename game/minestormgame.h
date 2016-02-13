#ifndef MINESTORMGAME_H
#define MINESTORMGAME_H
#include "game.h"

#include <QPoint>
#include <QBrush>
#include <QImage>
#include <vector>
#include <QRect>
#include <QLine>
#include <QPainter>
#include "objects/spaceship.h"
#include "objects/mine.h"
#include <sstream>

using namespace std;
/**
 * @brief La classe MinestormGame utilise la classe Game représentant la base du jeu Mindstorm
 * Voir game.h
 *
 */
class MinestormGame : public Game
{
    Q_OBJECT
public:
    MinestormGame(const QSize &size,QObject *parent = nullptr);
    virtual void draw(QPainter &painter, QRect &rect) override;
    void mousePressed( int x, int y) override;
    void keyPressed( int key ) override;
    void keyReleased( int key ) override;
    void mouseReleased( int x, int y) override;
    void mouseMoved(int x, int y) override;

private:
    virtual void step();
    void initialize();
    /**
     * @brief addSpaceShipBullet ajoute un objet Bullet à la liste _spaceShipBullets
     * @param bullet l'objet Bullet à ajouter
     */
    void addSpaceShipBullet(Bullet bullet);
    /**
     * @brief addEnemyBullet ajoute un objet Bullet à la liste _enemiesBullets
     * @param bullet l'objet Bullet à ajouter
     */
    void addEnemyBullet(Bullet bullet);
    /**
     * @brief generateEnemy genere un objet de type SpaceShip par rapport à la hauteur et la largeur
     * Ajouter à la liste _enemies après la création
     * @param width la largeur de la zone de jeu
     * @param height la hauteur de la zone de jeu
     */
    void generateEnemy(int width, int height);
    /**
     * @brief generateMines genere un objet de type Mine par rapport à la hauteur et la largeur
     * Ajouter à la liste _mines après la création
     * @param width
     * @param height
     */
    void generateMines(int width, int height);
    /**
     * @brief drawSpaceShip draw spaceship and spaceship movs
     * @param painter
     */
    void drawSpaceShip(QPainter &painter);
    /**
     * @brief drawEnemies draw et movs de _enemies
     * @param painter
     */
    void drawEnemies(QPainter &painter);
    /**
     * @brief drawMines
     * @param painter
     */
    void drawMines(QPainter &painter);
    /**
     * @brief drawEnemiesBullets draw et movs de _enemiesBullets
     * @param painter
     * @param rect
     */
    void drawEnemiesBullets(QPainter &painter, QRect &rect);
    /**
     * @brief drawSpaceShipBullets draw et movs de _spaceShipBullets
     * @param painter
     * @param rect
     */
    void drawSpaceShipBullets(QPainter &painter, QRect &rect);
    void drawHearth(QPainter &painter, QRect &rect);
    /**
     * @brief drawScore affiche le score en haut à gauche de l'écran
     * @param painter
     */
    void drawScore(QPainter &painter,QRect &rect);
    /**
     * @brief testKeys verifie si une touche est pressed
     */
    void testKeys();
    /**
     * @brief showCinematics vide
     * @param painter
     * @param rect
     */
    void showCinematics(QPainter &painter, QRect &rect);

    vector<SpaceShip> _enemies;
    SpaceShip _spaceShip;
    Qt::BrushStyle _currentStyle;
    vector<Bullet> _spaceShipBullets;
    vector<Bullet> _enemiesBullets;
    vector<Mine> _mines;
    vector<QPoint> _hearths;
    int _hearthGenerateTime;
    int _spaceShipShootControl;
    int _enemyShootIntervalle;
    int _enemyGenerateTime;
    int _health;
    int _score;
    bool _keyLeft;
    bool _keyRight;
    bool _keyUp;
    bool _keyDown;
    bool _keyS;
    bool _keyR;
    bool _gamePaused;

};

#endif // MINESTORMGAME_H
