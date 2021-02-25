class LeaderboardGUI extends UIScriptedMenu {
	
	
	WrapSpacerWidget 		playerList;
	
	TextWidget				txtTime;
	TextWidget				txtHeading;
	TextWidget				PlayerOnline;
	TextWidget				Pname;
	
	Widget 					entryWidget;
	Widget 					FSLink;
	Widget 					FSButton;
	

	override Widget Init() {
		    
			
			layoutRoot = GetGame().GetWorkspace().CreateWidgets("KillReward/gui/layouts/leaderboard.layout");
			
			playerList = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("playerList"));
			txtTime = TextWidget.Cast(layoutRoot.FindAnyWidget("time"));
			txtHeading = TextWidget.Cast(layoutRoot.FindAnyWidget("heading"));
			FSLink = layoutRoot.FindAnyWidget("FSImage");
			FSButton = layoutRoot.FindAnyWidget("FSButton");
			PlayerOnline = TextWidget.Cast(layoutRoot.FindAnyWidget("PlayerOnline"));				
			dataupdate();

			return layoutRoot;
		
	}
		
	void dataupdate() {

            txtTime.SetText(""+RSGetDateTime());
        	txtHeading.SetText(" Bestenliste - Top 10 von " + m_KillReward_Players.Count() + " Spielern");
			PlayerOnline.SetText(" Spieler Online: " + 	m_KR_OnlinePlayer.Count());
		
			while (playerList.GetChildren())	
			playerList.RemoveChild(playerList.GetChildren());		


			for ( int i =0; i < 10; i++ )
			{	
				KillRewardPlayer p = m_KillReward_Players.Get(i);			
					if (!p)	
						continue;	
					entryWidget = GetGame().GetWorkspace().CreateWidgets("KillReward/gui/layouts/leaderboardentry.layout", playerList);
					TextWidget prank = TextWidget.Cast(entryWidget.FindAnyWidget("rank_text"));
					prank.SetText(" " + (i + 1)); // Rank
					TextWidget pname = TextWidget.Cast(entryWidget.FindAnyWidget("name_text"));
					pname.SetText(""+p.PlayerName); // Name
					TextWidget pkills = TextWidget.Cast(entryWidget.FindAnyWidget("kills_text"));
					pkills.SetText(""+p.getStat("ZombieKill")); // PlayerKills
					TextWidget pdeaths = TextWidget.Cast(entryWidget.FindAnyWidget("deaths_text"));
					pdeaths.SetText(""+p.PlayerDeaths); // Deaths
					TextWidget pkd = TextWidget.Cast(entryWidget.FindAnyWidget("kd_text"));
					pkd.SetText(""+p.GetKD()); // KD	
					
					
					
					
		
					for ( int i1 = 0; i1 < m_KR_OnlinePlayer.Count(); ++i1 )
					{

						string poid = m_KR_OnlinePlayer.Get(i1);
							if (p.PlayerID == poid)
								{ 
									
									pname.SetColor(0x00ff40);
									pname.SetAlpha(1);
									
								} 
									
						}			
			}
	}
				
	bool IsFocusable( Widget w )
	{
		if( w )
		{
			if( w == entryWidget || w == playerList);
			{
				return true;
			}
		}
		return false;
	}
	
	static string RSGetDate()
	{
		int year, month, day;		
		GetYearMonthDay(year, month, day);		
		string returned_message = day.ToStringLen(2) + "." + month.ToStringLen(2) + "." + year.ToStringLen(2);
		return returned_message;
	}

	static string RSGetTime()
	{
		int hour, minute, second;				
		GetHourMinuteSecond(hour, minute, second);
		string returned_message = hour.ToStringLen(2) + ":" + minute.ToStringLen(2);
		return returned_message;
	}

	static string RSGetDateTime()
	{
		int year, month, day, hour, minute, second;		
		GetYearMonthDay(year, month, day);		
		GetHourMinuteSecond(hour, minute, second);
		string returned_message = RSGetDate() + " " + RSGetTime();
		return returned_message;
	}	
	
	
	override bool OnClick(Widget w, int x, int y, int button) {
		if (w == FSLink) {
			////Print("Opening FS Link...");
			GetGame().OpenURL("https://www.friendly-survivors.de");
			return true;
		} else if (w == FSButton) {
			////Print("Opening FS Link");
			GetGame().OpenURL("https://www.friendly-survivors.de");
			return true;
		}
		return false;
	}
	
	
		override bool OnMouseEnter( Widget w, int x, int y )
	{		
		if( IsFocusable( w ) )
		{
			
			ColorHighlight( w );
						
			return true;
		}
		return false;
	}
	
		override bool OnMouseLeave( Widget w, Widget enterW, int x, int y )
	{		
		if( IsFocusable( w ) )
		{
			ColorNormal( w );
			
			
			return true;
		}
		return false;
	}
	
	
	
	
	//Coloring functions (Until WidgetStyles are useful)
	void ColorHighlight( Widget w )
	{
		if( w.IsInherited( ButtonWidget ) )
		{
			ButtonWidget button = ButtonWidget.Cast( w );
			button.SetTextColor( ARGB( 255, 200, 0, 0 ) );
		}
		
		w.SetColor( ARGB( 89, 89, 89, 200 ) );
		
		TextWidget text1	= TextWidget.Cast(w.FindAnyWidget( "rank" ) );
		TextWidget text2	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_label" ) );
		TextWidget text3	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_text_1" ) );
		ImageWidget image	= ImageWidget.Cast( w.FindAnyWidget( w.GetName() + "_image" ) );
		Widget option		= Widget.Cast( w.FindAnyWidget( "PanelWidget1" ) );

		
		if( text1 )
		{
			text1.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		
		if( text2 )
		{
			text2.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		
		if( text3 )
		{
			text3.SetColor( ARGB( 255, 255, 0, 0 ) );
			w.SetAlpha(1);
		}
		
		if( image )
		{
			image.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		
		if ( option )
		{
			option.SetColor( ARGB( 255, 255, 0, 0 ) );
		}
		

	}
	
	void ColorNormal( Widget w )
	{
		////Print("ColorNormal -> "+ w.GetName());
		//DumpStack();
		
		
		if( w.IsInherited( ButtonWidget ) )
		{
			ButtonWidget button = ButtonWidget.Cast( w );
			button.SetTextColor( ARGB( 89, 89, 89, 200 ) );
		}
		
		TextWidget text1	= TextWidget.Cast(w.FindAnyWidget( "rank" ) );
		TextWidget text2	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_label" ) );
		TextWidget text3	= TextWidget.Cast(w.FindAnyWidget( w.GetName() + "_text_1" ) );
		ImageWidget image	= ImageWidget.Cast( w.FindAnyWidget( w.GetName() + "_image" ) );
		Widget option		= Widget.Cast( w.FindAnyWidget( "PanelWidget1" ) );

		
		if( text1 )
		{
			text1.SetColor( ARGB( 89, 89, 89, 200 ) );
		}
		
		if( text2 )
		{
			text2.SetColor( ARGB( 89, 89, 89, 200 ) );
		}
		
		if( text3 )
		{
			text3.SetColor( ARGB( 89, 89, 89, 200 ) );
			w.SetAlpha(0);
		}
		
		if( image )
		{
			image.SetColor( ARGB( 89, 89, 89, 200 ) );
		}
		
		if ( option )
		{
			option.SetColor( 0x8c8c8c );
		}
		

	}
	
	
	
	
	
	
    override void OnHide() {
        super.OnHide();
        Mission mission = GetGame().GetMission();
        if (mission) {
            IngameHud hud = IngameHud.Cast( mission.GetHud() );
            if (hud) {
                hud.ShowQuickbarUI( true );
                hud.ShowHud( true );
            }
        }
    }
    
    override void OnShow() {
        super.OnShow();
        Mission mission = GetGame().GetMission();
        if (mission) {
            IngameHud hud = IngameHud.Cast( mission.GetHud() );
            if (hud) {
                hud.ShowQuickbarUI( false );
                hud.ShowHud( false );
            }
        }
    }
	
	override void Update( float timeslice ) {
		super.Update(timeslice);
		
		if( GetGame() && GetGame().GetInput() && GetGame().GetInput().LocalPress("UAUIBack", false) ) {
			CloseMe();
		}
	}
	
	void CloseMe() {
		MissionGameplay.Cast( GetGame().GetMission() ).PlayerControlEnable(true);
		GetGame().GetUIManager().CloseAll();
	}
	
	
}