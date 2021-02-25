//BASESetting
class KillReward_KillRewardBASESettings : Managed{              
		int ZombieGlobalMessage = 1;        							// 1 = ON   0 = OFF
		int PlayerGlobalMessage = 1;									// 1 = ON   0 = OFF	
		int MessageSystem = 2;											// 0 = Text Chat  2=CF  3=VPP 
		int PVP = 0;
		
	void KillReward_KillRewardBASESettings() { }
}

//Reward for ZombieKills
class KillReward_KillRewardZOMBIESettings : Managed{
	    int ZombieKillReward = 1;										// 1 = ON   0 = OFF
		ref TIntArray ZombieKills = {5, 15, 35, 50, 75, 100};			// Reward for 1,2,4 Zombie kills
		ref TIntArray ZombieMoney = {50, 150, 250, 500, 750, 1000};		// Money for Kills
        ref TIntArray ZombieWeaponBox = {50, 75, 100};					// WeaponBox for 3,5 Zombie kills
		ref TIntArray ZombieWeaponBoxNumber = {1, 2, 3};				// WeaponBoxNumber for Box
	
	void KillReward_KillRewardZOMBIESettings() { }
}

//Reward for PlayerKills
class KillReward_KillRewardPLAYERSettings : Managed{
		int PlayerKillReward = 1;											// 1 = ON   0 = OFF
		ref TIntArray PlayerKills = {5, 15, 35, 50, 75, 100};				// Reward for 1,2,4 Palyer kills
		ref TIntArray PlayerMoney = {500, 1500, 2500, 5000, 7500, 10000};	// Money for Kills
		ref TIntArray PlayerWeaponBox = {50, 75, 100};						// WeaponBox for 3,5 Player kills
		ref TIntArray PlayerWeaponBoxNumber = {1, 2, 3};	
		
	void KillReward_KillRewardPLAYERSettings() { }
}

//Reward for Hunting
class KillReward_KillRewardHUNTINGSettings : Managed{
		int HuntingReward = 1;												// 1 = ON   0 = OFF
		ref TIntArray WolfKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray WolfMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray BearKills = {5, 15, 25, 50, 75, 100};					// Reward for 1,2,4 animal kills
		ref TIntArray BearMoney = {50, 150, 250, 500, 750, 1000};  			// Money for Kills
		
		ref TIntArray StagKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray StagMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray HindKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray HindMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray RoebuckKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray RoebuckMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray DoeKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray DoeMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray Wild_BoarKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray Wild_BoarMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray PigKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray PigMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray RamKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray RamMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray EweKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray EweMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray billy_goatKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray billy_goatMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray goatKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray goatMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray BullKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray BullMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray CowKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray CowMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray RoosterKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray RoosterMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills
		
		ref TIntArray HenKills = {5, 15, 25, 50, 75, 100};				// Reward for 1,2,4 animal kills
		ref TIntArray HenMoney = {50, 150, 250, 500, 750, 1000};   		// Money for Kills


	void KillReward_KillRewardHUNTINGSettings() { }
}

