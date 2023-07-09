#include "Map.h"

namespace platfrom
{
    namespace map
    {
        constexpr auto FOLDER_PATH = "..\\Map";
        POC::POC()
        {
            CreateDirectoryA(FOLDER_PATH, NULL);
        }

        void POC::walk()
        {
            std::string path(FOLDER_PATH);
            path += "\\Level000.caasi";
            std::ofstream os(path);

            os
                << "Walk\n"
                << logic::blocks::Block(
                    { -1000, 500 },
                    { {0, 0},{10000, 0},{10000, 100},{0, 100} },
                    logic::blocks::matter::None,
                    { new logic::blocks::decorators::Hurting })
                << logic::blocks::Block(
                    { 0, 50 },
                    { {-50, 0},{3000, 0},{3000, 20},{-50, 20} },
                    logic::blocks::matter::Dirt,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 500, 50 },
                    { {-20, 0},{20, 0},{20, -180},{-20, -180} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 500, -300 },
                    { { -20, 0},{20, 0},{20, 10},{-20, 10} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::OneWay })
                << logic::blocks::Block(
                    { 1000, 50 },
                    { {-20, 0},{20, 0},{20, -180},{-20, -180} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple });
            for (int i = 0; i < 10; i++)
                os << logic::FireBall({ 500, -400 });
            for (int i = 0; i < 6; i++)
                os << logic::mobs::SimpleMob({ static_cast<float>(550 + i * 50), 0 }, true);
            os << logic::blocks::Block(
                    { 1500, 50 },
                    { {-20, 0},{20, 0},{20, -180},{-20, -180} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 2000, 50 },
                    { {-20, 0},{20, 0},{20, -180},{-20, -180} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple });
            for (int i = 0; i < 5; i++)
                os << logic::mobs::PortableMob({ static_cast<float>(1550 + i * 50), 0 }, true);
            os << logic::blocks::Block(
                    { 2500, 50 },
                    { {0, 0},{20, 0},{20, -100},{0, -100} },
                    logic::blocks::matter::Finish,
                    { new logic::blocks::decorators::Finish });


            os.close();
            std::cout << "File: (" << path << ") as been saved" << std::endl;
        }

