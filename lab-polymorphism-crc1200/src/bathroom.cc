#include "bathroom.hpp"

Bathroom::Bathroom(): Room("bathroom") {}

bool Bathroom::CanAddPerson() const {
    return people_.empty();
}



