#include "raqueue.hpp"

Raqueue::Raqueue(){

    data = nullptr;
    head = 0;
    sz = 0;
}

Raqueue::~Raqueue(){

    delete data;
}

void Raqueue::init(int max){

    sz = max;
    data = new std::string[sz];
    for(int i = 0; i < sz; i++){

        data[i] = "";
    }
}

std::string Raqueue::at(int index){

    if(data == nullptr){

        return "ERROR, tried to access element of empty Raqueue";
    }

    int toAccess = head + index;
    if(toAccess >= sz){

        toAccess -= sz;
    }
    if(toAccess >= sz){

        return "ERROR, tried to access out of bounds element in Raqueue";
    }

    return data[toAccess];
}

void Raqueue::push(std::string value){

    data[head] = value;
    head++;
    if(head >= sz){

        head -= sz;
    }
}

int Raqueue::size(){

    return sz;
}