        void POC::web()
        {
            std::string path(FOLDER_PATH);
            path += "\\Level001.caasi";
            std::ofstream os(path);

            os
                << "Web\n"
                << logic::blocks::Block(
                    { -1000, 500 },
                    { {0, 0},{10000, 0},{10000, 100},{0, 100} },
                    logic::blocks::matter::None,
                    { new logic::blocks::decorators::Hurting })
                << logic::blocks::Block(
                    { 0, 50 },
                    { {-50, 0},{3000, 0},{3000, 20},{-50, 20} },
                    logic::blocks::matter::Dirt,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 150, 50 },
                    { {0, 0},{20, 0},{20, -180},{0, -180} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 300, 50 },
                    { {0, 0},{20, 0},{20, -180},{0, -180} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 320, 50 },
                    { {0, 0},{580, 0},{580, -2000},{0, -2000} },
                    logic::blocks::matter::Web,
                    { new logic::blocks::decorators::Web })
                << logic::blocks::Block(
                    { 1000, 50 },
                    { {0, 0},{100, 0},{100, -180},{0, -180} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple });
            for (int i = 0; i < 18; i++)
                os << logic::blocks::Block(
                    { static_cast<float>(1100+i*20), 50 },
                    { {0, 0},{20, 0},{10, -30} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple ,
                     new logic::blocks::decorators::Hurting });
            os << logic::blocks::Block(
                { 1700, 50 },
                { {-20, 0},{20, 0},{20, -180},{-20, -180} },
                logic::blocks::matter::Stone,
                { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 1700, -300 },
                    { { -20, 0},{20, 0},{20, 10},{-20, 10} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::OneWay });
            for (int i = 0; i < 10; i++)
                os << logic::FireBall({ 1700, -400 });
            for (int i = 0; i < 5; i++)
                os << logic::mobs::SimpleMob({ static_cast<float>(1800 + i*50), 0 }, true);
            os  << logic::blocks::Block(
                { 2000, 50 },
                { {-20, 0},{20, 0},{20, -180},{-20, -180} },
                logic::blocks::matter::Stone,
                { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 1980, -130 },
                    { {-10, 0},{0, 0},{0, -10},{-10, -10} },
                    logic::blocks::matter::None)
                << logic::blocks::Block(
                    { 2020, -130 },
                    { {10, 0},{0, 0},{0, -10},{10, -10} },
                    logic::blocks::matter::None)
                << logic::mobs::SimpleMob({ 2000, -130 }, false);
            os << logic::blocks::Block(
                { 2500, 50 },
                { {0, 0},{20, 0},{20, -100},{0, -100} },
                logic::blocks::matter::Finish,
                { new logic::blocks::decorators::Finish });
            os.close();
            std::cout << "File: (" << path << ") as been saved" << std::endl;
        }

        void POC::air()
        {
            std::string path(FOLDER_PATH);
            path += "\\Level002.caasi";
            std::ofstream os(path);

            os
                << "Air\n"
                << logic::blocks::Block(
                    { -1000, 500 },
                    { {0, 0},{10000, 0},{10000, 100},{0, 100} },
                    logic::blocks::matter::None,
                    { new logic::blocks::decorators::Hurting })
                << logic::blocks::Block(
                    { 0, 50 },
                    { {-50, 0},{50, 0},{50, 20},{-50, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 150, 0 },
                    { {-50, 0},{50, 0},{50, 20},{-50, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 350, 0 },
                    { {-50, 0},{50, 0},{50, 20},{-50, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 600, 0 },
                    { {-50, 0},{50, 0},{50, 20},{-50, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple,
                      new logic::blocks::decorators::Bouncing })
                << logic::blocks::Block(
                    { 600, -400 },
                    { {-50, 0},{50, 0},{50, 20},{-50, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple });
            for (int i = 0; i < 3; i++)
                os << logic::FireBall({ 600, -500 });
            os << logic::blocks::Block(
                    { 1100, 0 },
                    { {-50, 0},{50, 0},{50, 20},{-50, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 1100, 0 },
                    { {-10, -500},{10, -500},{10, 0},{-10, 0} },
                    logic::blocks::matter::Lader,
                    { new logic::blocks::decorators::Lader })
                << logic::blocks::Block(
                    { 1100, -500 },
                    { {-50, 0},{50, 0},{50, 10},{-50, 10} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::OneWay })
                << logic::mobs::SimpleMob({ 1100, -500 }, true)
                << logic::blocks::Block(
                    { 1150, -500 },
                    { {5, 0},{0, 0},{0, -5},{5, -5} },
                    logic::blocks::matter::None)
                << logic::blocks::Block(
                    { 1050, -500 },
                    { {-5, 0},{0, 0},{0, -5},{-5, -5} },
                    logic::blocks::matter::None)
                << logic::blocks::Block(
                    { 1300, -600 },
                    { {0, 10},{0, 0},{50, 0},{600, 600},{550, 600} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 1900, 0 },
                    { {-50, 0},{50, 0},{50, 20},{-50, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 2300, -500 },
                    { {-50, 0},{50, 0},{50, 10},{-50, 10} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::mobs::PortableMob({ 2300, -500 }, true)
                << logic::blocks::Block(
                    { 2350, -500 },
                    { {5, 0},{0, 0},{0, -5},{5, -5} },
                    logic::blocks::matter::None)
                << logic::blocks::Block(
                    { 2250, -500 },
                    { {-5, 0},{0, 0},{0, -5},{-5, -5} },
                    logic::blocks::matter::None)
                << logic::blocks::Block(
                    { 2000, 0 },
                    { {-10, -500},{10, -500},{10, 0},{-10, 0} },
                    logic::blocks::matter::Lader,
                    { new logic::blocks::decorators::Lader });

            for (int i = 0; i < 7; i++)
                os << logic::mobs::PortableMob({ static_cast<float>(2850 + i*50), -300 }, true);
                os << logic::blocks::Block(
                    { 2800, -300 },
                    { {0, 0},{400, 0},{400, 10},{0, 10} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 3200, -300 },
                    { {40, 10},{0, 10},{0, -40},{40, -40} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 2800, -300 },
                    { {-40, 10},{0, 10},{0, -40},{-40, -40} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple });
            for (int i = 0; i < 10; i++)
                os << logic::blocks::Block(
                    { static_cast<float>( 3400 + i * 100), static_cast<float>(-400 - i*100) },
                    { {0, 0},{100, 0},{100, 20},{0, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple });
            os << logic::blocks::Block(
                { 4400, -1400 },
                { {0, 0},{2000, 0},{2000, 20},{0, 20} },
                logic::blocks::matter::Stone,
                { new logic::blocks::decorators::Simple });
            for (int i = 0; i < 20; i++)
                os << logic::mobs::PortableMob({ static_cast<float>(4500 + i * 50), -1500 }, false);
            os << logic::blocks::Block(
                { 5400, -1400 },
                { {0, 0},{20, 0},{20, -100},{0, -100} },
                logic::blocks::matter::Finish,
                { new logic::blocks::decorators::Finish });
            os.close();
            std::cout << "File: (" << path << ") as been saved" << std::endl;
        }

        void POC::pole()
        {
            std::string path(FOLDER_PATH);
            path += "\\Level003.caasi";
            std::ofstream os(path);

            os
                << "Pole\n"
                << logic::blocks::Block(
                    { -1000, 500 },
                    { {0, 0},{10000, 0},{10000, 100},{0, 100} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Hurting });
            for (int i = 0; i < 5; i++)
                os << logic::blocks::Block(
                    { static_cast<float>(i * 200), 0 },
                    { {-25, static_cast<float>(50 - i * 100)},{25, static_cast<float>(50 - i * 100)},{25, 500},{-25, 500} },
                    logic::blocks::matter::Dirt,
                    { new logic::blocks::decorators::Simple });
            for (int i = 0; i < 10; i++)
                os << logic::blocks::Block(
                        { static_cast<float>(1000 + i * 200), 0 },
                        { {-25, static_cast<float>(-450 - i * 100)},{25, static_cast<float>(-450 - i * 100)},{25, 500},{-25, 500} },
                        logic::blocks::matter::Dirt,
                        { new logic::blocks::decorators::Simple })
                    << logic::mobs::PortableMob({ static_cast<float>(1000 + i * 200), static_cast<float>(-450 - i * 100) }, true)
                    << logic::blocks::Block(
                        { static_cast<float>(1025 + i * 200), static_cast<float>(-450 - i * 100) },
                        { {5, 0},{0, 0},{0, -5},{5, -5} },
                        logic::blocks::matter::None)
                    << logic::blocks::Block(
                        { static_cast<float>(975 + i * 200), static_cast<float>(-450 - i * 100) },
                        { {-5, 0},{0, 0},{0, -5},{-5, -5} },
                        logic::blocks::matter::None);
            for (int i = 0; i < 5; i++)
                os << logic::blocks::Block(
                    { static_cast<float>(3000 + i * 200), 0 },
                    { {-25, static_cast<float>(50 - i * 300)},{25, static_cast<float>(50 - i * 300)},{25, 500},{-25, 500} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Bouncing, new logic::blocks::decorators::Simple });

            os << logic::blocks::Block(
                    { 4300, -1200 },
                    { {0, 0},{1000, 0},{1000, 20},{0, 20} },
                    logic::blocks::matter::Stone,
                    { new logic::blocks::decorators::Simple })
                << logic::blocks::Block(
                    { 4800, -1200 },
                    { {0, 0},{20, 0},{20, -100},{0, -100} },
                    logic::blocks::matter::Finish,
                    { new logic::blocks::decorators::Finish });
            os.close();
            std::cout << "File: (" << path << ") as been saved" << std::endl;
        }

    }
}