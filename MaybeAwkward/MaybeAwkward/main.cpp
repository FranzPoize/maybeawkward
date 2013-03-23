#include "constants.h"

#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#include <ClanLib/application.h>
#include <string>

#include <memory>

#include "Entity.h"
#include "Physics.h"
#include "GameLogic.h"
#include "DrawerSprite.h"
#include "GraphicWrapper.h"
#include "XBoxController.h"
#include "Camera.h"
#include "FuckYouChoucheController.h"
#include "MockController.h"
#include "AIFlyingInPenisFormation.h"

class ConsoleProgram
{
public:
    static int main(const std::vector<CL_String> &args)
    {
#ifdef WIN32
        HANDLE process = GetCurrentProcess();
        SetPriorityClass(process, ABOVE_NORMAL_PRIORITY_CLASS);
#endif
        MA::PhysicsSystem::init();

        CL_SetupCore setup_core;
        CL_SetupDisplay setup_display;
        CL_SetupGL setup_opengl;

        CL_ConsoleWindow console("Console", 80, 160);
        CL_DisplayWindowDescription windowDescription;
        //Fucked up default value of "client area" to false... so this line is very important to get sensible behavior.
        windowDescription.set_size(CL_Size(WIN_WIDTH, WIN_HEIGHT), true);
        windowDescription.set_title("MaybeAwkward");
        CL_DisplayWindow window(windowDescription);
        CL_GraphicContext gc = window.get_gc();
        CL_InputContext ic = window.get_ic();


        CL_FileLogger file_logger("logfile.txt");

        //gc.set_map_mode(cl_map_2d_upper_left);

        //CL_InputDevice gamepad = ic.get_joystick_count() ? ic.get_joystick() : ic.get_keyboard();

        //Business starts here
        try
        {
			//Player Instanciation
            CL_SpriteDescription pibiDescription;
            pibiDescription.add_frame(ASSET_PATH+"placeholders/nounours_corps.png");
            
            CL_Sprite pibiSprite(gc, pibiDescription);
            pibiSprite.set_alignment(origin_bottom_left);

			//Enemy Instanciation
			CL_SpriteDescription enemyDescription;
			enemyDescription.add_frame(ASSET_PATH+"crap/enemy.png");

			CL_Sprite enemySprite(gc,enemyDescription);
			enemySprite.set_alignment(origin_bottom_left);

			std::shared_ptr<MA::Camera> camera(new MA::Camera(0.0f));
			MA::GraphicWrapper gw(gc,camera);
            std::shared_ptr<MA::Drawer> pibiDrawer = std::make_shared<MA::DrawerSprite>(gw, pibiSprite);
			std::shared_ptr<MA::Drawer> enemyDrawer = std::make_shared<MA::DrawerSprite>(gw, enemySprite);
#ifdef WIN32
            std::shared_ptr<MA::Controller> pibiController = std::make_shared<MA::XBoxController>();
#else 
            std::shared_ptr<MA::Controller> pibiController = std::make_shared<MA::MockController>();
#endif

			std::shared_ptr<MA::Controller> enemyController = std::make_shared<MA::AIFlyingInPenisFormation>();

            std::shared_ptr<MA::Entity> pibi(new MA::Entity(pibiController, pibiDrawer));

            std::shared_ptr<MA::GameLogic> gameplay = std::make_shared<MA::GameLogic>(nullptr);

            pibi->families().push_back(MA::FRIEND);
            pibi->families().push_back(MA::PLAYER);
            camera->followEntity(pibi);

            std::shared_ptr<MA::Entity> enemy(new MA::Entity(enemyController,enemyDrawer));
            enemy->families().push_back(MA::ENEMY);

			MA::PhysicsSystem::addEntity(*pibi,MA::PHYSICS_BOX_GRAVITY);
			MA::PhysicsSystem::addEntity(*enemy,MA::PHYSICS_BOX);
            MA::PhysicsSystem::setPosition(pibi->physicsID(), 100.0f, 540.0f);
			MA::PhysicsSystem::setPosition(enemy->physicsID(),100.0f,100.0f);

            unsigned int current_time=CL_System::get_time(), last_time=current_time-1;
            while (ic.get_keyboard().get_keycode(CL_KEY_ESCAPE) == false)
            {
                current_time = CL_System::get_time();
                float delta = (current_time-last_time)/1000.f;
                last_time = current_time;
                //CL_Console::write_line("dt : %1", delta);

                MA::PhysicsSystem::update(delta);

                gc.clear(CL_Colorf::whitesmoke);
                
				camera->update();
				enemy->update(delta);
                pibi->update(delta);
				enemy->draw();
                pibi->draw();

                window.flip(1);
                CL_KeepAlive::process(0);

                current_time = CL_System::get_time();
                if(current_time-last_time>ABNORMAL_TIME)
                {
                    cl_log_event("info", "ABNORMAL time : %1 ms", current_time-last_time);
                }
                //int timeToSleep = FRAME_TIME_TARGET - (current_time-last_time);
                //if(timeToSleep > 0)
                //    CL_System::sleep(timeToSleep);
                //CL_System::sleep(10);
            }
        }
        catch(CL_Exception &exception)
        {
            // Create a console window for text-output if not available
            //CL_ConsoleWindow console("Console", 80, 160);
            CL_Console::write_line("Error: " + exception.get_message_and_stack_trace());
            console.display_close_message();
            return -1;
        }

        return 0;
    }
};

// Create global application object, you MUST include this line or
// the application start-up will fail to locate your application object.
CL_ClanApplication app(&ConsoleProgram::main);