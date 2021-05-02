//BASESetting
class KillReward_KillRewardBASESettings : Managed{              
		int ZombieGlobalMessage = 1;        							// 1 = ON   0 = OFF
		int PlayerGlobalMessage = 1;									// 1 = ON   0 = OFF	
		int MessageSystem = 2;											// 0 = Text Chat  2=CF  3=VPP 
		int PointLoseByDeath = 500;										// Point Lose By Death
		int PVPVE = 0;													// 0 = PVP   1 = PVE    3 = PVPVE
		
	void KillReward_KillRewardBASESettings() { }
}

//Reward for ZombieKills
class KillReward_KillRewardZOMBIESettings : Managed{
	    int ZombieKillReward = 1;										// 1 = ON   0 = OFF
		int ZombieKillPoints = 10;										// Points for Zombiekills
		ref TIntArray ZombieKills = {5, 15, 35, 50, 75, 100};			// Reward for 1,2,4 Zombie kills
		ref TIntArray ZombieMoney = {50, 150, 250, 500, 750, 1000};		// Money for Kills
        ref TIntArray ZombieWeaponBox = {50, 75, 100};					// WeaponBox for 3,5 Zombie kills
		ref TIntArray ZombieWeaponBoxNumber = {1, 2, 3};				// WeaponBoxNumber for Box
	
	void KillReward_KillRewardZOMBIESettings() { }
}

//Reward for PlayerKills
class KillReward_KillRewardPLAYERSettings : Managed{
		int PlayerKillReward = 1;											// 1 = ON   0 = OFF
		int PlayerKillPoints = 100;											// Points for Playerkill
		ref TIntArray PlayerKills = {5, 15, 35, 50, 75, 100};				// Reward for 1,2,4 Palyer kills
		ref TIntArray PlayerMoney = {500, 1500, 2500, 5000, 7500, 10000};	// Money for Kills	
		ref TIntArray PlayerWeaponBox = {50, 75, 100};						// WeaponBox for 3,5 Player kills
		ref TIntArray PlayerWeaponBoxNumber = {1, 2, 3};	
		
	void KillReward_KillRewardPLAYERSettings() { }
}

//Reward for Hunting
class KillReward_KillRewardHUNTINGSettings : Managed{
		int HuntingReward = 1;												// 1 = ON   0 = OFF
		
		int WolfPoints = 5;
		ref TIntArray WolfKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray WolfMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		int BearPoints = 5;
		ref TIntArray BearKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray BearMoney = {50, 150, 250, 500, 750, 1000};  			// Money for Kills
		
		int StagPoints = 5;
		ref TIntArray StagKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray StagMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		int HindPoints = 5;
		ref TIntArray HindKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray HindMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		int RoebuckPoints = 5;
		ref TIntArray RoebuckKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray RoebuckMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		int DoePoints = 5;
		ref TIntArray DoeKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray DoeMoney = {50, 150, 250, 500, 750, 1000};   			// Money for Kills
		
		int Wild_BoarPoints = 5;
		ref TIntArray Wild_BoarKills = {5, 15, 25, 50, 75, 100};			// Reward for 1,2,4 animal kills
		ref TIntArray Wild_BoarMoney = {50, 150, 250, 500, 750, 1000};   	// Money for Kills
		
		int PigPoints = 5;
		ref TIntArray PigKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray PigMoney = {50, 150, 250, 500, 750, 1000};   			// Money for Kills
		
		int RamPoints = 5;
		ref TIntArray RamKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray RamMoney = {50, 150, 250, 500, 750, 1000};   			// Money for Kills
		
		int EwePoints = 5;
		ref TIntArray EweKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray EweMoney = {50, 150, 250, 500, 750, 1000};   			// Money for Kills
		
		int billy_goatPoints = 5;
		ref TIntArray billy_goatKills = {5, 15, 25, 50, 75, 100};			// Reward for 1,2,4 animal kills
		ref TIntArray billy_goatMoney = {50, 150, 250, 500, 750, 1000};   	// Money for Kills
		
		int goatPoints = 5;
		ref TIntArray goatKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray goatMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		int BullPoints = 5;
		ref TIntArray BullKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray BullMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		int CowPoints = 5;
		ref TIntArray CowKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray CowMoney = {50, 150, 250, 500, 750, 1000};   			// Money for Kills
		
		int RoosterPoints = 5;
		ref TIntArray RoosterKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray RoosterMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		int HenPoints = 5;
		ref TIntArray HenKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray HenMoney = {50, 150, 250, 500, 750, 1000};   			// Money for Kills
		
		


	void KillReward_KillRewardHUNTINGSettings() { }
}

