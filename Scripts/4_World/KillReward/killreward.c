	ref KillReward 					m_KillReward;
	
	ref KillRewardPlayer 			g_KillRewardPlayer;

class KillReward {
	
	ref array<ref KillRewardPlayer> KillRewardPlayers = new ref array< ref KillRewardPlayer >;

	void KillReward()
	{	
	}
	
	void Init()
	{	
	}

	void SaveAllPlayers()
	{
		if ( KillRewardPlayers ){
			for ( int i = 0; i < KillRewardPlayers.Count(); i++ )
			{
				KillRewardPlayers.Get(i).saveData();
			}
			//Print("Saved all KR Player Data");
		} else {
			//Print("No KR Players Loaded to Save");
		}
	}
	
	
	
	void OnPlayerConnect(PlayerIdentity playerIdent)
	{
		if (IsPlayerLoaded(playerIdent.GetPlainId()))
		{
			//Print("Player " + playerIdent.GetPlainId()+ " connected and already KR loaded");	
			return;
		}else{
			loadPlayer(playerIdent.GetPlainId());
			
			GetPlayer(playerIdent.GetPlainId()).savePlayerName(playerIdent.GetName());
		}
	}
	
	void loadPlayer(string playerID){
		KillRewardPlayers.Insert(new ref KillRewardPlayer(playerID));
	}
	
	void OnPlayerDisconnect(PlayerBase player)
	{
		if ( player.GetIdentity() ) {
			//Print("Player " + player.GetIdentity().GetPlainId()+ " Disconnecting saving KR player data");	
			GetPlayer(player.GetIdentity().GetPlainId()).savePlayerName(player.GetIdentity().GetName());
			GetPlayer(player.GetIdentity().GetPlainId()).saveData();
		}
	}

