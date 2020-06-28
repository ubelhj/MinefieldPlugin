#include "pch.h"
#include "MinefieldPlugin.h"
#include "utils\parser.h"
#include "bakkesmod\wrappers\GameEvent\GameEventWrapper.h"
#include "bakkesmod\wrappers\Engine\ActorWrapper.h"
#include "bakkesmod\wrappers\GameObject\CarWrapper.h"

BAKKESMOD_PLUGIN(MinefieldPlugin, "Minefield plugin", "1.0", 0)

void MinefieldPlugin::onLoad()
{
	cvarManager->registerCvar("minefield_bumpspeed_angular", "(0, 5.5)", "How hard you will get thrown rotationally", true, true, 0.0f, true, 10.0f);
	cvarManager->registerCvar("minefield_bumpspeed_linear", "(500, 1000)", "How hard you will get thrown", true, true, 0.f, true, 2300.0f);
	cvarManager->registerCvar("minefield_bumpspeed_linear_z", "(200, 800)", "How hard you will get thrown (height)", true, true, -2300.0f, true, 2300.0f);

	gameWrapper->HookEventWithCaller<ActorWrapper>("Function TAGame.VehiclePickup_Boost_TA.Pickup", std::bind(&MinefieldPlugin::OnBoostPickUp, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

void MinefieldPlugin::OnBoostPickUp(ActorWrapper caller, void* params, std::string funcName){

	Vector* values;
	values = GetBumpValues();

	/* NOT WORKING, GAME CRASHES
	CarWrapper car = CarWrapper(reinterpret_cast<uintptr_t>(params));
	car.SetAngularVelocity(values[0], 0);
	car.AddVelocity(values[1]);		
	*/
}


Vector* MinefieldPlugin::GetBumpValues()
{
	static Vector values[2];
	
		Vector angularBump = {
			cvarManager->getCvar("minefield_bumpspeed_angular").getFloatValue(),
			cvarManager->getCvar("minefield_bumpspeed_angular").getFloatValue(),
			cvarManager->getCvar("minefield_bumpspeed_angular").getFloatValue()
		};
		Vector linearBump = {
			cvarManager->getCvar("minefield_bumpspeed_linear").getFloatValue(),
			cvarManager->getCvar("minefield_bumpspeed_linear").getFloatValue(),
			cvarManager->getCvar("minefield_bumpspeed_linear_z").getFloatValue()
		};


		angularBump.X = random(0, 1) == 1 ? angularBump.X : -angularBump.X;
		angularBump.Y = random(0, 1) == 1 ? angularBump.Y : -angularBump.Y;
		angularBump.Z = random(0, 1) == 1 ? angularBump.Z : -angularBump.Z;

		linearBump.X = random(0, 1) == 1 ? linearBump.X : -linearBump.X;
		linearBump.Y = random(0, 1) == 1 ? linearBump.Y : -linearBump.Y;

		values[0] = angularBump;
		values[1] = linearBump;

		return values;
}

	void MinefieldPlugin::onUnload()
	{

	}

