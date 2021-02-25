class CfgPatches
{
	class KillReward
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"JM_CF_Scripts"
		};
	};
};
class CfgMods
{
	class KillReward
	{
		dir="KillReward";
		name="KillReward";
		inputs="KillReward/inputs/inputs.xml";		
		action = "";
		hideName = 0;
		hidePicture = 0;
		credits="Thx for Support!";
		picture="KillReward/data/KR.paa";
		author="=FS=Kailber";
		version="1.5";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"KillReward/Scripts/3_Game",
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"KillReward/Scripts/4_World",
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"KillReward/Scripts/5_Mission",
				};
			};
		};
	};
};
