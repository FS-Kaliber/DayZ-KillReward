modded class AnimalBase extends DayZAnimal
{
	
	override void EEKilled(Object killer)
	{
		super.EEKilled(killer);
		
			EntityAI killer_entity = EntityAI.Cast( killer );
			Man killerV = killer_entity.GetHierarchyRootPlayer();
			PlayerBase killerVictim = PlayerBase.Cast(killerV);
						
		if(!killerVictim){
				
			}else{
		
			string killer_name  = killerVictim.GetIdentity().GetName();
			string sourcePlayerID = killerVictim.GetIdentity().GetPlainId();
			PlayerIdentity Killer_identity = killerVictim.GetIdentity();
			string animalType = this.GetType();
			string AnimalName = this.GetDisplayName();
			
			////Print("[Animal Debug] Killed Animal = " +AnimalName+ " type = " +animalType );
			
        if( animalType == "Animal_CanisLupus_White" || animalType == "Animal_CanisLupus_Grey")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "WolfKills"));	
			}

		//Bär
		if( animalType == "Animal_UrsusArctos")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "BearKills"));		
			}
		
		//Hirsch	
		if(animalType == "Animal_CervusElaphus")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "StagKills"));			
			}		
			
		//Hirschkuh	
		if(animalType == "Animal_CervusElaphusF")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "HindKills"));		
			}			

		//Rehbock
	    if(animalType == "Animal_CapreolusCapreolus")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "RoebuckKills"));			
			}	
			
		//Reh
	    if(animalType == "Animal_CapreolusCapreolusF")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "DoeKills"));			
			}
			
		//Wildschwein
	    if(animalType == "Animal_SusScrofa")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "Wild_BoarKills"));				
			}	

		//Hausschwein
	    if(animalType == "Animal_SusDomesticus")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "PigKills"));			
			}		
			
		//Schafbock
	    if(animalType == "Animal_OvisAries")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "RamKills"));				
			}	
			
		//Schaf
	    if(animalType == "Animal_OvisAriesF")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "EweKills"));			
			}

		//Ziegenbock
	    if(animalType == "Animal_CapraHircus_Black" || animalType == "Animal_CapraHircus_Brown" || animalType == "Animal_CapraHircus_White")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "Billy_GoatKills"));				
			}

		//Ziege
	    if(animalType == "Animal_CapraHircusF")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "GoatKills"));			
			}

		//Bulle
	    if(animalType == "Animal_BosTaurus_White" || animalType == "Animal_BosTaurus_Brown" || animalType == "Animal_BosTaurus_Spotted")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "BullKills"));			
			}
			
		//Kuh
	    if(animalType == "Animal_BosTaurusF_White" || animalType == "Animal_BosTaurusF_Brown" || animalType == "Animal_BosTaurusF_Spotted")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "CowKills"));	
			}
			
		//Hahn
	   if(animalType == "Animal_GallusGallusDomesticus" || animalType == "Animal_GallusGallusDomesticus_Brown" || animalType == "Animal_GallusGallusDomesticus_Spotted")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "RoosterKills"));				
			}	

		//Huhn
	   if(animalType == "Animal_GallusGallusDomesticusF_White" || animalType == "Animal_GallusGallusDomesticusF_Brown" || animalType == "Animal_GallusGallusDomesticusF_Spotted")
			{
				GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "HenKills"));				
			}	
	  }
	}
	
	 
}