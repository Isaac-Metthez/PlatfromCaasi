#include "Config.h"

namespace platfrom
{
    namespace hmi
    {
#pragma region Config 

        Config::Config()
        {
            CreateDirectoryA(PLATFROM_DATA, NULL);
            CreateDirectoryA(CONFIG_DIR, NULL);
            std::string dummy;
            std::ifstream is(getPath());
            if (!is.is_open())
                save();
            else
                is >>
                dummy >> dummy >> _logEvents >>
                dummy >> dummy >> _showHitBox >>
                dummy >> dummy >> _creative;
            is.close();
        }

        Config::~Config()
        {
        }

        void Config::save()
        {
            std::ofstream os(getPath());
            os << "Log \t\t: " << _logEvents << "\n"
                << "HitBox \t\t: " << _showHitBox << "\n"
                << "Creative \t: " << _creative << "\n";
            os.close();
        }

        std::string Config::getPath()
        {
            std::string path(CONFIG_DIR);
            path += "\\";
            path += CONFIG_FILE;
            return path;
        }
#pragma endregion
    }
}
