modded class MissionServer extends MissionBase
{
    void ~MissionServer()
	{
		//Print("Saving All Player Data From ~MissionServer");
		GetKillReward().SaveAllPlayers();
	}
	
    void MissionServer(){
       	GetRPCManager().AddRPC( "KR", "RPCSyncAllData", this, SingeplayerExecutionType.Both );		

    }	
	
	override void OnInit()
	{
		super.OnInit();
		GetKillReward();
		GetRPCManager().AddRPC( "KR", "RPCRequestKRPlayerData", this, SingeplayerExecutionType.Both );		
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "UpdateAllKRPlayersSettings", 600 * 1000, true);	
		GetKillReward().KRLoadAllPlayers();		
	}
	
	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		//Print("InvokeOnConnect KR Player Connected");
		GetKillReward().OnPlayerConnect(identity);
		super.InvokeOnConnect(player, identity);
		if ( identity )
		{
			string playerID = identity.GetPlainId();
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "SendAllData", 5000, true, new Param1<ref PlayerBase >( player ));
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLaterByName(this, "SendKillRewardSettings", 5500, false, new Param1<ref PlayerBase >( player ));
		
		}
	}
	

	
	override void InvokeOnDisconnect( PlayerBase player )
	{
		//Print("InvokeOnDisconnect KR Player Disconneted");
		if ( player.GetIdentity() ){
			GetKillReward().OnPlayerDisconnect(player);
		}
		
		super.InvokeOnDisconnect(player);
	}
	
	
	
	void RPCRequestKRPlayerData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		if (!sender)
		{
			return;
		}
		string playerID = sender.GetPlainId();
		//Print(" Request from:" + playerID + " for player data:");
		KillRewardPlayer playerData = GetKillReward().GetPlayer(playerID);
		GetRPCManager().SendRPC("KR", "RPCUpdateKRPlayerData", new Param1< KillRewardPlayer>(playerData), true, sender);
	}
	
	
	 void RPCSyncAllData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param2< map<string,string>, array<ref KillRewardPlayer> > data;
        if ( !ctx.Read( data ) ||  !sender ) return;
        ref array<string> playeronline = new array<string>;
        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        for (int i = 0; i < players.Count(); i++){
            DayZPlayer thePlayer = DayZPlayer.Cast(players.Get(i));
            if (thePlayer && thePlayer.GetIdentity()){
               playeronline.Insert(thePlayer.GetIdentity().GetPlainId());
            }
        }
        GetRPCManager().SendRPC("KR", "RPCSyncupdateAllData", new Param2< array<string>, array<ref KillRewardPlayer> >(playeronline,  GetKillReward().KillRewardPlayers),true,sender);
    }
	
	 void SendAllData( PlayerBase player)
    {
		PlayerIdentity identity = PlayerIdentity.Cast(player.GetIdentity());
        Param2< array<string>, array<ref KillRewardPlayer> > data;
        ref array<string> playeronline = new array<string>;
        ref array<Man> players = new array<Man>;
        GetGame().GetPlayers(players);
        for (int i = 0; i < players.Count(); i++){
            DayZPlayer thePlayer = DayZPlayer.Cast(players.Get(i));
            if (thePlayer && thePlayer.GetIdentity()){
                playeronline.Insert(thePlayer.GetIdentity().GetPlainId());
            }
        }
		GetRPCManager().SendRPC("KR", "RPCSyncupdateAllData", new Param2< array<string>, array<ref KillRewardPlayer> >(playeronline,  GetKillReward().KillRewardPlayers),true, identity);
    }
	
	
		void SendKillRewardSettings( PlayerBase player ){
		if (player.IsPlayerDisconnected()) { return; }
		PlayerIdentity identity = PlayerIdentity.Cast(player.GetIdentity());
		if (identity){
			string playerID = identity.GetPlainId();
			//Print("Sending Settings to Player: " + playerID);
			GetRPCManager().SendRPC("KR", "RPCUpdateKRSettings", new Param1< KillRewardPlayer> ( GetKillReward().GetPlayer(playerID)), true, identity);
			KillRewardPlayer playerData = GetKillReward().GetPlayer(playerID);		
			
			GetRPCManager().SendRPC("KR", "RPCUpdateKRPlayerData", new Param1< KillRewardPlayer>( playerData ), true, identity);
		}
	}
		
	void UpdateKRAllPlayersSettings(){
		PlayerBase p;
		string playerID;
		ref array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);
		for ( int i = 0; i < players.Count(); i++ )
		{
			p = PlayerBase.Cast(players.Get(i));
			if (!p.IsPlayerDisconnected())
			{
				playerID = p.GetIdentity().GetPlainId();
				string playerName = p.GetIdentity().GetName();
				GetRPCManager().SendRPC("KR", "RPCUpdateKRSettings", new Param1< KillRewardPlayer> (GetKillReward().GetPlayer(playerID)), true, p.GetIdentity());
			}
		}
	}	
		
		
};
