#include "entity.hpp"

Entity::Entity(){

    x = -1;
    y = -1;
    health = 0;
    image = "";
}

//tbh not sure why I made a destructor
Entity::~Entity(){}

int Entity::getX() const{

   return x;
}

int Entity::getY() const{

    return y;
}

void Entity::setPos(const int nx, const int ny){

    x = nx;
    y = ny;
}

void Entity::incX(const int n){

    x += n;
}

void Entity::incY(const int n){

    y += n;
}

int Entity::getHealth() const{

    return health;
}

void Entity::setHealth(const int h){

    health = h;
}

void Entity::takeDamage(const int h){

    health -= h;
}

std::string Entity::getImage() const{

    return image;
}

void Entity::setImage(const std::string key){

    image = key;
}