	void NewPlayerAction(string playerID, string action, int shoot)
	{
		for ( int i = 0; i < KillRewardPlayers.Count(); i++ )
		{
			KillRewardPlayer p = KillRewardPlayers.Get(i);
			if ( p.PlayerID ==  playerID)
			{
				PlayerBase player = PlayerBase.Cast(KRGetPlayerBaseByID(playerID));
				string playername  = player.GetIdentity().GetName();
				p.NewAction(action, shoot);
				GetPlayer(player.GetIdentity().GetPlainId()).savePlayerName(player.GetIdentity().GetName());
				//ZombieKillReward
				if (g_Game.KRconfig.KillRewardZOMBIE.ZombieKillReward == 1)
					{
					if (action == "ZombieKill")
						{
							
							p.KRPoints(g_Game.KRconfig.KillRewardZOMBIE.ZombieKillPoints);								
							for(int zk=0;zk<p.getStat("ZombieKill");zk++){
								
							if (p.getStat("ZombieKill") == (g_Game.KRconfig.KillRewardZOMBIE.ZombieKills[zk] - 5)) 
									{				
										//Player Nachricht
										KRMessagePlayer(player,""+playername+" #KR_more", "#KR_Keep");			
									}
									
							if (p.getStat("ZombieKill") == g_Game.KRconfig.KillRewardZOMBIE.ZombieKills[zk]) 
								{		
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardZOMBIE.ZombieMoney[zk]);
									//Globale Nachricht
									if (g_Game.KRconfig.KillRewardBASE.ZombieGlobalMessage == 1)
										{
										KRMessageGlobal(""+playername+" #KR_has "+p.getStat("ZombieKill")+" #KR_Killed", "#KR_Congrat");		
										}
									if (g_Game.KRconfig.KillRewardGIFT.PlayerGift == 1)
										{	
										//Player Nachricht
										KRMessagePlayer(player,""+playername+" #KR_gift", "#KR_Reward");				
										//Geschenk			
										KRGift(player);
										}
								}
								if (p.getStat("ZombieKill") == g_Game.KRconfig.KillRewardZOMBIE.ZombieWeaponBox[zk]) 
										{
										//Player Nachricht
										KRMessagePlayer(player,""+playername+" #KR_giftbox", "#KR_Reward");			
										KRWeapon(player, g_Game.KRconfig.KillRewardZOMBIE.ZombieWeaponBoxNumber[zk]);
										}	
								
							}	
						}
					}

				 string killer_name  = player.GetIdentity().GetName();
				 PlayerIdentity Killer_identity = player.GetIdentity();	
				//PlayerKillReward
				if (action == "PlayerKill")
					{
						if(!player){
						}else{
					
		

						if (g_Game.KRconfig.KillRewardNEGATIVE.PlayerKillNegativeReward == 1)
							{
							p.KRLosePoints(g_Game.KRconfig.KillRewardNEGATIVE.Pointlose);	
							if (!player.CommitedSuicide())
								{  
		
									if(g_Game.KRconfig.KillRewardNEGATIVE.PlayerKill == 1)
										{					
											player.SetHealth(0);	
										}
					
										string SpawnItem;
										vector SpawnPoint;
										EntityAI spawn_bonus;
										
										float playerAngle = MiscGameplayFunctions.GetHeadingAngle(player);
										vector posModifier = Vector(-(3 * Math.Sin(playerAngle)), 0, 3 * Math.Cos(playerAngle));
										vector SpawnLocation = player.GetPosition() + posModifier;
									
										//Globale Nachricht
										if (g_Game.KRconfig.KillRewardBASE.PlayerGlobalMessage == 1 )
											{
												KRMessageGlobal(""+killer_name+" #KR_Badmessage", "#KR_BadReward");	
											}
											
											LoseMoney(Killer_identity , player); 
										
										for(int i1 = 0; i1 < g_Game.KRconfig.KillRewardNEGATIVE.PlayerKillNegativeRewardBonusQuantity; i1++) 
												{
													
													SpawnPoint = KR_RandomCircle(SpawnLocation, 5, 5, true, 0.5);
													SpawnItem = g_Game.KRconfig.KillRewardNEGATIVE.PlayerKillNegativeRewardBonus.GetRandomElement();
													spawn_bonus = EntityAI.Cast( GetGame().CreateObject(SpawnItem, SpawnPoint, false, true) );
													if (!spawn_bonus) {
														// Log spaw item failure
														//Print("[NEGATIVE REWARD] Spawn failed [" + i1 + "] '" + SpawnItem + "', does not exist in DayZ!");
														} 
														else 
														{
														spawn_bonus.SetLifetime(300);
														}
												}
								}	 
							}
	
					if (g_Game.KRconfig.KillRewardPLAYER.PlayerKillReward == 1)
						{		
							if (!player.CommitedSuicide())
									{
										// PlayerKillPoints
										p.KRPoints(g_Game.KRconfig.KillRewardPLAYER.PlayerKillPoints);	
										for(int pk=0;pk<p.getStat("PlayerKill");pk++){		
										if (player.StatGet("players_killed") == (g_Game.KRconfig.KillRewardPLAYER.PlayerKills[pk] - 5)) 
											{			
												//Player Nachricht
												KRMessagePlayer(player,""+killer_name+" #KR_more", "#KR_Keep");	
											}		
										if (p.getStat("PlayerKill") == g_Game.KRconfig.KillRewardPLAYER.PlayerKills[pk]) 
											{		
										player.increasePlayerCurrency(g_Game.KRconfig.KillRewardPLAYER.PlayerMoney[pk]);
										//Globale Nachricht
										if (g_Game.KRconfig.KillRewardBASE.PlayerGlobalMessage == 1)
											{			
												KRMessageGlobal(""+killer_name+" #KR_has "+p.getStat("PlayerKill")+" #KR_Killed_Player", "#KR_Congrat");		
											}	
										if (g_Game.KRconfig.KillRewardGIFT.PlayerGift == 1)
											{			
										//Player Nachricht
										KRMessagePlayer(player,""+killer_name+" #KR_gift", "#KR_Reward");			     
										//Geschenk
												KRGift(player);
											}
										}
										//WaeponBox
										if (p.getStat("PlayerKill") == g_Game.KRconfig.KillRewardPLAYER.PlayerWeaponBox[pk]) 
										{
										//Player Nachricht
										KRMessagePlayer(player,""+killer_name+" #KR_giftbox", "#KR_Reward");		
										KRWeapon(player, g_Game.KRconfig.KillRewardPLAYER.PlayerWeaponBoxNumber[pk]);
										}
										}		
										//Reward for longest SHOOT
										if (g_Game.KRconfig.KillRewardSHOOTDISTANCE.SHOOTReward == 1)
										{ 
											if(p.getStat("longest_survivor_hit") > g_Game.KRconfig.KillRewardSHOOTDISTANCE.PlayerSHOOTDISTANCE)
												{
													//Player Nachricht
													KRMessagePlayer(player,""+killer_name+" #KR_giftbox", "#KR_Reward");	
													KRWeapon(player, g_Game.KRconfig.KillRewardPLAYER.PlayerWeaponBoxNumber[pk]);	
													
													}	
												}
											}
											
									}
						}	
					}	
			

			
				//HuntingRewards
				if (action == "WolfKills")
					{	
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.WolfPoints);
							for(int H1=0;H1<p.getStat("WolfKills");H1++){
		
								if (p.getStat("WolfKills") == g_Game.KRconfig.KillRewardHUNTING.WolfKills[H1]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.WolfMoney[H1]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");			
									}
								}	
					}
				if (action == "BearKills")
					{	
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.BearPoints);		
							for(int H2=0;H2<p.getStat("BearKills");H2++){
								
								if (p.getStat("BearKills") == g_Game.KRconfig.KillRewardHUNTING.BearKills[H2]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.BearMoney[H2]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}				
					}
				if (action == "StagKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.StagPoints);						
							for(int H3=0;H3<p.getStat("StagKills");H3++){
								
								if (p.getStat("StagKills") == g_Game.KRconfig.KillRewardHUNTING.StagKills[H3]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.StagMoney[H3]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}	
				if (action == "HindKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.HindPoints);						
							for(int H4=0;H4<p.getStat("HindKills");H4++){		
										
								if (p.getStat("HindKills") == g_Game.KRconfig.KillRewardHUNTING.HindKills[H4]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.HindMoney[H4]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}
				if (action == "RoebuckKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.RoebuckPoints);						
							for(int H5=0;H5<p.getStat("RoebuckKills");H5++){
								
								if (p.getStat("RoebuckKills") == g_Game.KRconfig.KillRewardHUNTING.RoebuckKills[H5]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.RoebuckMoney[H5]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}
				if (action == "DoeKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.DoePoints);							
							for(int H6=0;H6<p.getStat("DoeKills");H6++){		
										
								if (p.getStat("DoeKills") == g_Game.KRconfig.KillRewardHUNTING.DoeKills[H6]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.DoeMoney[H6]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}
				if (action == "Wild_BoarKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.Wild_BoarPoints);							
							for(int H7=0;H7<p.getStat("Wild_BoarKills");H7++){		
										
								if (p.getStat("Wild_BoarKills") == g_Game.KRconfig.KillRewardHUNTING.Wild_BoarKills[H7]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.Wild_BoarMoney[H7]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}						
					}
				if (action == "PigKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.PigPoints);							
							for(int H8=0;H8<p.getStat("PigKills");H8++){		
										
								if (p.getStat("PigKills") == g_Game.KRconfig.KillRewardHUNTING.PigKills[H8]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.PigMoney[H8]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}
				if (action == "RamKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.RamPoints);							
							for(int H9=0;H9<p.getStat("RamKills");H9++){		
										
								if (p.getStat("RamKills") == g_Game.KRconfig.KillRewardHUNTING.RamKills[H9]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.RamMoney[H9]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}
				if (action == "EweKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.EwePoints);							
							for(int H10=0;H10<p.getStat("EweKills");H10++){		
										
								if (p.getStat("EweKills") == g_Game.KRconfig.KillRewardHUNTING.EweKills[H10]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.EweMoney[H10]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}
				if (action == "Billy_GoatKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.billy_goatPoints);							
							for(int H11=0;H11<p.getStat("Billy_GoatKills");H11++){		
										
								if (p.getStat("Billy_GoatKills") == g_Game.KRconfig.KillRewardHUNTING.billy_goatKills[H11]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.billy_goatMoney[H11]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}						
					}
				if (action == "GoatKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.goatPoints);							
							for(int H12=0;H12<p.getStat("GoatKills");H12++){		
										
								if (p.getStat("GoatKills") == g_Game.KRconfig.KillRewardHUNTING.goatKills[H12]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.goatMoney[H12]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}
				if (action == "BullKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.BullPoints);							
							for(int H13=0;H13<p.getStat("BullKills");H13++){		
										
								if (p.getStat("BullKills") == g_Game.KRconfig.KillRewardHUNTING.BullKills[H13]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.BullMoney[H13]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}						
					}
				if (action == "CowKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.CowPoints);							
							for(int H14=0;H14<p.getStat("CowKills");H14++){		
										
								if (p.getStat("CowKills") == g_Game.KRconfig.KillRewardHUNTING.CowKills[H14]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.CowMoney[H14]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}							
					}
				if (action == "RoosterKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.RoosterPoints);							
							for(int H15=0;H15<p.getStat("RoosterKills");H15++){		
										
								if (p.getStat("RoosterKills") == g_Game.KRconfig.KillRewardHUNTING.RoosterKills[H15]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.RoosterMoney[H15]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}						
					}
				if (action == "HenKills")
					{
						p.KRPoints(g_Game.KRconfig.KillRewardHUNTING.HenPoints);							
							for(int H16=0;H16<p.getStat("HenKills");H16++){		
										
								if (p.getStat("HenKills") == g_Game.KRconfig.KillRewardHUNTING.HenKills[H16]) 
									{	
									player.increasePlayerCurrency(g_Game.KRconfig.KillRewardHUNTING.HenMoney[H16]);
									KRMessagePlayer(player,""+killer_name+" #KR_Huntmes", "#KR_Hunt");					
									}
								}						
					}					
						if (player){
							GetRPCManager().SendRPC("KR", "RPCUpdateKRPlayerData", new Param1< KillRewardPlayer>( p ), true, player.GetIdentity());
						}

				return;
			}    
		}
	}

	KillRewardPlayer GetPlayer( string pID)
	{
		if (!IsPlayerLoaded(pID))
		{
			loadPlayer(pID);
		}
		for ( int i = 0; i < KillRewardPlayers.Count(); i++ )
		{
			if ( KillRewardPlayers.Get(i).PlayerID ==  pID)
			{
				return KillRewardPlayers.Get(i);
			}
		}
	    //Print("Failed to get KillRewardPlayer for Player " + pID);
		return null;
	}


	bool IsPlayerLoaded( string pID )
	{
		for ( int i = 0; i < KillRewardPlayers.Count(); i++ )
		{
			if ( KillRewardPlayers.Get(i).PlayerID ==  pID)
			{
				return true;
			}
		}
		return false;
	}

    void KRLoadAllPlayers()
    {
        ref array<string> playerDataBaseFiles = new array<string>;
        ref array<string> playerList = new array<string>;
        playerDataBaseFiles = KRFindFilesInDirectory(KillReward_PlayerDB);
        string tempFileName = "";
        string jsonName = "";
        int nameLength = 0;
        if (!playerDataBaseFiles) { return; }
        for ( int i =0; i < playerDataBaseFiles.Count(); i++ )
        {
            tempFileName = playerDataBaseFiles.Get(i);
            nameLength = tempFileName.Length();
            nameLength = nameLength - 5;
            jsonName = tempFileName.Substring(nameLength, 5);
            if ( jsonName == ".json" && tempFileName.Length() ==  22){
                playerList.Insert(tempFileName);
                //Print("Valid File Found: " + tempFileName + " Loading it now");
                tempFileName = tempFileName.Substring(0, 17);
                loadPlayer(tempFileName);
            } else {
                //Print("Invalid File Found: " + tempFileName + " Name Length: " + tempFileName.Length() + "Json Name: " + jsonName);
            }
        }
	}	

	void KRMessageGlobal(string message, string heading)
	{		
			
		if (g_Game.KRconfig.KillRewardBASE.MessageSystem == 4) // 1=TextChat 2=CF 3=VPPNotification 4=Notifications
			{	
			#ifdef NOTIFICATIONS
			NotificationSystem.SimpleNoticiation(heading, message, "KillReward/gui/images/kr.paa", ARGB(240, 0, 100, 200), 10);		
			#endif
	        }
		if (g_Game.KRconfig.KillRewardBASE.MessageSystem == 3) 
			{	
			#ifdef VPPNOTIFICATIONS
			g_Game.SendMessage(true,NULL,heading, message,10,2,false,true,"",0,0);
			#endif
			}
		if(g_Game.KRconfig.KillRewardBASE.MessageSystem == 2)
			{	
			m_KillRewardNotificationSystem.CreateNotification(new ref StringLocaliser(heading), new ref StringLocaliser(message), "KillReward/gui/images/kr.paa", ARGB(255,0,100,200),10);
			}
		if(g_Game.KRconfig.KillRewardBASE.MessageSystem == 1)
			{
			sendGlobalMessage(message);	
			}	
	}
	
	void KRMessagePlayer(PlayerBase player, string message, string heading)
	{		
		if (g_Game.KRconfig.KillRewardBASE.MessageSystem == 4) // 1=TextChat 2=CF 3=VPPNotification 4=Notifications
			{	
			#ifdef NOTIFICATIONS
			NotificationSystem.SimpleNoticiation(heading, message, "KillReward/gui/images/kr.paa", ARGB(240, 0, 100, 200), 10,player.GetIdentity());	
			#endif			
	        }
		if (g_Game.KRconfig.KillRewardBASE.MessageSystem == 3) 
			{	
			#ifdef VPPNOTIFICATIONS
			g_Game.SendMessage(false,player.GetIdentity(),heading, message,10,2,false,true,"",0,0);		
			#endif	
			}
		if(g_Game.KRconfig.KillRewardBASE.MessageSystem == 2)
			{	
			m_KillRewardNotificationSystem.CreateNotification(new ref StringLocaliser(heading), new ref StringLocaliser(message), "KillReward/gui/images/kr.paa", ARGB(255,0,100,200),10,player.GetIdentity());
			}
		if(g_Game.KRconfig.KillRewardBASE.MessageSystem == 1)
			{
			sendPlayerMessage(player,message);	
			}	
	}
	
	void sendGlobalMessage(string message)	
	{
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers( players );
		for ( int i = 0; i < players.Count(); ++i )
		{
			Man player = players.Get(i);
			if( player )
				sendPlayerMessage(player, message);
		}
	}

	void sendPlayerMessage(PlayerBase player, string message)	
	{
		Param1<string> Msgparam;
		Msgparam = new Param1<string>(message);
		GetGame().RPCSingleParam(player, ERPCs.RPC_USER_ACTION_MESSAGE, Msgparam, true, player.GetIdentity());
	}	
	
	void KRGift(PlayerBase killerVictim)
	{	
			EntityAI itemEnt;
			ItemBase itemcase;
			ItemBase itemBs;
			string giftdrink;
			string gifteat;
			string gifttools;
			string giftMedical;
			string giftbox;
		
		giftbox = g_Game.KRconfig.KillRewardGIFT.Giftbox.GetRandomElement();
		giftdrink = g_Game.KRconfig.KillRewardGIFT.Giftdrink.GetRandomElement();
		gifteat = g_Game.KRconfig.KillRewardGIFT.Gifteat.GetRandomElement();
		gifttools = g_Game.KRconfig.KillRewardGIFT.Gifttools.GetRandomElement();
		giftMedical = g_Game.KRconfig.KillRewardGIFT.Giftmedical.GetRandomElement();
		
		itemcase = ItemBase.Cast(GetGame().CreateObject(giftbox,killerVictim.GetPosition()));
		itemcase.GetInventory().CreateEntityInCargo(gifteat);
		itemcase.GetInventory().CreateEntityInCargo(giftdrink);
		itemcase.GetInventory().CreateEntityInCargo(gifttools);
		itemcase.GetInventory().CreateEntityInCargo(giftMedical);
		itemcase.SetLifetime(g_Game.KRconfig.KillRewardGIFT.GiftLifetime * 60);
	}
	
	void KRWeapon ( PlayerBase killerVictim , int BoxNumber ){ 
	
			ItemBase itemMoney;
			EntityAI itemEnt;
			ItemBase itemcase;
			ItemBase itemBs;
			ItemBase itemCount;
			ItemBase itemAtt;
			EntityAI itemEntWeapon;
			EntityAI itemEntBackpack;
			EntityAI suppressor;
			EntityAI Buttstock;
			EntityAI Bayonet;
			EntityAI Handguard;
			EntityAI Sight;
			EntityAI SightBatt;
			EntityAI magazine;
			EntityAI magazinBs;
			EntityAI itemEntMeeleWeapon;	

		for ( int b =0; b < g_Game.KRconfig.KillRewardWEAPONBOX.Count(); b++ )
        {
			if (BoxNumber == g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxNumber)
			{				
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX[b].Box ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxWeapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxWeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxWeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxWeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxWeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxWeaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxWeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						TStringArray Bonus = new TStringArray;	
						Bonus = g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxBonus;	
						for(int i1 = 0; i1 < g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxMagazinQuantity; i1++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX[b].BoxWeaponMagazin,itemBs);
						}
						for (int bb = 0; bb < Bonus.Count(); bb++) {
						createItemInWeaponBox(Bonus.Get(bb),itemBs);
						}
												
			}
		}
				
							
				
		}
		
		
	
	void createItemInWeaponBox(string itemType, ItemBase itemBs)
	{
		
		
		if (canCreateItemInWeaponBox(itemType, itemBs))
		{
							
                itemBs.GetInventory().CreateEntityInCargo(itemType);
			}
			else
			{
				itemBs.SpawnEntityOnGroundPos(itemType, itemBs.GetPosition());
			}
	}
	
	bool canCreateItemInWeaponBox(string itemType, ItemBase itemBs)
	{

		InventoryLocation il = new InventoryLocation;		
		if (itemBs.GetInventory().FindFirstFreeLocationForNewEntity(itemType, FindInventoryLocationType.ANY, il))
			return true;

		return false;			
	}
		
		
		
		vector KR_RandomCircle(vector centerpoint, float mind, float maxd, bool grounded, float groundoffset) {

		float h = Math.RandomFloat(0.0, 2.0) * Math.PI;
		float d = Math.RandomFloat(mind, maxd);
		vector offsetposition = centerpoint + Vector(Math.Cos(h) * d, 0.0, Math.Sin(h) * d);
		if (grounded) {
			offsetposition[1] = GetGame().SurfaceY(offsetposition[0], offsetposition[2]) + groundoffset;
		}
		return offsetposition;
	}

		void	LoseMoney( PlayerIdentity Killer_identity, PlayerBase killerVictim ){
				
				killerVictim.deductPlayerCurrency(g_Game.KRconfig.KillRewardNEGATIVE.LoseMoney);	
		}
	
};

static ref KillReward GetKillReward()
{
	if (!m_KillReward)
	{
		Print("Init KillReward");
		m_KillReward = new KillReward;
		m_KillReward.Init();
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(m_KillReward, "SaveAllPlayers", 300 * 1000, true);
	}
	return m_KillReward;
};