//Reward MoneySetting
class KillReward_KillRewardNEGATIVESettings : Managed{
		int PlayerKillNegativeReward = 0;						// 1 = ON   0 = OFF for PVE is on "1" PlayerKillReward = "0"!
		int PlayerKill = 0;
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
		int WeaponBox = 1;
        int BoxLifetime = 5;
		int _____________BOX1_____________ = 0;		
		string Box1 = "WoodenCrate";
		string Box1Weapon = "AKM";
		string Box1WeaponBayonet = "";
		string Box1WeaponButtstock = "AK_Woodbttstck";
		string Box1WeaponHandguard = "AK_WoodHndgrd";
		string Box1Weaponsuppressor = "AK_Suppressor";
		string Box1WeaponSight = "PSO11Optic";
		string Box1WeaponMagazin = "Mag_AKM_30Rnd";
		int Box1MagazinQuantity = 5;
		ref TStringArray Box1Bonus = {
			"Rice",
			"Rice",
			"Rice"};		
		int _____________BOX2_____________ = 0;
		string Box2 = "WoodenCrate";
		string Box2Weapon = "SKS";
		string Box2WeaponBayonet = "SKS_Bayonet";
		string Box2WeaponButtstock = "";
		string Box2WeaponHandguard = "";
		string Box2Weaponsuppressor = "";
		string Box2WeaponSight = "PUScopeOptic";
		string Box2WeaponMagazin = "Ammo_762x39Tracer";
		int Box2MagazinQuantity = 5;
		ref TStringArray Box2Bonus = {
			"Rice",
			"Rice",
			"Rice"};	
		int _____________BOX3_____________ = 0;
		string Box3 = "WoodenCrate";
		string Box3Weapon = "Winchester70";
		string Box3WeaponBayonet = "";
		string Box3WeaponButtstock = "";
		string Box3WeaponHandguard = "";
		string Box3Weaponsuppressor = "";
		string Box3WeaponSight = "HuntingOptic";
		string Box3WeaponMagazin = "Ammo_308WinTracer";
		int Box3MagazinQuantity = 5;
		ref TStringArray Box3Bonus = {
			"",
			"",
			""};	
		int _____________BOX4_____________ = 0;
		string Box4 = "WoodenCrate";
		string Box4Weapon = "Mosin9130_Camo";
		string Box4WeaponBayonet = "";
		string Box4WeaponButtstock = "";
		string Box4WeaponHandguard = "";
		string Box4Weaponsuppressor = "Mosin_Compensator";
		string Box4WeaponSight = "PUScopeOptic";
		string Box4WeaponMagazin = "Ammo_762x54Tracer";
		int Box4MagazinQuantity = 5;
		ref TStringArray Box4Bonus = {
			"",
			"",
			""};
		int _____________BOX5_____________ = 0;
		string Box5 = "WoodenCrate";
		string Box5Weapon = "CZ527";
		string Box5WeaponBayonet = "";
		string Box5WeaponButtstock = "";
		string Box5WeaponHandguard = "";
		string Box5Weaponsuppressor = "";
		string Box5WeaponSight = "HuntingOptic";
		string Box5WeaponMagazin = "Mag_CZ527_5rnd";
		int Box5MagazinQuantity = 5;
		ref TStringArray Box5Bonus = {
			"",
			"",
			""};
		int _____________BOX6_____________ = 0;
		string Box6 = "WoodenCrate";
		string Box6Weapon = "VSS";
		string Box6WeaponBayonet = "";
		string Box6WeaponButtstock = "";
		string Box6WeaponHandguard = "";
		string Box6Weaponsuppressor = "";
		string Box6WeaponSight = "PSO11Optic";
		string Box6WeaponMagazin = "Mag_VSS_10Rnd";
		int Box6MagazinQuantity = 5;
		ref TStringArray Box6Bonus = {
			"",
			"",
			""};
		int _____________BOX7_____________ = 0;
		string Box7 = "WoodenCrate";
		string Box7Weapon = "SVD";
		string Box7WeaponBayonet = "";
		string Box7WeaponButtstock = "";
		string Box7WeaponHandguard = "";
		string Box7Weaponsuppressor = "";
		string Box7WeaponSight = "PSO11Optic";
		string Box7WeaponMagazin = "Mag_SVD_10Rnd";
		int Box7MagazinQuantity = 5;
		ref TStringArray Box7Bonus = {
			"",
			"",
			""};
		int _____________BOX8_____________ = 0;
		string Box8 = "WoodenCrate";
		string Box8Weapon = "M4A1";
		string Box8WeaponBayonet = "";
		string Box8WeaponButtstock = "M4_MPBttstck_Black";
		string Box8WeaponHandguard = "M4_RISHndgrd_Black";
		string Box8Weaponsuppressor = "";
		string Box8WeaponSight = "ACOGOptic";
		string Box8WeaponMagazin = "Mag_STANAG_30Rnd";
		int Box8MagazinQuantity = 5;
		ref TStringArray Box8Bonus = {
			"",
			"",
			""};	
		int _____________BOX9_____________ = 0;
		string Box9 = "";
		string Box9Weapon = "";
		string Box9WeaponBayonet = "";
		string Box9WeaponButtstock = "";
		string Box9WeaponHandguard = "";
		string Box9Weaponsuppressor = "";
		string Box9WeaponSight = "";
		string Box9WeaponMagazin = "";
		int Box9MagazinQuantity = 0;
		ref TStringArray Box9Bonus = {
			"",
			"",
			""};	
		int _____________BOX10_____________ = 0;
		string Box10 = "";
		string Box10Weapon = "";
		string Box10WeaponBayonet = "";
		string Box10WeaponButtstock = "";
		string Box10WeaponHandguard = "";
		string Box10Weaponsuppressor = "";
		string Box10WeaponSight = "";
		string Box10WeaponMagazin = "";
		int Box10MagazinQuantity = 0;
		ref TStringArray Box10Bonus = {
			"",
			"",
			""};	
		int _____________BOX11_____________ = 0;
		string Box11 = "";
		string Box11Weapon = "";
		string Box11WeaponBayonet = "";
		string Box11WeaponButtstock = "";
		string Box11WeaponHandguard = "";
		string Box11Weaponsuppressor = "";
		string Box11WeaponSight = "";
		string Box11WeaponMagazin = "";
		int Box11MagazinQuantity = 0;
		ref TStringArray Box11Bonus = {
			"",
			"",
			""};	
		int _____________BOX12_____________ = 0;
		string Box12 = "";
		string Box12Weapon = "";
		string Box12WeaponBayonet = "";
		string Box12WeaponButtstock = "";
		string Box12WeaponHandguard = "";
		string Box12Weaponsuppressor = "";
		string Box12WeaponSight = "";
		string Box12WeaponMagazin = "";
		int Box12MagazinQuantity = 0;
		ref TStringArray Box12Bonus = {
			"",
			"",
			""};	
		int _____________BOX13_____________ = 0;
		string Box13 = "";
		string Box13Weapon = "";
		string Box13WeaponBayonet = "";
		string Box13WeaponButtstock = "";
		string Box13WeaponHandguard = "";
		string Box13Weaponsuppressor = "";
		string Box13WeaponSight = "";
		string Box13WeaponMagazin = "";
		int Box13MagazinQuantity = 0;
		ref TStringArray Box13Bonus = {
			"",
			"",
			""};	
		int _____________BOX14_____________ = 0;
		string Box14 = "";
		string Box14Weapon = "";
		string Box14WeaponBayonet = "";
		string Box14WeaponButtstock = "";
		string Box14WeaponHandguard = "";
		string Box14Weaponsuppressor = "";
		string Box14WeaponSight = "";
		string Box14WeaponMagazin = "";
		int Box14MagazinQuantity = 0;
		ref TStringArray Box14Bonus = {
			"",
			"",
			""};	
		int _____________BOX15_____________ = 0;
		string Box15 = "";
		string Box15Weapon = "";
		string Box15WeaponBayonet = "";
		string Box15WeaponButtstock = "";
		string Box15WeaponHandguard = "";
		string Box15Weaponsuppressor = "";
		string Box15WeaponSight = "";
		string Box15WeaponMagazin = "";
		int Box15MagazinQuantity = 0;
		ref TStringArray Box15Bonus = {
			"",
			"",
			""};	
		int _____________BOX16_____________ = 0;
		string Box16 = "";
		string Box16Weapon = "";
		string Box16WeaponBayonet = "";
		string Box16WeaponButtstock = "";
		string Box16WeaponHandguard = "";
		string Box16Weaponsuppressor = "";
		string Box16WeaponSight = "";
		string Box16WeaponMagazin = "";
		int Box16MagazinQuantity = 0;
		ref TStringArray Box16Bonus = {
			"",
			"",
			""};	
		int _____________BOX17_____________ = 0;
		string Box17 = "";
		string Box17Weapon = "";
		string Box17WeaponBayonet = "";
		string Box17WeaponButtstock = "";
		string Box17WeaponHandguard = "";
		string Box17Weaponsuppressor = "";
		string Box17WeaponSight = "";
		string Box17WeaponMagazin = "";
		int Box17MagazinQuantity = 0;
		ref TStringArray Box17Bonus = {
			"",
			"",
			""};	
		int _____________BOX18_____________ = 0;
		string Box18 = "";
		string Box18Weapon = "";
		string Box18WeaponBayonet = "";
		string Box18WeaponButtstock = "";
		string Box18WeaponHandguard = "";
		string Box18Weaponsuppressor = "";
		string Box18WeaponSight = "";
		string Box18WeaponMagazin = "";
		int Box18MagazinQuantity = 0;
		ref TStringArray Box18Bonus = {
			"",
			"",
			""};	
		int _____________BOX19_____________ = 0;
		string Box19 = "";
		string Box19Weapon = "";
		string Box19WeaponBayonet = "";
		string Box19WeaponButtstock = "";
		string Box19WeaponHandguard = "";
		string Box19Weaponsuppressor = "";
		string Box19WeaponSight = "";
		string Box19WeaponMagazin = "";
		int Box19MagazinQuantity = 0;
		ref TStringArray Box19Bonus = {
			"",
			"",
			""};	
		int _____________BOX20_____________ = 0;
		string Box20 = "";
		string Box20Weapon = "";
		string Box20WeaponBayonet = "";
		string Box20WeaponButtstock = "";
		string Box20WeaponHandguard = "";
		string Box20Weaponsuppressor = "";
		string Box20WeaponSight = "";
		string Box20WeaponMagazin = "";
		int Box20MagazinQuantity = 0;
		ref TStringArray Box20Bonus = {
			"",
			"",
			""};	
		int _____________BOX21_____________ = 0;
		string Box21 = "";
		string Box21Weapon = "";
		string Box21WeaponBayonet = "";
		string Box21WeaponButtstock = "";
		string Box21WeaponHandguard = "";
		string Box21Weaponsuppressor = "";
		string Box21WeaponSight = "";
		string Box21WeaponMagazin = "";
		int Box21MagazinQuantity = 0;
		ref TStringArray Box21Bonus = {
			"",
			"",
			""};	
		int _____________BOX22_____________ = 0;
		string Box22 = "";
		string Box22Weapon = "";
		string Box22WeaponBayonet = "";
		string Box22WeaponButtstock = "";
		string Box22WeaponHandguard = "";
		string Box22Weaponsuppressor = "";
		string Box22WeaponSight = "";
		string Box22WeaponMagazin = "";
		int Box22MagazinQuantity = 0;
		ref TStringArray Box22Bonus = {
			"",
			"",
			""};		
		int _____________BOX23_____________ = 0;
		string Box23 = "";
		string Box23Weapon = "";
		string Box23WeaponBayonet = "";
		string Box23WeaponButtstock = "";
		string Box23WeaponHandguard = "";
		string Box23Weaponsuppressor = "";
		string Box23WeaponSight = "";
		string Box23WeaponMagazin = "";
		int Box23MagazinQuantity = 0;
		ref TStringArray Box23Bonus = {
			"",
			"",
			""};
		int _____________BOX24_____________ = 0;
		string Box24 = "";
		string Box24Weapon = "";
		string Box24WeaponBayonet = "";
		string Box24WeaponButtstock = "";
		string Box24WeaponHandguard = "";
		string Box24Weaponsuppressor = "";
		string Box24WeaponSight = "";
		string Box24WeaponMagazin = "";
		int Box24MagazinQuantity = 0;
		ref TStringArray Box24Bonus = {
			"",
			"",
			""};	
		int _____________BOX25_____________ = 0;
		string Box25 = "";
		string Box25Weapon = "";
		string Box25WeaponBayonet = "";
		string Box25WeaponButtstock = "";
		string Box25WeaponHandguard = "";
		string Box25Weaponsuppressor = "";
		string Box25WeaponSight = "";
		string Box25WeaponMagazin = "";
		int Box25MagazinQuantity = 0;
		ref TStringArray Box25Bonus = {
			"",
			"",
			""};	
		int _____________BOX26_____________ = 0;
		string Box26 = "";
		string Box26Weapon = "";
		string Box26WeaponBayonet = "";
		string Box26WeaponButtstock = "";
		string Box26WeaponHandguard = "";
		string Box26Weaponsuppressor = "";
		string Box26WeaponSight = "";
		string Box26WeaponMagazin = "";
		int Box26MagazinQuantity = 0;
		ref TStringArray Box26Bonus = {
			"",
			"",
			""};	
		int _____________BOX27_____________ = 0;
		string Box27 = "";
		string Box27Weapon = "";
		string Box27WeaponBayonet = "";
		string Box27WeaponButtstock = "";
		string Box27WeaponHandguard = "";
		string Box27Weaponsuppressor = "";
		string Box27WeaponSight = "";
		string Box27WeaponMagazin = "";
		int Box27MagazinQuantity = 0;
		ref TStringArray Box27Bonus = {
			"",
			"",
			""};
		int _____________BOX28_____________ = 0;
		string Box28 = "";
		string Box28Weapon = "";
		string Box28WeaponBayonet = "";
		string Box28WeaponButtstock = "";
		string Box28WeaponHandguard = "";
		string Box28Weaponsuppressor = "";
		string Box28WeaponSight = "";
		string Box28WeaponMagazin = "";
		int Box28MagazinQuantity = 0;
		ref TStringArray Box28Bonus = {
			"",
			"",
			""};
		int _____________BOX29_____________ = 0;
		string Box29 = "";
		string Box29Weapon = "";
		string Box29WeaponBayonet = "";
		string Box29WeaponButtstock = "";
		string Box29WeaponHandguard = "";
		string Box29Weaponsuppressor = "";
		string Box29WeaponSight = "";
		string Box29WeaponMagazin = "";
		int Box29MagazinQuantity = 0;
		ref TStringArray Box29Bonus = {
			"",
			"",
			""};
		int _____________BOX30_____________ = 0;
		string Box30 = "";
		string Box30Weapon = "";
		string Box30WeaponBayonet = "";
		string Box30WeaponButtstock = "";
		string Box30WeaponHandguard = "";
		string Box30Weaponsuppressor = "";
		string Box30WeaponSight = "";
		string Box30WeaponMagazin = "";
		int Box30MagazinQuantity = 0;
		ref TStringArray Box30Bonus = {
			"",
			"",
			""};	
		
		
	void KillReward_KillRewardWEAPONBOXSettings() { }
}