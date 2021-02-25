class KillReward_Config : Managed{
	// KillReward settings section
	autoptr ref KillReward_KillRewardBASESettings KillRewardBASE;
    autoptr ref KillReward_KillRewardNEGATIVESettings KillRewardNEGATIVE;
	autoptr ref KillReward_KillRewardGIFTSettings KillRewardGIFT;
	autoptr ref KillReward_KillRewardZOMBIESettings KillRewardZOMBIE;
	autoptr ref KillReward_KillRewardPLAYERSettings KillRewardPLAYER;
	autoptr ref KillReward_KillRewardHUNTINGSettings KillRewardHUNTING;
	autoptr ref KillReward_KillRewardSHOOTDISTANCESettings KillRewardSHOOTDISTANCE;
	autoptr ref KillReward_KillRewardWEAPONBOXSettings KillRewardWEAPONBOX;
	int version = 5;

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
		KillRewardWEAPONBOX = new ref KillReward_KillRewardWEAPONBOXSettings;
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
		
		if (version < 3) {
			version = 3;
			CopyFile(KillReward_CONFIG_JSON, KillReward_CONFIG_FOLDER + "\\Config_Backup.json");
			DeleteFile(KillReward_CONFIG_JSON);
			LoadDefaultKillConfig();
		}
		if (version < 4) {
			version = 4;
		KillRewardWEAPONBOX.BoxLifetime = 5;
		
        KillRewardGIFT.PlayerGift = 1;
		KillRewardGIFT.GiftLifetime = 5;
		KillRewardGIFT.Giftbox = {
                "GiftBox_Medium_1",
                "GiftBox_Medium_2",
                "GiftBox_Medium_3"};
				
		KillRewardGIFT.Giftdrink = {
				"SodaCan_Cola", 
				"SodaCan_Kvass", 
				"SodaCan_Pipsi", 
				"SodaCan_Spite",
				"Canteen",
				"WaterBottle"};
				
		KillRewardGIFT.Gifteat = {
				"BakedBeansCan", 
				"TacticalBaconCan", 
				"Apple", 
				"BoxCerealCrunchin", 
				"CaninaBerry", 
				"Canteen", 
				"GreenBellPepper",
				"Pear",
				"Plum",
				"Potato",
				"PowderedMilk",
				"Pumpkin",
				"Rice",
				"SambucusBerry",
				"SpaghettiCan_Opened",
				"Tomato",
				"TunaCan_Opened",
				"Zucchini" };

		KillRewardGIFT.Gifttools = {
                "Battery9V",
                "CanOpener",
                "ChernarusMap",
                "Compass",
                "Flashlight",
                "Hacksaw",
                "Hammer",
                "Hatchet",
                "HuntingKnife",
                "LeatherSewingKit",
                "Matchbox",
                "Pickaxe",
                "Rangefinder",
                "Roadflare",
                "Screwdriver",
                "Whetstone"};

		KillRewardGIFT.Giftmedical = {
                "BandageDressing",
                "Epinephrine",
                "Heatpack",
                "Morphine",
                "PainkillerTablets",
                "PurificationTablets",
                "Rag",
                "TetracyclineAntibiotics",
                "VitaminBottle"};	
		}

		if (version < 5) {
			version = 5;
		KillRewardHUNTING.StagKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.StagMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.HindKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.HindMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.RoebuckKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.RoebuckMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.DoeKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.DoeMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.Wild_BoarKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.Wild_BoarMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.PigKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.PigMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.RamKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.RamMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.EweKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.EweMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.billy_goatKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.billy_goatMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.goatKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.goatMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.BullKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.BullMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.CowKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.CowMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.RoosterKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.RoosterMoney = {50, 150, 250, 500, 750, 1000};   		
		
		KillRewardHUNTING.HenKills = {5, 15, 25, 50, 75, 100};				
		KillRewardHUNTING.HenMoney = {50, 150, 250, 500, 750, 1000}; 
		}
		
		if (version < 6) {
			version = 6;
			KillRewardPLAYER.PlayerWeaponBoxNumber = {1, 2, 3};
			KillRewardZOMBIE.ZombieWeaponBoxNumber = {1, 2, 3};
		
		}
		
			JsonFileLoader<KillReward_Config>.JsonSaveFile(KillReward_CONFIG_JSON, this);
	}

	void LoadDefaultKillConfig() {
			Init();
			JsonFileLoader<KillReward_Config>.JsonSaveFile(KillReward_CONFIG_JSON, this);		
	}
}