
class KillRewardPanelUI extends UIScriptedMenu
{	
	private bool m_KillRewardPanelIsOpen;
	
	ImageWidget			m_KRImage;
	RichTextWidget		m_PlayerKills;
	RichTextWidget		m_ZombieKills;
	RichTextWidget		m_LongestShoot;
	RichTextWidget		m_WolfKills;
	RichTextWidget		m_BearKills;	   
	RichTextWidget		m_RoebuckKills;
	RichTextWidget		m_DoeKills;
	RichTextWidget		m_StagKills;
	RichTextWidget		m_HindKills;
	RichTextWidget		m_BoarKills;
	RichTextWidget		m_BullKills;
	RichTextWidget		m_CowKills;
	RichTextWidget		m_billygoatKills;
	RichTextWidget		m_goatKills;
	RichTextWidget		m_RoosterKills;
	RichTextWidget		m_HenKills;
	RichTextWidget		m_RamKills;
	RichTextWidget		m_EweKills;
	RichTextWidget		m_PigKills;


	string				m_layout = "KillReward/gui/layouts/KillRewardPanel.layout";
	
	override Widget Init()
    {
		
		layoutRoot 			= GetGame().GetWorkspace().CreateWidgets( m_layout );
		m_KRImage			= ImageWidget.Cast( layoutRoot.FindAnyWidget( "KRImage" ) );
		m_PlayerKills		= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRPlayerKills" ) );
		m_LongestShoot		= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRLongestShoot" ) );
		m_ZombieKills		= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRZombieKills" ) );
		m_WolfKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRWolfKills" ) );
		m_BearKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRBearKills" ) );	
		m_RoebuckKills		= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRRoebuckKills" ) );	
		m_DoeKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRDoeKills" ) );	
		m_StagKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRStagKills" ) );	
		m_HindKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRHindKills" ) );	
		m_BoarKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRBoarKills" ) );	
		m_BullKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRBullKills" ) );	
		m_CowKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRCowKills" ) );	
		m_billygoatKills	= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRbillygoatKills" ) );	
		m_goatKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRgoatKills" ) );	
		m_RoosterKills		= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRRoosterKills" ) );	
		m_HenKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRHenKills" ) );	
		m_RamKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRRamKills" ) );	
		m_EweKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KREweKills" ) );	
		m_PigKills			= RichTextWidget.Cast( layoutRoot.FindAnyWidget( "KRPigKills" ) );			


		
		m_KRImage.LoadImageFile( 0, "KillReward/data/KRpanelDE.paa" , true );	
		m_PlayerKills.SetText(""+g_KillRewardPlayer.getStat("PlayerKill"));	
		m_ZombieKills.SetText(""+g_KillRewardPlayer.getStat("ZombieKill"));	
		m_LongestShoot.SetText(""+g_KillRewardPlayer.getStat("longest_survivor_hit")+"m");	
		m_WolfKills.SetText(""+g_KillRewardPlayer.getStat("WolfKills"));
		m_BearKills.SetText(""+g_KillRewardPlayer.getStat("BearKills"));
		m_RoebuckKills.SetText(""+g_KillRewardPlayer.getStat("RoebuckKills"));
		m_DoeKills.SetText(""+g_KillRewardPlayer.getStat("DoeKills"));
		m_StagKills.SetText(""+g_KillRewardPlayer.getStat("StagKills"));
		m_HindKills.SetText(""+g_KillRewardPlayer.getStat("HindKills"));
		m_BoarKills.SetText(""+g_KillRewardPlayer.getStat("Wild_BoarKills"));
		m_BullKills.SetText(""+g_KillRewardPlayer.getStat("BullKills"));
		m_CowKills.SetText(""+g_KillRewardPlayer.getStat("CowKills"));
		m_billygoatKills.SetText(""+g_KillRewardPlayer.getStat("Billy_GoatKills"));
		m_goatKills.SetText(""+g_KillRewardPlayer.getStat("GoatKills"));
		m_RoosterKills.SetText(""+g_KillRewardPlayer.getStat("RoosterKills"));
		m_HenKills.SetText(""+g_KillRewardPlayer.getStat("HenKills"));
		m_RamKills.SetText(""+g_KillRewardPlayer.getStat("RamKills"));
		m_EweKills.SetText(""+g_KillRewardPlayer.getStat("EweKills"));
		m_PigKills.SetText(""+g_KillRewardPlayer.getStat("PigKills"));
				
        return layoutRoot; 
    }

	void updatekillData()
	{
		
		m_PlayerKills.SetText(""+g_KillRewardPlayer.getStat("PlayerKill"));	
		m_ZombieKills.SetText(""+g_KillRewardPlayer.getStat("ZombieKill"));	
		m_LongestShoot.SetText(""+g_KillRewardPlayer.getStat("longest_survivor_hit")+"m");	
		m_WolfKills.SetText(""+g_KillRewardPlayer.getStat("WolfKills"));
		m_BearKills.SetText(""+g_KillRewardPlayer.getStat("BearKills"));
		m_RoebuckKills.SetText(""+g_KillRewardPlayer.getStat("RoebuckKills"));
		m_DoeKills.SetText(""+g_KillRewardPlayer.getStat("DoeKills"));
		m_StagKills.SetText(""+g_KillRewardPlayer.getStat("StagKills"));
		m_HindKills.SetText(""+g_KillRewardPlayer.getStat("HindKills"));
		m_BoarKills.SetText(""+g_KillRewardPlayer.getStat("Wild_BoarKills"));
		m_BullKills.SetText(""+g_KillRewardPlayer.getStat("BullKills"));
		m_CowKills.SetText(""+g_KillRewardPlayer.getStat("CowKills"));
		m_billygoatKills.SetText(""+g_KillRewardPlayer.getStat("Billy_GoatKills"));
		m_goatKills.SetText(""+g_KillRewardPlayer.getStat("GoatKills"));
		m_RoosterKills.SetText(""+g_KillRewardPlayer.getStat("RoosterKills"));
		m_HenKills.SetText(""+g_KillRewardPlayer.getStat("HenKills"));
		m_RamKills.SetText(""+g_KillRewardPlayer.getStat("RamKills"));
		m_EweKills.SetText(""+g_KillRewardPlayer.getStat("EweKills"));
		m_PigKills.SetText(""+g_KillRewardPlayer.getStat("PigKills"));		
	}	

	
	
	bool IsOpen () {
		return m_KillRewardPanelIsOpen;
	}

	void SetOpen (bool open) {
		m_KillRewardPanelIsOpen = open;
	}
	
}
