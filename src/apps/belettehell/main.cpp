#include "constants.h"


#include <ClanLib/core.h>
#include <ClanLib/gl.h>
#include <ClanLib/display.h>
#include <ClanLib/application.h>

#include <ClanLib/sound.h>

#include <string>

#include <memory>

#include "Entity.h"
#include "Physics.h"
#include "GameLogic.h"
#include "DrawerSprite.h"
#include "GraphicWrapper.h"
#include "XBoxController.h"
#include "MockController.h"
#include "Camera.h"
#include "AttackerBullet.h"
#include "World.h"
#include "AnimatorSpriteSwitcher.h"

class ConsoleProgram
{
public:
    static std::shared_ptr<MA::Entity> createPibi(MA::World &aWorld)
    {
        CL_SpriteDescription pibiDescription;
        pibiDescription.add_frame(ASSET_PATH+"design_export/nounours_idle/nounours_idle_00.png");

        CL_Sprite pibiSprite(aWorld.getGraphicWrapper().cl(), pibiDescription);
        pibiSprite.set_alignment(ORIGIN);
        std::shared_ptr<MA::Drawer> pibiDrawer = std::make_shared<MA::DrawerSprite>(aWorld.getGraphicWrapper(), pibiSprite);

        //RightArm
        CL_SpriteDescription rightArmDescritpion;
        rightArmDescritpion.add_frame(ASSET_PATH+"design_export/nounours_bra_droit/nounours_bra_droit_00.png");

        CL_Sprite rightArmSprite(aWorld.getGraphicWrapper().cl(), rightArmDescritpion);
        rightArmSprite.set_alignment(ORIGIN);
        rightArmSprite.set_rotation_hotspot(origin_top_left, -85, -108);
        std::shared_ptr<MA::Drawer> rightArmDrawer = std::make_shared<MA::DrawerSprite>(aWorld.getGraphicWrapper(), rightArmSprite);

        // LeftArm
        CL_SpriteDescription leftArmDescritpion;
        leftArmDescritpion.add_frame(ASSET_PATH+"design_export/nounours_bra_gauche/nounours_bra_gauche_00.png");

        CL_Sprite leftArmSprite(aWorld.getGraphicWrapper().cl(), leftArmDescritpion);
        leftArmSprite.set_alignment(ORIGIN);
        leftArmSprite.set_rotation_hotspot(origin_top_left, -109, -107);
        std::shared_ptr<MA::Drawer> leftArmDrawer = std::make_shared<MA::DrawerSprite>(aWorld.getGraphicWrapper(), leftArmSprite);

#ifdef WIN32
        std::shared_ptr<MA::XBoxController> pibiController = std::make_shared<MA::XBoxController>();
        pibiController->switchControlType(MA::XBoxController::MOVE);

        std::shared_ptr<MA::XBoxController> rightArmController = std::make_shared<MA::XBoxController>();
        rightArmController->switchControlType(MA::XBoxController::LEFT_ATTACK);

        std::shared_ptr<MA::XBoxController> leftArmController = std::make_shared<MA::XBoxController>();
        leftArmController->switchControlType(MA::XBoxController::RIGHT_ATTACK);
#else 
        std::shared_ptr<MA::Controller> pibiController = std::make_shared<MA::MockController>();
        std::shared_ptr<MA::Controller> rightArmController = std::make_shared<MA::MockController>();
        std::shared_ptr<MA::Controller> leftArmController = std::make_shared<MA::MockController>();
#endif
        std::shared_ptr<MA::AnimatorSpriteSwitcher> spriteSwitch = std::make_shared<MA::AnimatorSpriteSwitcher>(ASSET_PATH+"design_export/nounoursSprites.xml");
        std::shared_ptr<MA::Entity> pibi = std::make_shared<MA::Entity>(pibiController, pibiDrawer);
        aWorld.pibiRef = pibi;
        pibi->setAnimator(spriteSwitch);
        pibi->name() = "Nounours";

		MA::PhysicsMaterial pibiMat(1.f,1.3f,1.f,200.f,170.f);
		MA::PhysicsSystem::addEntity(*pibi, MA::PHYSICS_BOX_GRAVITY,&pibiMat);
		pibi->setPosition(aWorld.getGraphicWrapper().camera().pos() + 100.0f, 540.0f);

        aWorld.getGraphicWrapper().camera().followEntity(pibi);

        std::shared_ptr<MA::Entity> rightArm = std::make_shared<MA::Entity>(rightArmController, rightArmDrawer);
        MA::PhysicsSystem::addEntity(*rightArm, MA::PHYSICS_BOX);
		rightArm->setPosition(0.0f, 0.0f);

        CL_Pointf rightOrigin(85.f, -62.f);
        std::shared_ptr<MA::AttackerBullet> rightAttacker = std::make_shared<MA::AttackerBullet>(rightOrigin);
        rightArm->setAttacker(rightAttacker);

        pibi->addChild(rightArm, 1);

        std::shared_ptr<MA::Entity> leftArm = std::make_shared<MA::Entity>(leftArmController, leftArmDrawer);
        MA::PhysicsSystem::addEntity(*leftArm, MA::PHYSICS_BOX);
		leftArm->setPosition(0.0f, 0.0f);

        CL_Pointf leftOrigin(109.f, -63.f);
        std::shared_ptr<MA::AttackerBullet> leftAttacker = std::make_shared<MA::AttackerBullet>(leftOrigin);
        leftArm->setAttacker(leftAttacker);

        pibi->addChild(leftArm, -1);

        pibi->families().push_back(MA::FRIEND);
        aWorld.everybodyList().push_back(pibi);
        return pibi;
    }

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
        CL_SetupSound setup_sound;
        CL_SoundOutput output(44100);

