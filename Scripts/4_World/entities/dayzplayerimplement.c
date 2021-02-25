modded class DayZPlayerImplement {

	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)
	{
		super.CommandHandler(pDt,pCurrentCommandID,pCurrentCommandFinished);
		////Print("CommandHandler: " + pDt + " " + pCurrentCommandID + " " + pCurrentCommandFinished);
		UAInput localInput1 = GetUApi().GetInputByName("UALBMOpenLeaderboard");
		if(localInput1.LocalPress()) {
			MissionBaseWorld mission = MissionBaseWorld.Cast(GetGame().GetMission());
			if (mission)
				mission.OpenLeaderboardGUI();
		}
	}
}