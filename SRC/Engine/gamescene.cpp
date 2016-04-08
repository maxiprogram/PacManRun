#include "gamescene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
    qDebug()<<"~GameScene";
}

void GameScene::AddGameObject(GameObject* object)
{
    QMultiHash<QString, GameObject*>::iterator it = ManagerGameObject::getInstance()->Add(object->GetName(), object);
    list_it.append(it);
}

void GameScene::DeleteGameObject(GameObject* object, bool scene)
{
    if (scene==true)
    {
        for (int i=0; i<list_it.size(); i++)
        {
            QMultiHash<QString, GameObject*>::iterator it = list_it.at(i);
            if (it.value()==object)
            {
                list_it.removeAt(i);
                break;
            }
        }
    }else
    {
        QMultiHash<QString, GameObject*>* hash_tab = ManagerGameObject::getInstance()->GetHashTab();
        for (int i=0; i<list_it.size(); i++)
        {
            QMultiHash<QString, GameObject*>::iterator it = list_it.at(i);
            if (it.value()==object)
            {
                hash_tab->remove(it.key(), it.value());
                delete object;
                list_it.removeAt(i);
                break;
            }
        }
    }
}

bool GameScene::Load(QString filename, CreatorGameObject* creator)
{
    Clear();
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly))
        return false;

    QXmlStreamReader reader(&f);

    while(!reader.atEnd() && !reader.hasError())
    {
        reader.readNext();
        if (reader.isStartElement())
        {
            //Считка массива вершин
            if (reader.name()=="Mesh")
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    qDebug()<<"Tag:"<<reader.name()<<"Id:"<<reader.attributes().value("id").toString();
                    Mesh* mesh = new Mesh();
                    mesh->Create();
                    ManagerMesh::getInstance()->Add(reader.attributes().value("id").toInt(),mesh);
                }
            }
            //Считка шейдера
            if (reader.name()=="Shader")
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    qDebug()<<"Tag:"<<reader.name()<<"Id:"<<reader.attributes().value("id").toString();
                    reader.readNext();
                    QString name = reader.text().toString();
                    QString tmp = name;
                    QString vert = tmp.replace(tmp.indexOf(";"), tmp.length()-tmp.indexOf(";"), "");
                    QString frag = name.replace(0, name.indexOf(";")+1, "");

                    qDebug()<<"Path vertex:"<<vert<<"Path fragment:"<<frag;
                    Shader* shader = new Shader;
                    shader->Load(vert, frag);
                    ManagerShader::getInstance()->Add(reader.attributes().value("id").toInt(), shader);
                }
            }
            //Считка текстуры
            if (reader.name()=="Texture")
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    QString tag_name = reader.name().toString();
                    int id = reader.attributes().value("id").toInt();
                    reader.readNext();
                    QString filename = reader.text().toString();
                    Texture* texture = new Texture(filename);
                    texture->Create();
                    ManagerTexture::getInstance()->Add(id, texture);
                    qDebug()<<"Tag:"<<tag_name<<"Id:"<<id<<"Path:"<<filename;
                }
            }
            //Считка спрайта
            if (reader.name()=="Sprite")
            {
                if (reader.attributes().hasAttribute("id"))
                {
                    int id = reader.attributes().value("id").toInt();
                    qDebug()<<"Tag:"<<reader.name()<<"Id:"<<id;
                    Sprite* sprite = new Sprite();
                    if (reader.attributes().hasAttribute("mid"))
                    {
                        sprite->SetMeshKey(reader.attributes().value("mid").toInt());
                    }
                    if (reader.attributes().hasAttribute("tid"))
                    {
                        sprite->SetTextureKey(reader.attributes().value("tid").toInt());
                    }
                    if (reader.attributes().hasAttribute("sid"))
                    {
                        sprite->SetShaderKey(reader.attributes().value("sid").toInt());
                    }
                    sprite->Create();
                    ManagerSprite::getInstance()->Add(id, sprite);
                }
            }
            //Считка шрифта
            if (reader.name()=="Font")
            {
                if (reader.attributes().hasAttribute("name"))
                {
                    QString tag_name = reader.name().toString();
                    QString name = reader.attributes().value("name").toString();
                    Font* font = new Font();
                    if (reader.attributes().hasAttribute("mid"))
                    {
                        font->SetMeshKey(reader.attributes().value("mid").toInt());
                    }
                    if (reader.attributes().hasAttribute("tid"))
                    {
                        font->SetTextureKey(reader.attributes().value("tid").toInt());
                    }
                    if (reader.attributes().hasAttribute("sid"))
                    {
                        font->SetShaderKey(reader.attributes().value("sid").toInt());
                    }
                    reader.readNext();
                    QString filename = reader.text().toString();
                    font->Load(filename);
                    font->Create();
                    ManagerFont::getInstance()->Add(name, font);
                    qDebug()<<"Tag:"<<tag_name<<"Name:"<<name<<"Path:"<<filename;
                }
            }
            //Считка тайл-карты
            if (reader.name()=="TileMap")
            {
                if (reader.attributes().hasAttribute("mid")==true && reader.attributes().hasAttribute("sid")==true)
                {
                    QString tag_name = reader.name().toString();
                    int mid = reader.attributes().value("mid").toInt();
                    int sid = reader.attributes().value("sid").toInt();            
                    reader.readNext();
                    QString filename = reader.text().toString();
                    TileMap::getInstance()->SetMeshKey(mid);
                    TileMap::getInstance()->SetShaderKey(sid);
                    TileMap::getInstance()->Load(filename);
                    qDebug()<<"Tag:"<<tag_name<<"mid:"<<mid<<"sid:"<<sid<<"Path:"<<filename;
                }
            }
            //Считка камеры
            if (reader.name()=="Camera")
            {
                if (reader.attributes().hasAttribute("name"))
                { 
                    QString name = reader.attributes().value("name").toString();
                    Camera* camera = new Camera();
                    if (reader.attributes().hasAttribute("type"))
                    {
                        camera->SetTypeCamera((TypeCamera)reader.attributes().value("type").toInt());
                    }
                    reader.readNext();
                    reader.readNext();
                    while (reader.isStartElement())
                    {
                        QString name = reader.name().toString();
                        //qDebug()<<"Name:"<<name;
                        reader.readNext();
                        if (name=="pos_x")
                        {
                            camera->SetPosX(reader.text().toString().toFloat());
                        }
                        if (name=="pos_y")
                        {
                            camera->SetPosY(reader.text().toString().toFloat());
                        }
                        if (name=="pos_z")
                        {
                            camera->SetPosZ(reader.text().toString().toFloat());
                        }
                        if (name=="rot_x")
                        {
                            camera->SetRotX(reader.text().toString().toFloat());
                        }
                        if (name=="rot_y")
                        {
                            camera->SetRotY(reader.text().toString().toFloat());
                        }
                        if (name=="rot_z")
                        {
                            camera->SetRotZ(reader.text().toString().toFloat());
                        }
                        reader.readNext();
                        reader.readNext();
                        reader.readNext();
                    }
                    qDebug()<<"Tag:"<<name<<"type:"<<camera->GetTypeCamera()<<"Pos:"<<camera->GetPos();
                    ManagerCamera::getInstance()->Add(name, camera);
                    ManagerCamera::getInstance()->SetCurrentCamera(name);
                }
            }
            //Считка игровых объектов
            if (reader.name()=="GameObject")
            {
                if (reader.attributes().hasAttribute("type"))
                {
                    uint type = reader.attributes().value("type").toUInt();
                    GameObject* obj = 0;
                    if (creator!=0)
                    {
                        obj = creator->CreateGameObject(type);
                    }
                    if (obj!=0)
                    {
                        if (reader.attributes().hasAttribute("name"))
                        {
                            obj->SetName(reader.attributes().value("name").toString());
                        }
                        qDebug()<<"Tag:"<<reader.name()<<"Type:"<<type<<"Name:"<<obj->GetName();
                        QMultiHash<QString, GameObject*>::iterator it = ManagerGameObject::getInstance()->Add(obj->GetName(), obj);
                        list_it.append(it);
                        QHash<QString,QString> property;

                        reader.readNext();
                        reader.readNext();
                        while (reader.isStartElement())
                        {
                            QString name = reader.name().toString();
                            reader.readNext();
                            QString value = reader.text().toString();
                            property.insert(name, value);
                            reader.readNext();
                            reader.readNext();
                            reader.readNext();
                            qDebug()<<"Name:"<<name<<"value:"<<value;
                        }

                        obj->Init(property);
                    }else
                        qDebug()<<"Error Create GameObject";

                }
            }
        }

    }
    f.close();

    if (reader.hasError())
        return false;

    return true;
}

