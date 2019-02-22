#include <animationparser.h>
#include <istream>
#include <array>
#include <stdexcept>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <graphics/texturemanager.h>
#include <util/filename.h>

using namespace boost::property_tree;

namespace EUSDAB
{
    using namespace Util;

    AnimationParser::AnimationParser(const std::string & baseDirectory):
        _baseDirectory(Filename::clean(baseDirectory))
    {
    }

    // Concepts:
    //  - animDir is a valid path to the Animation's directory,
    //      and contains no trailing slashes
    Animation * AnimationParser::loadAnimation(const std::string & animDir)
    {
        std::string cleanedAnimDir = Filename::clean(animDir);
        Animation * animation = nullptr;
        auto it = _animations.find(cleanedAnimDir);
        if (it != _animations.end())
        {
            return new Animation(it->second);
        }
        else
        {
            std::string animFilename(Filename::join(_baseDirectory,
                        cleanedAnimDir, "animation.json"));
            std::ifstream animFile(animFilename.c_str());
            if (animFile.good())
            {
                animation = readAnimation(animFile, animDir);
            }
        }
        return animation;
    }

    // Concepts:
    //  - is is a "good" std::istream
    //  - animDir is a valid path to the Animation's directory,
    //      relative to the base directory,
    //      and contains no trailing slashes
    Animation * AnimationParser::readAnimation(std::istream & is,
            const std::string & animDir)
    {
        // Boost's magic
        ptree animationPt;
        try
        {
            read_json(is, animationPt);
        }
        catch (const ptree_error&)
        {
            std::cerr << "Animation JSON file invalid" << std::endl;
            return nullptr;
        }

        // Flip field
        try
        {
            const std::string & flip_from = animationPt.get<std::string>("flip");
            Animation * to_flip = loadAnimation(Filename::join(animDir, flip_from));
            if (to_flip == nullptr)
            {
                return nullptr;
            }
            else
            {
                Animation * a = addSharedAnimation(animDir, to_flip->flipped());
                delete to_flip;
                return a;
            }
        }
        catch (const ptree_error&)
        {
            // Nothing to do...
        }

        // Actual animation parsing
        Animation animation;

        // FPI field
        typedef Animation::FPI FPI;
        FPI fpi = animationPt.get<FPI>("fpi", Animation::DefaultFPI);
        animation.setFPI(fpi);

        // Frames container
        const ptree & framesPt = animationPt.get_child("frames");

        // Parse frames
        try
        {
            for (auto f : framesPt)
            {
                // Animation is dict frame filename -> frame,
                //  where the filename is relative to the
                //  Animation's directory
                std::string frameImagePath(Filename::join(_baseDirectory,
                            animDir, f.first));
                const ptree & hitboxesPt = f.second;

                // Load texture
                typedef Graphics::TextureManager TextureManager;
                typedef TextureManager::TexturePtr TexturePtr;
                TexturePtr tx = TextureManager::loadTexture(frameImagePath);

                // Shortcuts
                typedef Frame::Hitbox Hitbox;
                typedef Hitbox::AABB AABB;
                typedef AABB::Unit Unit;

                // Parse Hitboxes
                // List of different hitboxes
                std::array<Hitbox, 5> frameHitboxes = {{
                    Hitbox(Hitbox::Defense),
                    Hitbox(Hitbox::Attack),
                    Hitbox(Hitbox::Grabable),
                    Hitbox(Hitbox::Grab),
                    Hitbox(Hitbox::Foot),
                }};

                // Parse all AABBs
                for (auto p : hitboxesPt)
                {
                    const ptree & hb = p.second;
                    Unit x = hb.get<Unit>("center.x");
                    Unit y = hb.get<Unit>("center.y");
                    Unit width = hb.get<Unit>("width");
                    Unit height = hb.get<Unit>("height");

                    // Hitbox semantic
                    Hitbox::Semantic sem;
                    const std::string & semantic = hb.get<std::string>("semantic");
                    if (semantic == "defense") { sem = Hitbox::Defense; }
                    else if (semantic == "foot") { sem = Hitbox::Foot; }
                    else if (semantic == "attack") { sem = Hitbox::Attack; }
                    else if (semantic == "grab") { sem = Hitbox::Grab; }
                    else if (semantic == "grabable") { sem = Hitbox::Grabable; }
                    else { throw std::runtime_error("Unknown hitbox semantic"); }

                    // Ensure Hitbox is in set and add AABB to it
                    AABB frameAABB = AABB(x, y, width, height);
                    Hitbox & frameHitbox = *std::find(frameHitboxes.begin(),
                            frameHitboxes.end(), Hitbox(sem));
                    frameHitbox.addAABB(frameAABB);
                }

                // Add finalized frame to animation
                animation.addFrame(Frame(tx, frameHitboxes.begin(), 
                            frameHitboxes.end()));
            }
        }
        catch (const ptree_error&)
        {
            return nullptr;
        }
        return addSharedAnimation(animDir, animation);
    }

    Animation * AnimationParser::addSharedAnimation(const std::string & name,
            const Animation & animation)
    {
        _animations[name] = animation;
        return new Animation(animation);
    }

    std::string AnimationParser::baseDirectory() const
    {
        return _baseDirectory;
    }
}
