class KillRewardPlayer : RestCallback
{
	//Default Values
    string PlayerID = "";
	string PlayerName;
	int PlayerDeaths = 0;
	ref array< ref KRStat > Stats = new ref array< ref KRStat >;
	void KillRewardPlayer(string pID = "") 
	{
        PlayerID = pID;
		
		if (FileExist(KillReward_PlayerDB + "\\" + pID + ".json")) //If config file exsit load the file
        {
            JsonFileLoader<KillRewardPlayer>.JsonLoadFile(KillReward_PlayerDB+"\\" + pID + ".json", this);
        }
        else //If config file doesn't exsit create the file
        {
            if (GetGame().IsServer() || !GetGame().IsMultiplayer())
            {
                JsonFileLoader<KillRewardPlayer>.JsonSaveFile(KillReward_PlayerDB+"\\" + pID + ".json", this);
            }
        }
    }
    

	void saveData(){
		if (GetGame().IsServer())
		{
			JsonFileLoader<KillRewardPlayer>.JsonSaveFile(KillReward_PlayerDB + "\\" + PlayerID + ".json", this);
	    }
	}
	
	void savePlayerName(string pname){

			PlayerName = pname;
	}
	
	float getStat(string statName){
		//Print("[KillRewardPlayer][DebugClient] Looking for Stat: " + statName );
		float statTotal = 0;
		string prefix;
		int nameLength;
		if ( statName == "ZombieKill" ) {
			for ( int o =0; o < Stats.Count(); o++ )
			{
				if ( Stats.Get(o).Name.Contains("ZombieKill") ){
					statTotal = statTotal + Stats.Get(o).Stat;
				}
			}
			return statTotal;
		} 
		
		for ( int i =0; i < Stats.Count(); i++ )
		{
			if (Stats.Get(i).Name == statName){
				return Stats.Get(i).Stat;
			}
		}
		//Print("Stat: " + statName + " for player " + PlayerID + " not found");
		return 0;
	}
	
	float GetKD() {
		if (PlayerDeaths == 0)
			return ((float)getStat("ZombieKill")) / 100;
		float kd = (((float) getStat("ZombieKill")) / ((float) PlayerDeaths)) / 100;		
		kd *= 100;
		kd = Math.Round(kd);
		kd /= 100;
		return kd;
	}
		
	bool NewAction(string actionName, int shoot){

		int statID = -1;
		//Print("Player: " + PlayerID + " performed Action: " + actionName);
		for ( int i =0; i < Stats.Count(); i++ )
		{
			if (Stats.Get(i).Name == actionName){
				statID = i;
			}	
		}
		if (statID == -1){//Stat Not found so adding it
			Stats.Insert(new ref KRStat(actionName, 1));
			//Print("Stat: " + actionName + " for player " + PlayerID + " Created");
		}
		else
		{
			if(actionName == "longest_survivor_hit")
			{
				Stats.Get(statID).KRshoot(shoot);
				//Print("Stat: " + actionName + " for player " + PlayerID + " Updated to " + shoot);
			}else{	
			Stats.Get(statID).updateStat();
			//Print("Stat: " + actionName + " for player " + PlayerID + " Updated to " + Stats.Get(statID).Stat);
			}
			
		}

        return true;
		
	}

		void OnDeath(){

			PlayerDeaths++;
			for ( int j =0; j < Stats.Count(); j++ ){
				Stats.Get(j).Stat = 0;
				
			}
		
		
	}
	
};

