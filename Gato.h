#ifndef GATO_H
#define GATO_H

#include "Animal.h"

class Gato : public Animal
{
    public:
        string que_come();
        bool requiere_ducha();
};

#endif