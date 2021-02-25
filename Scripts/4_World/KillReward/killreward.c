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

		
				
		switch (BoxNumber.ToString()) 
		{ 
                case "1":
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box1 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box1Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box1WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box1WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box1WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box1WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box1Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box1WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						TStringArray Bonus1 = new TStringArray;	
						Bonus1 = g_Game.KRconfig.KillRewardWEAPONBOX.Box1Bonus;	
						for(int i1 = 0; i1 < g_Game.KRconfig.KillRewardWEAPONBOX.Box1MagazinQuantity; i1++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box1WeaponMagazin,itemBs);
						}
						for (int bb = 0; bb < Bonus1.Count(); bb++) {
						createItemInWeaponBox(Bonus1.Get(bb),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
				break;
				
				case "2":
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box2 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box2Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box2WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box2WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box2WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box2WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box2Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box2WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i2 = 0; i2 < g_Game.KRconfig.KillRewardWEAPONBOX.Box2MagazinQuantity; i2++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box2WeaponMagazin,itemBs);
						}
						TStringArray Bonus2 = new TStringArray;	
						Bonus2 = g_Game.KRconfig.KillRewardWEAPONBOX.Box2Bonus; 	
						for (int b2 = 0; b2 < Bonus2.Count(); b2++) {
						createItemInWeaponBox(Bonus2.Get(b2),itemBs);
						}						
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						

				break;
		
				case "3":
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box3 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box3Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box3WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box3WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box3WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box3WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box3Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box3WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i3 = 0; i3 < g_Game.KRconfig.KillRewardWEAPONBOX.Box3MagazinQuantity; i3++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box3WeaponMagazin,itemBs);
						}
						TStringArray Bonus3 = new TStringArray;	
						Bonus3 = g_Game.KRconfig.KillRewardWEAPONBOX.Box3Bonus;
						for (int b3 = 0; b3 < Bonus3.Count(); b3++) {
						createItemInWeaponBox(Bonus3.Get(b3),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);
				break;
				
				case "4":
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box4 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box4Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box4WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box4WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box4WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box4WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box4Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box4WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i4 = 0; i4 < g_Game.KRconfig.KillRewardWEAPONBOX.Box4MagazinQuantity; i4++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box4WeaponMagazin,itemBs);
						}	
						TStringArray Bonus4 = new TStringArray;	
						Bonus4 = g_Game.KRconfig.KillRewardWEAPONBOX.Box4Bonus;
						for (int b4 = 0; b4 < Bonus4.Count(); b4++) {
						createItemInWeaponBox(Bonus4.Get(b4),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
	
				break;
				
				case "5":
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box5 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box5Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box5WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box5WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box5WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box5WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box5Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box5WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i5 = 0; i5 < g_Game.KRconfig.KillRewardWEAPONBOX.Box5MagazinQuantity; i5++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box5WeaponMagazin,itemBs);
						}	
						TStringArray Bonus5 = new TStringArray;
						Bonus5 = g_Game.KRconfig.KillRewardWEAPONBOX.Box5Bonus;
						for (int b5 = 0; b5 < Bonus5.Count(); b5++) {
						createItemInWeaponBox(Bonus5.Get(b5),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
				break;
				
				case "6":
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box6 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box6Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box6WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box6WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box6WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box6WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box6Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box6WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i6 = 0; i6 < g_Game.KRconfig.KillRewardWEAPONBOX.Box6MagazinQuantity; i6++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box6WeaponMagazin,itemBs);
						}	
						TStringArray Bonus6 = new TStringArray;
						Bonus6 = g_Game.KRconfig.KillRewardWEAPONBOX.Box6Bonus;						
						for (int b6 = 0; b6 < Bonus6.Count(); b6++) {
						createItemInWeaponBox(Bonus6.Get(b6),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
					
				break;

				case "7":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box7 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box7Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box7WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box7WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box7WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box7WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box7Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box7WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i7 = 0; i7 < g_Game.KRconfig.KillRewardWEAPONBOX.Box7MagazinQuantity; i7++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box7WeaponMagazin,itemBs);
						}
						TStringArray Bonus7 = new TStringArray;
						Bonus7 = g_Game.KRconfig.KillRewardWEAPONBOX.Box7Bonus;							
						for (int b7 = 0; b7 < Bonus7.Count(); b7++) {
						createItemInWeaponBox(Bonus7.Get(b7),itemBs);
						}						
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "8":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box8 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box8Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box8WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box8WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box8WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box8WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box8Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box8WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i8 = 0; i8 < g_Game.KRconfig.KillRewardWEAPONBOX.Box8MagazinQuantity; i8++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box8WeaponMagazin,itemBs);
						}	
						TStringArray Bonus8 = new TStringArray;
						Bonus8 = g_Game.KRconfig.KillRewardWEAPONBOX.Box8Bonus;
						for (int b8 = 0; b8 < Bonus8.Count(); b8++) {
						createItemInWeaponBox(Bonus8.Get(b8),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;
				
				case "9":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box9 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box9Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box9WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box9WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box9WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box9WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box9Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box9WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i9 = 0; i9 < g_Game.KRconfig.KillRewardWEAPONBOX.Box9MagazinQuantity; i9++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box9WeaponMagazin,itemBs);
						}
						TStringArray Bonus9 = new TStringArray;
						Bonus9 = g_Game.KRconfig.KillRewardWEAPONBOX.Box9Bonus;
						for (int b9 = 0; b9 < Bonus9.Count(); b9++) {
						createItemInWeaponBox(Bonus9.Get(b9),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;
				
				case "10":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box10 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box10Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box10WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box10WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box10WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box10WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box10Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box10WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i10 = 0; i10 < g_Game.KRconfig.KillRewardWEAPONBOX.Box10MagazinQuantity; i10++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box10WeaponMagazin,itemBs);
						}
						TStringArray Bonus10 = new TStringArray;
						Bonus10 = g_Game.KRconfig.KillRewardWEAPONBOX.Box10Bonus;
						for (int b10 = 0; b10 < Bonus10.Count(); b10++) {
						createItemInWeaponBox(Bonus10.Get(b10),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "11":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box11 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box11Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box11WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box11WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box11WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box11WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box11Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box11WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i11 = 0; i11 < g_Game.KRconfig.KillRewardWEAPONBOX.Box11MagazinQuantity; i11++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box11WeaponMagazin,itemBs);
						}
						TStringArray Bonus11 = new TStringArray;
						Bonus11 = g_Game.KRconfig.KillRewardWEAPONBOX.Box11Bonus;
						for (int b11 = 0; b11 < Bonus11.Count(); b11++) {
						createItemInWeaponBox(Bonus11.Get(b11),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "12":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box12 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box12Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box12WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box12WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box12WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box12WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box12Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box12WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i12 = 0; i12 < g_Game.KRconfig.KillRewardWEAPONBOX.Box12MagazinQuantity; i12++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box12WeaponMagazin,itemBs);
						}
						TStringArray Bonus12 = new TStringArray;
						Bonus12 = g_Game.KRconfig.KillRewardWEAPONBOX.Box12Bonus;
						for (int b12 = 0; b12 < Bonus12.Count(); b12++) {
						createItemInWeaponBox(Bonus12.Get(b12),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;
				
				case "13":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box13 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box13Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box13WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box13WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box13WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box13WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box13Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box13WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i13 = 0; i13 < g_Game.KRconfig.KillRewardWEAPONBOX.Box13MagazinQuantity; i13++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box13WeaponMagazin,itemBs);
						}
						TStringArray Bonus13 = new TStringArray;
						Bonus13 = g_Game.KRconfig.KillRewardWEAPONBOX.Box13Bonus;
						for (int b13 = 0; b13 < Bonus13.Count(); b13++) {
						createItemInWeaponBox(Bonus13.Get(b13),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "14":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box14 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box14Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box14WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box14WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box14WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box14WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box14Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box14WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i14 = 0; i14 < g_Game.KRconfig.KillRewardWEAPONBOX.Box14MagazinQuantity; i14++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box14WeaponMagazin,itemBs);
						}
						TStringArray Bonus14 = new TStringArray;
						Bonus14 = g_Game.KRconfig.KillRewardWEAPONBOX.Box14Bonus;
						for (int b14 = 0; b14 < Bonus14.Count(); b14++) {
						createItemInWeaponBox(Bonus14.Get(b14),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "15":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box15 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box15Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box15WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box15WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box15WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box15WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box15Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box15WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i15 = 0; i15 < g_Game.KRconfig.KillRewardWEAPONBOX.Box15MagazinQuantity; i15++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box15WeaponMagazin,itemBs);
						}	
						TStringArray Bonus15 = new TStringArray;
						Bonus15 = g_Game.KRconfig.KillRewardWEAPONBOX.Box15Bonus;
						for (int b15 = 0; b15 < Bonus15.Count(); b15++) {
						createItemInWeaponBox(Bonus15.Get(b15),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "16":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box16 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box16Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box16WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box16WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box16WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box16WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box16Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box16WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i16 = 0; i16 < g_Game.KRconfig.KillRewardWEAPONBOX.Box16MagazinQuantity; i16++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box16WeaponMagazin,itemBs);
						}
						TStringArray Bonus16 = new TStringArray;
						Bonus16 = g_Game.KRconfig.KillRewardWEAPONBOX.Box16Bonus;
						for (int b16 = 0; b16 < Bonus16.Count(); b16++) {
						createItemInWeaponBox(Bonus16.Get(b16),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "17":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box17 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box17Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box17WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box17WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box17WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box17WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box17Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box17WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i17 = 0; i17 < g_Game.KRconfig.KillRewardWEAPONBOX.Box17MagazinQuantity; i17++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box17WeaponMagazin,itemBs);
						}
						TStringArray Bonus17 = new TStringArray;
						Bonus17 = g_Game.KRconfig.KillRewardWEAPONBOX.Box17Bonus;
						for (int b17 = 0; b17 < Bonus17.Count(); b17++) {
						createItemInWeaponBox(Bonus17.Get(b17),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "18":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box18 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box18Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box18WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box18WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box18WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box18WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box18Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box18WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i18 = 0; i18 < g_Game.KRconfig.KillRewardWEAPONBOX.Box18MagazinQuantity; i18++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box18WeaponMagazin,itemBs);
						}
						TStringArray Bonus18 = new TStringArray;
						Bonus18 = g_Game.KRconfig.KillRewardWEAPONBOX.Box18Bonus;
						for (int b18 = 0; b18 < Bonus18.Count(); b18++) {
						createItemInWeaponBox(Bonus18.Get(b18),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "19":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box19 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box19Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box19WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box19WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box19WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box19WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box19Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box19WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i19 = 0; i19 < g_Game.KRconfig.KillRewardWEAPONBOX.Box19MagazinQuantity; i19++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box19WeaponMagazin,itemBs);
						}
						TStringArray Bonus19 = new TStringArray;
						Bonus19 = g_Game.KRconfig.KillRewardWEAPONBOX.Box19Bonus;
						for (int b19 = 0; b19 < Bonus19.Count(); b19++) {
						createItemInWeaponBox(Bonus19.Get(b19),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "20":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box20 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box20Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box20WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box20WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box20WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box20WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box20Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box20WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i20 = 0; i20 < g_Game.KRconfig.KillRewardWEAPONBOX.Box20MagazinQuantity; i20++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box20WeaponMagazin,itemBs);
						}
						TStringArray Bonus20 = new TStringArray;
						Bonus20 = g_Game.KRconfig.KillRewardWEAPONBOX.Box20Bonus;
						for (int b20 = 0; b20 < Bonus20.Count(); b20++) {
						createItemInWeaponBox(Bonus20.Get(b20),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;
				
				case "21":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box21 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box21Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box21WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box21WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box21WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box21WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box21Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box21WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i21 = 0; i21 < g_Game.KRconfig.KillRewardWEAPONBOX.Box21MagazinQuantity; i21++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box21WeaponMagazin,itemBs);
						}
						TStringArray Bonus21 = new TStringArray;
						Bonus21 = g_Game.KRconfig.KillRewardWEAPONBOX.Box21Bonus;
						for (int b21 = 0; b21 < Bonus21.Count(); b21++) {
						createItemInWeaponBox(Bonus21.Get(b21),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "22":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box22 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box22Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box22WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box22WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box22WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box22WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box22Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box22WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i22 = 0; i22 < g_Game.KRconfig.KillRewardWEAPONBOX.Box22MagazinQuantity; i22++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box22WeaponMagazin,itemBs);
						}
						TStringArray Bonus22 = new TStringArray;
						Bonus22 = g_Game.KRconfig.KillRewardWEAPONBOX.Box22Bonus;
						for (int b22 = 0; b22 < Bonus22.Count(); b22++) {
						createItemInWeaponBox(Bonus22.Get(b22),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;
				
				case "23":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box23 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box23Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box23WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box23WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box23WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box23WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box23Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box23WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i23 = 0; i23 < g_Game.KRconfig.KillRewardWEAPONBOX.Box23MagazinQuantity; i23++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box23WeaponMagazin,itemBs);
						}
						TStringArray Bonus23 = new TStringArray;
						Bonus23 = g_Game.KRconfig.KillRewardWEAPONBOX.Box23Bonus;
						for (int b23 = 0; b23 < Bonus23.Count(); b23++) {
						createItemInWeaponBox(Bonus23.Get(b23),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "24":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box24 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box24Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box24WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box24WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box24WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box24WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box24Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box24WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i24 = 0; i24 < g_Game.KRconfig.KillRewardWEAPONBOX.Box24MagazinQuantity; i24++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box24WeaponMagazin,itemBs);
						}
						TStringArray Bonus24 = new TStringArray;
						Bonus24 = g_Game.KRconfig.KillRewardWEAPONBOX.Box24Bonus;
						for (int b24 = 0; b24 < Bonus24.Count(); b24++) {
						createItemInWeaponBox(Bonus24.Get(b24),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "25":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box25 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box25Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box25WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box25WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box25WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box25WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box25Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box25WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i25 = 0; i25 < g_Game.KRconfig.KillRewardWEAPONBOX.Box25MagazinQuantity; i25++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box25WeaponMagazin,itemBs);
						}
						TStringArray Bonus25 = new TStringArray;
						Bonus25 = g_Game.KRconfig.KillRewardWEAPONBOX.Box25Bonus;
						for (int b25 = 0; b25 < Bonus25.Count(); b25++) {
						createItemInWeaponBox(Bonus25.Get(b25),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "26":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box26 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box26Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box26WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box26WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box26WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box26WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box26Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box26WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i26 = 0; i26 < g_Game.KRconfig.KillRewardWEAPONBOX.Box26MagazinQuantity; i26++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box26WeaponMagazin,itemBs);
						}
						TStringArray Bonus26 = new TStringArray;
						Bonus26 = g_Game.KRconfig.KillRewardWEAPONBOX.Box26Bonus;
						for (int b26 = 0; b26 < Bonus26.Count(); b26++) {
						createItemInWeaponBox(Bonus26.Get(b26),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "27":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box27 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box27Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box27WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box27WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box27WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box27WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box27Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box27WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i27 = 0; i27 < g_Game.KRconfig.KillRewardWEAPONBOX.Box27MagazinQuantity; i27++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box27WeaponMagazin,itemBs);
						}
						TStringArray Bonus27 = new TStringArray;
						Bonus27 = g_Game.KRconfig.KillRewardWEAPONBOX.Box27Bonus;
						for (int b27 = 0; b27 < Bonus27.Count(); b27++) {
						createItemInWeaponBox(Bonus27.Get(b27),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "28":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box28 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box28Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box28WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box28WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box28WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box28WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box28Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box28WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i28 = 0; i28 < g_Game.KRconfig.KillRewardWEAPONBOX.Box28MagazinQuantity; i28++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box28WeaponMagazin,itemBs);
						}
						TStringArray Bonus28 = new TStringArray;
						Bonus28 = g_Game.KRconfig.KillRewardWEAPONBOX.Box28Bonus;
						for (int b28 = 0; b28 < Bonus28.Count(); b28++) {
						createItemInWeaponBox(Bonus28.Get(b28),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "29":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box29 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box29Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box29WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box29WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box29WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box29WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box29Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box29WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i29 = 0; i29 < g_Game.KRconfig.KillRewardWEAPONBOX.Box29MagazinQuantity; i29++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box29WeaponMagazin,itemBs);
						}	
						TStringArray Bonus29 = new TStringArray;
						Bonus29 = g_Game.KRconfig.KillRewardWEAPONBOX.Box29Bonus;
						for (int b29 = 0; b29 < Bonus29.Count(); b29++) {
						createItemInWeaponBox(Bonus29.Get(b29),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;	
				
				case "30":	
						itemBs = ItemBase.Cast(GetGame().CreateObject(g_Game.KRconfig.KillRewardWEAPONBOX.Box30 ,killerVictim.GetPosition()));
						itemEntWeapon = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box30Weapon);
						magazine = itemBs.GetInventory().CreateEntityInCargo(g_Game.KRconfig.KillRewardWEAPONBOX.Box30WeaponMagazin);
						magazine = ItemBase.Cast(itemEntWeapon);						
						Bayonet = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box30WeaponBayonet);
						Bayonet = ItemBase.Cast(itemEntWeapon);
						Buttstock = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box30WeaponButtstock);
						Buttstock = ItemBase.Cast(itemEntWeapon);
						Handguard = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box30WeaponHandguard);
						Handguard = ItemBase.Cast(itemEntWeapon);
						suppressor = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box30Weaponsuppressor);
						suppressor = ItemBase.Cast(itemEntWeapon);
						Sight = itemEntWeapon.GetInventory().CreateAttachment(g_Game.KRconfig.KillRewardWEAPONBOX.Box30WeaponSight);
						Sight = ItemBase.Cast(itemEntWeapon);
						for(int i30 = 0; i30 < g_Game.KRconfig.KillRewardWEAPONBOX.Box30MagazinQuantity; i30++) {
						createItemInWeaponBox(g_Game.KRconfig.KillRewardWEAPONBOX.Box30WeaponMagazin,itemBs);
						}	
						TStringArray Bonus30 = new TStringArray;
						Bonus30 = g_Game.KRconfig.KillRewardWEAPONBOX.Box30Bonus;
						for (int b30 = 0; b30 < Bonus30.Count(); b30++) {
						createItemInWeaponBox(Bonus30.Get(b30),itemBs);
						}
						itemBs.SetLifetime(g_Game.KRconfig.KillRewardWEAPONBOX.BoxLifetime * 60);						
						
				break;					
				
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


