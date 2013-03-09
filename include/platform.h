#ifndef PLATFORM_H
#define PLATFORM_H

#include <entity.h>
#include <view.h>

class Platform: public Entity
{
    public:
        Platform();
        virtual ~Platform();
        const std::string & name();
        void name(const std::string &);
        const View & view();

    private:
        std::string _name;
        View _view;
};

#endif