        CL_ConsoleWindow console("Console", 80, 160);
        CL_DisplayWindowDescription windowDescription;
        //Fucked up default value of "client area" to false... so this line is very important to get sensible behavior.
        windowDescription.set_size(CL_Size(WIN_WIDTH, WIN_HEIGHT), true);
        windowDescription.set_title("MaybeAwkward");
        CL_DisplayWindow window(windowDescription);
        CL_GraphicContext gc = window.get_gc();
        CL_InputContext ic = window.get_ic();

        MA::GameLogic logic;
        init_gameplay(&logic);

        CL_FileLogger file_logger("logfile.txt");

        //gc.set_map_mode(cl_map_2d_upper_left);

        //CL_InputDevice gamepad = ic.get_joystick_count() ? ic.get_joystick() : ic.get_keyboard();

        //Business starts here
        try
        {
            std::shared_ptr<MA::Camera> camera(new MA::Camera(0.0f));
            std::shared_ptr<MA::GraphicWrapper> gw(new MA::GraphicWrapper(gc, camera));
            MA::World &world = MA::World::instance;
            world.setGraphicWrapper(gw);
            world.init();

            // Load a sample from a wave file:
            CL_SoundBuffer sample(ASSET_PATH+"design_export/Music_Awkward_West.wav");
			CL_SoundBuffer_Session playback = sample.prepare();

            // Play sample
			playback.set_looping(true);
			playback.set_volume(1.f);
			playback.play();
            //Title
            CL_ResourceManager rTitre(ASSET_PATH+"design_export/titre.xml");
            CL_Sprite titre(gc, "titre", &rTitre);


            while (ic.get_keyboard().get_keycode(CL_KEY_ENTER) == false)
            {
				world.step(0.f);
				titre.draw(gc,0,720);
				world.getGraphicWrapper().camera().setPos(world.getGraphicWrapper().camera().pos() + 10);
                window.flip(1);
                CL_KeepAlive::process(0);
            }

            std::shared_ptr<MA::Entity> pibi = createPibi(world);
            world.createSpawner(*pibi);

            unsigned int current_time=CL_System::get_time(), last_time=current_time-1;
            while (ic.get_keyboard().get_keycode(CL_KEY_ESCAPE) == false)
            {
                current_time = CL_System::get_time();
                float delta = (current_time-last_time)/1000.f;
                last_time = current_time;
                //CL_Console::write_line("dt : %1", delta);

				// Yup, we did that
                //logic.update(delta);

                gc.clear(CL_Colorf::whitesmoke);

                world.step(delta);

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

				if(pibi->isMarkedForDeletion() && ic.get_keyboard().get_keycode(CL_KEY_ENTER))
				{
					world.empty();
					pibi->setX(100.0f);
					pibi->setY(540.0f);
					pibi->getPhysicalObject()->setXVelocity(0.f);
					pibi->getPhysicalObject()->setYVelocity(0.f);
					world.getGraphicWrapper().camera().setPos(0.f);
					pibi->markForDeletion(false);
					world.init();
					world.everybodyList().push_back(pibi);

				}
            }
        }
        catch(CL_Exception &exception)
        {
            // Create a console window for text-output if notf available
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