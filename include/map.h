#ifndef MAP_H
#define MAP_H

#include <entity.h>
#include <platform.h>

class Map: public Entity
{
    public:

        Map(...);
        Map(Map &&);
        virtual ~Map() { }

        View & view();
        string const & name();
        void name(string const & name);
        void addPlatform(Platform * platform);
        Platform * removePlatform(Platform * platform);
        void addCharacter(Character * character);
        Character * removeCharacter(Character * character);

    protected:
        string _name;
        View _view;
        std::vector<Platform *> _platforms;
        std::vector<Character *> _characters;

        Map();
        Map(Map const &);
        Map & operator = (Map const &);
};

#endif //MAP_H
