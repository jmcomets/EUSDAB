#include <animationparser.h>
#include <istream>
#include <array>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <texturemanager.h>

using boost::lexical_cast;
using namespace boost::property_tree;

namespace EUSDAB
{
    Animation * AnimationParser::loadAnimation(const std::string & animDir) const
    {
        Animation * animation = nullptr;
        std::string animFilename(animDir + "/animation.json");
        std::ifstream animFile(animFilename.c_str());
        if (animFile.good())
        {
            animation = readAnimation(animFile, animDir);
        }
        return animation;
    }

    // Concepts:
    //  - is is a "good" std::istream
    //  - animDir is a valid path to the Animation's directory,
    //      and contains no trailing slashes
    Animation * AnimationParser::readAnimation(std::istream & is,
            const std::string & animDir) const
    {
        // Boost's magic
        ptree animationPt;
        try
        {
            read_json(is, animationPt);
        }
        catch (ptree_error)
        {
            std::cerr << "Animation JSON file invalid" << std::endl;
            return nullptr;
        }

        // Actual animation parsing
        Animation * animation = new Animation();
        try
        {
            for (auto a : animationPt)
            {
                // Animation is dict frame filename -> frame,
                //  where the filename is relative to the
                //  Animation's directory
                std::string frameImagePath(animDir + "/" + a.first);
                const ptree & hitboxesPt = a.second;

                // Load texture
                typedef Graphics::TextureManager TextureManager;
                typedef TextureManager::TexturePtr TexturePtr;
                TexturePtr tx = TextureManager::loadTexture(frameImagePath);

                // Shortcuts
                typedef Frame::Hitbox Hitbox;
                typedef Hitbox::AABB AABB;
                typedef AABB::Unit Unit;
                typedef AABB::Vector2 Vector2;

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
                    Unit x = lexical_cast<Unit>(hb.get<std::string>("center.x"));
                    Unit y = lexical_cast<Unit>(hb.get<std::string>("center.y"));
                    Unit width = lexical_cast<Unit>(hb.get<std::string>("width"));
                    Unit height = lexical_cast<Unit>(hb.get<std::string>("height"));

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
                    AABB frameAABB = AABB(Vector2(x, y), width, height);
                    Hitbox & frameHitbox = *std::find(frameHitboxes.begin(),
                            frameHitboxes.end(), Hitbox(sem));
                    frameHitbox.addAABB(frameAABB);
                }

                // Add finalized frame to animation
                animation->addFrame(Frame(tx, frameHitboxes.begin(), 
                            frameHitboxes.end()));
            }
        }
        catch (ptree_error)
        {
            delete animation;
            animation = nullptr;
        }
        return animation;
    }
}
