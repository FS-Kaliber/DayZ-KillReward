class KillReward_Config : Managed{
	// KillReward settings section
	autoptr ref KillReward_KillRewardBASESettings KillRewardBASE;
    autoptr ref KillReward_KillRewardNEGATIVESettings KillRewardNEGATIVE;
	autoptr ref KillReward_KillRewardGIFTSettings KillRewardGIFT;
	autoptr ref KillReward_KillRewardZOMBIESettings KillRewardZOMBIE;
	autoptr ref KillReward_KillRewardPLAYERSettings KillRewardPLAYER;
	autoptr ref KillReward_KillRewardHUNTINGSettings KillRewardHUNTING;
	autoptr ref KillReward_KillRewardSHOOTDISTANCESettings KillRewardSHOOTDISTANCE;
	autoptr array<ref KillReward_KillRewardWEAPONBOXSettings> KillRewardWEAPONBOX;
	int version = 6;

	void KillReward_Config() {
		Init();
        LoadFromKillJson();
	}
    
	void Init() {
        MakeDirectory(KillReward_CONFIG_FOLDER);
		KillRewardBASE = new ref KillReward_KillRewardBASESettings;
		KillRewardNEGATIVE = new ref KillReward_KillRewardNEGATIVESettings;
		KillRewardGIFT = new ref KillReward_KillRewardGIFTSettings;
		KillRewardZOMBIE = new ref KillReward_KillRewardZOMBIESettings;
		KillRewardPLAYER = new ref KillReward_KillRewardPLAYERSettings;
		KillRewardHUNTING = new ref KillReward_KillRewardHUNTINGSettings;
		KillRewardSHOOTDISTANCE = new ref KillReward_KillRewardSHOOTDISTANCESettings;
	}
	bool IsBroken() {}
	void LoadFromKillJson() {
		
		if (FileExist(KillReward_CONFIG_JSON))
		{
			JsonFileLoader<KillReward_Config>.JsonLoadFile(KillReward_CONFIG_JSON, this);
		}
		
		if (this.IsBroken()) {
			//Print("The file 'KillReward_Config.json' is corrupted or doesn't exist, a new file is going to be created with default values.");
			LoadDefaultKillConfig();
		}
		
		if (version < 7) {
			version = 7;
			CopyFile(KillReward_CONFIG_JSON, KillReward_CONFIG_FOLDER + "\\Config_Backup.json");
			DeleteFile(KillReward_CONFIG_JSON);
			LoadDefaultKillConfig();
		}
		
			JsonFileLoader<KillReward_Config>.JsonSaveFile(KillReward_CONFIG_JSON, this);
	}

	void LoadDefaultKillConfig() {
			Init();
					autoptr array<ref KillReward_KillRewardWEAPONBOXSettings> boxes = new array<ref KillReward_KillRewardWEAPONBOXSettings>;
					boxes.Insert(new ref KillReward_KillRewardWEAPONBOXSettings(1, "WoodenCrate", "M4A1", "", "M4_MPBttstck_Black", "M4_RISHndgrd_Black", "","ACOGOptic","Mag_STANAG_30Rnd",5,{"WeaponCleaningKit","WeaponCleaningKit","WeaponCleaningKit"}));
					boxes.Insert(new ref KillReward_KillRewardWEAPONBOXSettings(2, "WoodenCrate", "M4A1", "", "M4_MPBttstck_Black", "M4_RISHndgrd_Black", "","ACOGOptic","Mag_STANAG_30Rnd",5,{"WeaponCleaningKit","WeaponCleaningKit","WeaponCleaningKit"}));
					this.KillRewardWEAPONBOX = boxes;
			JsonFileLoader<KillReward_Config>.JsonSaveFile(KillReward_CONFIG_JSON, this);		
	}
}