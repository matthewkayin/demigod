//Demigod
//entity.hpp
//The entity class is for living objects in the world

#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity{

public:
    Entity();
    ~Entity();

    int getX() const;
    int getY() const;
    void setPos(const int nx, const int ny);
    void incX(const int n); //x += n
    void incY(const int n); //y += n

    int getHealth() const;
    void setHealth(const int h);
    void takeDamage(const int h); //health += h

    std::string getImage() const; //return the image key associated with the entity
    void setImage(const std::string key);
private:
    int x;
    int y;
    int health;
    std::string image;
};

#endif
