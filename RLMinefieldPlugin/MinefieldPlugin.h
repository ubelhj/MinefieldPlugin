#pragma once
#pragma comment( lib, "pluginsdk.lib" )
#include "bakkesmod/plugin/bakkesmodplugin.h"
#include "bakkesmod/plugin/pluginwindow.h"

constexpr auto plugin_version = "1.0";

class MinefieldPlugin: public BakkesMod::Plugin::BakkesModPlugin/*, public BakkesMod::Plugin::PluginWindow*/
{
private:
	bool recoveryEnabled = false;
	float lastBumpTime = 0.0f;
	float lastCooldownTime = 0.0f;	
public:
	void OnBoostPickUp(ActorWrapper cw, void* params, std::string funcName);
	virtual void onLoad();
	virtual void onUnload();
	Vector * GetBumpValues();
};

