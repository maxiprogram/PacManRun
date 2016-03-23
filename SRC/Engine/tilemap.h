#ifndef TILEMAP_H
#define TILEMAP_H

#include <QHash>
#include <QString>
#include <QFile>
#include <QXmlStreamReader>
#include <QtMath>

#include "setting.h"
#include "layer.h"
#include "transformer.h"
#include "sprite.h"
#include "managermesh.h"
#include "managershader.h"
#include "managertexture.h"
#include "managercamera.h"

class TileMap
{
public:
    TileMap();
    ~TileMap();
    static TileMap* getInstance();
    void SetMeshKey(int key);
    void SetShaderKey(int key);
    int GetTileWidth();
    int GetTileHeight();
    int GetTileCountWidth();
    int GetTileCountHeight();
    bool Load(QString filename);
    void Clear();
    void Destroy();
    void Draw();
    void Draw(QRectF rect);
    void Draw(QString layer_name);
    void Draw(QString layer_name, QRectF rect);
    QVector2D GetTileIJ(QVector3D pos);
    QRectF GetTilePos(QVector2D ij);
    bool CollisionX(QString layer_name, QVector3D& pos, QRectF bound, QVector2D dir);
    bool CollisionY(QString layer_name, QVector3D& pos, QRectF bound, QVector2D dir);
    QVector<Tile> GetTiles(QString layer_name, QRectF bound);
    Layer* GetLayer(QString layer_name);
private:
    static TileMap* instance;
    int key_mesh;
    int key_shader;
    QList<Sprite*> list_sprite;
    QList<DataLayer> list_layer;
    int count_x, count_y;
    int tile_width, tile_height;
};

#endif // TILEMAP_H
