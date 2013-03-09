#ifndef PLATFORM_H
#define PLATFORM_H

#include <entity.h>
#include <view.h>

class Platform : public Entity
{
    public:

        Platform();
        virtual ~Platform();

        string const & name();
        void name(string const &);
        View const & view();

    protected:
        string _name;
        View _view;

};

#endif
