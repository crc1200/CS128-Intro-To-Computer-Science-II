#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "room.hpp"

class Kitchen: public Room {
    public:
        Kitchen(); 
    protected:
        bool CanAddPerson() const;
    private:
};

#endif  // KITCHEN_HPP