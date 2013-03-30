#include <iostream>
#include <fstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace boost::property_tree;

static void parse_entity(std::ifstream &);
static void parse_entity_state(const ptree &);

void parse_entity(std::ifstream & ifs)
{
    ptree pt;
    read_json(ifs, pt);
    std::string name = pt.get_child("name").data();
    std::cout << "name : " << name << std::endl;
    ptree stateNodes = pt.get_child("states");
    for (auto s : stateNodes)
    {
        parse_entity_state ( s.second );
    }
}

void parse_entity_state(const ptree & pt)
{
    std::cout << "state :" << std::endl;

    std::string typeNode = pt.get_child("type").data();
    std::cout << "\ttype = " << typeNode.data() << std::endl;

    ptree movementNode = pt.get_child("movement");
    std::cout << "\tmovement :" << std::endl;

    ptree actionNode = movementNode.get_child("action");
    std::cout << "\t\taction = [";
    for (auto a : actionNode)
    {
        std::cout << " " << a.second.data();
    }
    std::cout << " ]" << std::endl;

    ptree directionNode = movementNode.get_child("direction");
    std::cout << "\t\tdirection = [";
    for (auto d : directionNode)
    {
        std::cout << " " << d.second.data();
    }
    std::cout << " ]" << std::endl;

    ptree viewNode = pt.get_child("view");
    ptree audioNode = viewNode.get_child("audio");
    ptree tilesetNode = viewNode.get_child("tileset");
    ptree physicsNode = pt.get_child("physics");
}

int main(int argc, const char *argv[])
{
    try
    {
        if (argc < 2)
        {
            std::cerr << "You must specify at least one JSON file to work with" 
                << std::endl;
        }
        else
        {
            std::ifstream ifs;
            ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            for (int i = 1; i < argc; i++)
            {
                const char * filename = argv[i];
                try
                {
                    ifs.open(filename);
                    std::cout << "Parsing JSON file \"" << filename
                        << "\"" << std::endl;
                    parse_entity(ifs);
                }
                catch (std::ifstream::failure e)
                {
                    std::cerr << "IOError for file \"" << filename 
                        << "\"" << std::endl;
                    ifs.clear();
                }
            }
        }
    }
    catch (std::exception e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
