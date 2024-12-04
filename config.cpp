class CfgPatches
{
	class ZenBrokenGlasses
	{
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class ZenBrokenGlasses
	{
		dir = "ZenBrokenGlasses";
		name = "Zen's Broken Glasses";
		author = "Zenarchist";
		credits = "";
		version = "1.0";
		type = "mod";
		dependencies[] = 
		{ 
			"Game", 
			"World", 
			"Mission" 
		};
		class defs
		{
			class worldScriptModule
			{
				files[] = 
				{ 
					"ZenBrokenGlasses/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				files[] = 
				{ 
					"ZenBrokenGlasses/scripts/5_mission"
				};
			};
		};
	};
};