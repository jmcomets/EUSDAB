#ifndef MAP_H
#define MAP_H

#include <entity.h>

class Map : public Entity
{
    public:

        Map(Map &&);

        virtual ~Map() { }

        View & view();

    private:
        View _view;

        Map();
        Map(Map const &);
        Map & operator = (Map const &);
};

#endif //MAP_H
