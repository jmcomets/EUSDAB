#ifndef GRAPHICS
#define GRAPHICS

namespace Graphics
{
    class Drawable:
    {
        public:
            Drawable();
            virtual ~Drawable();

            void render(Graphics::Target &, Graphics::Transformation);

        protected:
    };

    class Target:
    {
        public:
            Target();
            virtual ~Target();

        protected:
    };
}

#endif
