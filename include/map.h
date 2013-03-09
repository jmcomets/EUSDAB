#ifndef MAP_H
#define MAP_H

#include <vector>
#include <entity.h>
#include <platform.h>
#include <character.h>

class Map: public Entity
{
    public:

        Map(...);
        Map(Map &&) = delete;
        virtual ~Map() { }

        View & view();
        std::string const & name();
        void name(std::string const & name);
        void addPlatform(Platform * platform);
        void removePlatform(Platform * platform);
        void addCharacter(Character * character);
        void removeCharacter(Character * character);

    protected:
        std::string _name;
        View _view;
        std::vector<Platform *> _platforms;
        std::vector<Character *> _characters;

        Map();
        Map(Map const &);
        Map & operator = (Map const &);
};

#endif //MAP_H
