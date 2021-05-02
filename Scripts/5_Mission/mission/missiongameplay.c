	ref array<ref KillRewardPlayer> 	m_KillReward_Players;
	ref array<string> 					m_KR_OnlinePlayer;

modded class MissionGameplay extends MissionBase
{

	ref KillRewardPanelUI				m_KillRewardPanelUI;
	ref LeaderboardGUI					m_LeaderboardGUI;
	bool								m_KillRewardPanelOpening = false;
	
	void MissionGameplay()
	{
		GetRPCManager().AddRPC( "KR", "RPCUpdateKRPlayerData", this, SingeplayerExecutionType.Both );
		GetRPCManager().AddRPC( "KR", "RPCSyncupdateAllData", this, SingeplayerExecutionType.Both );
		GetRPCManager().AddRPC( "KR", "RPCUpdateKRSettings", this, SingeplayerExecutionType.Both );
	}
	
    void RPCSyncupdateAllData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
		//Print("[KillReward] [DebugClient] Received All Player Data");
        Param2< array<string> , array<KillRewardPlayer> > data;
        if ( !ctx.Read( data ) ) return;
        ref array<KillRewardPlayer> tempPlayers = new array<KillRewardPlayer>;
        tempPlayers.Copy(data.param2);
        int i = 0;		
		
        
		m_KR_OnlinePlayer = new array<string>;
		m_KR_OnlinePlayer.Copy(data.param1);
		
     
        m_KillReward_Players = new array<ref KillRewardPlayer>;
 								
		for (i = 0; i < tempPlayers.Count(); i++){
            if (tempPlayers.Get(i)){		
				bool Finished = false;
				int stopRunnaway = 0;
				while (stopRunnaway < 15 && !Finished && tempPlayers.Count() > 0){
					KillRewardPlayer TopPlayer = tempPlayers.Get(0);
					int TopPlayerIndex = 0;
					int ii = 0;
					while (tempPlayers.Count() != 0 && ii < tempPlayers.Count()){
						if (tempPlayers.Get(ii).KRGetPoints() > TopPlayer.KRGetPoints()){
							TopPlayer = tempPlayers.Get(ii);
							TopPlayerIndex = ii;
						}
						ii++;
					}
					if (tempPlayers.Count() == 0 && TopPlayer.KRGetPoints() <= 0.0 ){
						Finished = true;
					} else {
						m_KillReward_Players.Insert(TopPlayer);
						tempPlayers.RemoveItem(TopPlayer);
					}	
					stopRunnaway++;
				}
				
            }
        }
    }	
	
	
	override void OpenLeaderboardGUI() {
		if (!GetGame() || !GetGame().GetUIManager())
			return;
		if (GetGame().GetUIManager().GetMenu() == NULL) {
			GetGame().GetUIManager().ShowScriptedMenu(new LeaderboardGUI(), NULL);
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(m_LeaderboardGUI, "dataupdate", 400, false); 
			LockControlsLeaderboard();
		} else {
			LeaderboardGUI gui;
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(m_LeaderboardGUI, "dataupdate", 400, false); 
			if (Class.CastTo(gui, GetGame().GetUIManager().GetMenu())) {
				gui.CloseMe();
			}
		}
	}
	
	void LockControlsLeaderboard() {
		GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_INVENTORY);
		GetGame().GetGame().GetUIManager().ShowUICursor(true);
	}
	
	
	override void OnUpdate (float timeslice) {
        super.OnUpdate (timeslice);

        Input input = GetGame().GetInput();
        if (input.LocalPress("UAUIBack", false)) {
            if (m_KillRewardPanelUI != NULL && GetGame().GetUIManager().GetMenu() == m_KillRewardPanelUI) {
                KillRewardClosePanel();
				m_KillRewardPanelOpening = false;
            }
        }

        if (input.LocalPress("UAKillRewardPanel", false)) {
            if (m_KillRewardPanelUI) {
                if (m_KillRewardPanelUI.IsOpen()) {
					KillRewardClosePanel();
					m_KillRewardPanelOpening = false;
                } else if (GetGame().GetUIManager().GetMenu() == NULL) {
					GetRPCManager().SendRPC("KR", "RPCRequestKRPlayerData", NULL, true);
					if (!m_KillRewardPanelOpening){
					GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "KillRewardOpenPanel", 400, false);
                }
				m_KillRewardPanelOpening = true;
				}
            } else if (GetGame().GetUIManager().GetMenu() == NULL && m_KillRewardPanelUI == null) {
				GetRPCManager().SendRPC("KR", "RPCRequestKRPlayerData", NULL, true);
				if (!m_KillRewardPanelOpening){
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(this, "KillRewardCreatePanel", 400, false);
            }
			m_KillRewardPanelOpening = true;
			}
        }
    }
		
	void KillRewardCreatePanel()
	{

	    	KillRewardLockControls();
	        m_KillRewardPanelUI = KillRewardPanelUI.Cast(GetUIManager().EnterScriptedMenu(KILLREWARD_PANEL_MENU, null));
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(m_KillRewardPanelUI, "updatekillData", 500, false);
	        m_KillRewardPanelUI.SetOpen(true);
			m_KillRewardPanelOpening = false;
		
	}
	
	void KillRewardOpenPanel()
	{	

			GetGame().GetUIManager().ShowScriptedMenu(m_KillRewardPanelUI, NULL);
	        m_KillRewardPanelUI.SetOpen(true);
	    	KillRewardLockControls();
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLaterByName(m_KillRewardPanelUI, "updatekillData", 500, false);
			m_KillRewardPanelOpening = false;
	}
	
	void KillRewardClosePanel()
	{
		m_KillRewardPanelUI.SetOpen(false);
        GetGame().GetUIManager().HideScriptedMenu(m_KillRewardPanelUI);
		KillRewardUnLockControls();
		m_KillRewardPanelOpening = false;
	}
	
	private void KillRewardLockControls() {
        GetGame().GetMission().PlayerControlDisable(INPUT_EXCLUDE_MOUSE_ALL);
        GetGame().GetUIManager().ShowUICursor(true);
    }

    private void KillRewardUnLockControls() {
        GetGame().GetMission().PlayerControlEnable(false);
        GetGame().GetInput().ResetGameFocus();
        GetGame().GetUIManager().ShowUICursor(false);
    }
	
	void RPCUpdateKRPlayerData( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		//Print("[KillReward] [DebugClient] Received Player Data");
		Param1< KillRewardPlayer> data;
		if ( !ctx.Read( data ) ) return;
            g_KillRewardPlayer = data.param1;
			
			
	}
	

	
	void RPCUpdateKRSettings( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
	{
		//Print("[KillReward] [DebugClient] Received Settings");
		Param1<KillRewardPlayer> data;
		if ( !ctx.Read( data ) ) return;
		g_KillRewardPlayer = data.param1;

	}	

}