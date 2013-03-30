#include <iostream>
#include <fstream>
#include <string>
#include <entity.h>
#include <parsers/json.h>

using namespace EUSDAB;

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
            Parsers::Base * parser = new Parsers::Json();
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
                    Entity * e = parser->read(ifs);
                    if (e != nullptr)
                    {
                        std::cout << "<Entity> {" << std::endl
                            << "name: " << e->name() << "," << std::endl
                            << "state: " << e->state() << std::endl
                            << "}" << std::endl;
                        delete e;
                    }
                }
                catch (std::ifstream::failure e)
                {
                    std::cerr << "IOError for file \"" << filename 
                        << "\"" << std::endl;
                    ifs.clear();
                }
            }
            delete parser;
        }
    }
    catch (std::exception e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
