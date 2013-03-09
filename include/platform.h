#ifndef PLATFORM_H
#define PLATFORM_H

#include <entity.h>
#include <view.h>

class Platform : public Entity
{
    public:

        Platform();
        virtual ~Platform();

        std::string const & name();
        void name(std::string const &);
        View const & view();

    protected:
        std::string _name;
        View _view;

};

#endif