//Reward MoneySetting
class KillReward_KillRewardNEGATIVESettings : Managed{
		int PlayerKillNegativeReward = 0;						// 1 = ON   0 = OFF for PVE is on "1" PlayerKillReward = "0"!
		int PlayerKill = 0;
		int Pointlose = 100;
		int LoseMoney = 1000;  		
		int PlayerKillNegativeRewardBonusQuantity = 15;		
		ref TStringArray PlayerKillNegativeRewardBonus = {
				"Animal_UrsusArctos",
				"Animal_CanisLupus_White",
                "ZmbF_CitizenANormal_Brown",
                "ZmbF_CitizenBSkinny",
                "ZmbF_Clerk_Normal_White",
                "ZmbF_DoctorSkinny",
                "ZmbF_JoggerSkinny_Blue",
                "ZmbF_JournalistNormal_Red",
                "ZmbF_NurseFat",
                "ZmbF_ParamedicNormal_Red",
                "ZmbF_PatientOld",
                "ZmbF_PoliceWomanNormal",
                "ZmbF_ShortSkirt_black",
                "ZmbF_ShortSkirt_red",
                "ZmbF_ShortSkirt_yellow",
                "ZmbF_SkaterYoung_Violet",
                "ZmbM_CitizenASkinny_Red",
                "ZmbM_CitizenBFat_Blue",
                "ZmbM_ClerkFat_Brown",
                "ZmbM_CommercialPilotOld_Olive",
                "ZmbM_DoctorFat",
                "ZmbM_JacketNormal_greenchecks",
                "ZmbM_Jacket_stripes",
                "ZmbM_JoggerSkinny_Blue",
                "ZmbM_ParamedicNormal_Red",
                "ZmbM_PatientSkinny",
                "ZmbM_PatrolNormal_Autumn",
                "ZmbM_PolicemanFat",
                "ZmbM_PolicemanSpecForce",
                "ZmbM_PrisonerSkinny",
				"ZmbM_SkaterYoung_Grey"};

	void KillReward_KillRewardNEGATIVESettings() { }
}

class KillReward_KillRewardGIFTSettings : Managed{
	
        int PlayerGift = 1;	
		int GiftLifetime = 5;
		ref TStringArray Giftbox = {
                "GiftBox_Medium_1",
                "GiftBox_Medium_2",
                "GiftBox_Medium_3"};
				
		ref TStringArray Giftdrink = {
				"SodaCan_Cola", 
				"SodaCan_Kvass", 
				"SodaCan_Pipsi", 
				"SodaCan_Spite",
				"Canteen",
				"WaterBottle"};
				
		ref TStringArray Gifteat = {
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

		ref TStringArray Gifttools = {
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

		ref TStringArray Giftmedical = {
                "BandageDressing",
                "Epinephrine",
                "Heatpack",
                "Morphine",
                "PainkillerTablets",
                "PurificationTablets",
                "Rag",
                "TetracyclineAntibiotics",
                "VitaminBottle"};				

	void KillReward_KillRewardGIFTSettings() { }
}



//Reward for Longest Shoot
class KillReward_KillRewardSHOOTDISTANCESettings : Managed {
		int SHOOTReward = 1;
		float PlayerSHOOTDISTANCE = 500;  
		
	void KillReward_KillRewardSHOOTDISTANCESettings() { }
}



//WeaponBox
class KillReward_KillRewardWEAPONBOXSettings : Managed {
		
		int BoxNumber;
		string Box;
		string BoxWeapon;
		string BoxWeaponBayonet;
		string BoxWeaponButtstock;
		string BoxWeaponHandguard;
		string BoxWeaponsuppressor;
		string BoxWeaponSight;
		string BoxWeaponMagazin;
		int BoxMagazinQuantity;
		ref TStringArray BoxBonus;
		
	void KillReward_KillRewardWEAPONBOXSettings( int boxNumber, string box, string boxWeapon, string boxWeaponBayonet, string boxWeaponButtstock, string boxWeaponHandguard, string boxWeaponsuppressor, string boxWeaponSight, string boxWeaponMagazin, int boxMagazinQuantity, ref TStringArray boxBonus) { 
	
		BoxNumber = boxNumber;
		Box = box;
		BoxWeapon = boxWeapon;
		BoxWeaponBayonet = boxWeaponBayonet;
		BoxWeaponButtstock = boxWeaponButtstock;
		BoxWeaponHandguard = boxWeaponHandguard;
		BoxWeaponsuppressor = boxWeaponsuppressor;
		BoxWeaponSight = boxWeaponSight;
		BoxWeaponMagazin = boxWeaponMagazin;
		BoxMagazinQuantity = boxMagazinQuantity;
		BoxBonus = boxBonus;
	
	}
}