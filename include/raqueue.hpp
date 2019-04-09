//Demigod
//Matt Madden
//raqueue.hpp - The ra queue is a custom queue class that is meant to provide simple FIFO with a cap for storage while also giving random access to elements
//Assumption - I assumed this was only going to be used with strings, so I didn't bother trying to relearn how templates work when making the data structure

#ifndef RAQUEUE_H
#define RAQUEUE_H

#include <string>

class Raqueue{

public:
    Raqueue();
    ~Raqueue();
    void init(int max);
    std::string at(int index);
    void push(std::string value);
    int size();
private:
    std::string *data;
    int head;
    int sz;
};

#endif
