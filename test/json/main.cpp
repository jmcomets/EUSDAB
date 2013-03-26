#include <iostream>
#include <fstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

static void parse_character_json(std::ifstream & ifs)
{
    using namespace boost::property_tree;
    ptree pt;
    read_json(ifs, pt);
    auto stateNodes = pt.get_child("states");
    for (auto s : stateNodes)
    {
        std::cout << "state :" << std::endl;

        std::string typeNode = s.second.get_child("type").data();
        std::cout << "\ttype = " << typeNode.data() << std::endl;

        auto movementNode = s.second.get_child("movement");
        std::cout << "\tmovement :" << std::endl;

        auto actionNode = movementNode.get_child("action");
        std::cout << "\t\taction = [";
        for (auto a : actionNode)
        {
            std::cout << " " << a.second.data();
        }
        std::cout << " ]" << std::endl;

        auto directionNode = movementNode.get_child("direction");
        std::cout << "\t\tdirection = [";
        for (auto d : directionNode)
        {
            std::cout << " " << d.second.data();
        }
        std::cout << " ]" << std::endl;
    }
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
                    parse_character_json(ifs);
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
