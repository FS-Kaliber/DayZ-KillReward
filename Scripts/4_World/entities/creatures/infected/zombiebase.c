modded class ZombieBase
{
			
    override void EEKilled( Object killer )
    {
		super.EEKilled(killer);	

		if (killer.IsInherited(SurvivorBase) || killer.IsWeapon() || killer.IsMeleeWeapon())
		{
			EntityAI killer_entity = EntityAI.Cast( killer );
			Man killerV = killer_entity.GetHierarchyRootPlayer();
			
			string sourcePlayerID = killerV.GetIdentity().GetPlainId();
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "ZombieKill"));
		}
    }
	


}