void GameScene::Update(float dt)
{
    for (int i=0; i<list_it.size(); i++)
    {
        QMultiHash<QString, GameObject*>::iterator it = list_it.at(i);
        GameObject* obj = it.value();     
        obj->Update(dt);
    }
}

void GameScene::Draw()
{
    for (int i=0; i<list_it.size(); i++)
    {
        QHash<QString, GameObject*>::iterator it = list_it.at(i);
        GameObject* obj = it.value();
        obj->Draw();
    }
}

void GameScene::Draw(QRectF rect)
{
    for (int i=0; i<list_it.size(); i++)
    {
        QHash<QString, GameObject*>::iterator it = list_it.at(i);
        GameObject* obj = it.value();

        QVector3D pos = obj->GetPos();
        QVector3D scal = obj->GetScal();
        QVector3D pivot = obj->GetPivot();
        QRectF rect_pos;
        rect_pos.setLeft(pos.x()-scal.x()*pivot.x());
        rect_pos.setTop(pos.y()-scal.y()*pivot.y());
        rect_pos.setWidth(scal.x());
        rect_pos.setHeight(scal.y());
        if (rect_pos.intersects(rect))
            obj->Draw();
    }
}

void GameScene::Clear()
{
    QMultiHash<QString, GameObject*>* hash_tab = ManagerGameObject::getInstance()->GetHashTab();
    for (int i=0; i<list_it.size(); i++)
    {
        QMultiHash<QString, GameObject*>::iterator it = list_it.at(i);
        GameObject* obj = it.value();
        hash_tab->remove(it.key(), it.value());
        delete obj;
    }
    list_it.clear();
}
