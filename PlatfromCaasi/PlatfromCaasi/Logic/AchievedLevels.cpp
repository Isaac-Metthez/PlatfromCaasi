#include "AchievedLevels.h"
#include "../Platfrom.h"

namespace platfrom
{
    namespace logic
    {
#pragma region AchivedLevels 
        AchievedLevels::AchievedLevels()
        {
            CreateDirectoryA(PLATFROM_DATA, NULL);
            CreateDirectoryA(ACHIEVED_DIR, NULL);
        }

        void AchievedLevels::addAchievedLevel(std::string name)
        { 
            if (!isAchieved(name))
                _achievedLevels.push_back(name); 
        }

        bool AchievedLevels::isAchieved(std::string& name)
        {
            for (auto& doneMap : _achievedLevels)
                if (name == doneMap)
                    return true;
            return false;
        }
        void AchievedLevels::reload()
        {
            _achievedLevels.clear();
            int nb = 0;
            std::ifstream is(getPath());
            if (is.is_open())
            {
                is >> nb ;
                _achievedLevels.reserve(nb);
                for (int i = 0; i < nb; i++)
                {
                    _achievedLevels.emplace_back();
                    is >> _achievedLevels.back() ;
                }
                is.close();
            }
        }

        void AchievedLevels::save()
        {
            std::ofstream os(getPath());
            os << _achievedLevels.size() << "\n";
            for (auto& level : _achievedLevels)
                os << level << "\n";
            os.close();
            Platfrom::getEventLogger().addLogEvent("Save achieved levels");
        }

        std::string AchievedLevels::getPath()
        {
            std::string path(ACHIEVED_DIR);
            path += "\\";
            path += LEVEL_FILE;
            return path;
        }
#pragma endregion
    }
}
