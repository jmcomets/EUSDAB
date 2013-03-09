#ifndef DRAWABLE_H
#define DRAWABLE_H

class Drawable
{
    public:
        Drawable();
        virtual ~Drawable();

        void render(Graphics::Target &, Graphics::Transformation);

    protected:



#endif
