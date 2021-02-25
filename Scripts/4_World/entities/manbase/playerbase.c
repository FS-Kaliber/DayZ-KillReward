modded class PlayerBase extends ManBase {
		
	
    override void EEKilled( Object killer )
    {
		super.EEKilled(killer);			
		if (killer.IsInherited(SurvivorBase) || killer.IsInherited(Grenade_Base) || killer.IsWeapon() || killer.IsMeleeWeapon())
		{
			EntityAI killer_entity = EntityAI.Cast( killer );
			Man killerV = killer_entity.GetHierarchyRootPlayer();
			PlayerBase killerVictim = PlayerBase.Cast(killerV);
			string sourcePlayerID = killerV.GetIdentity().GetPlainId();
			GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param2<string, string>(sourcePlayerID, "PlayerKill"));
		} 
		if (GetIdentity()){
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetKRPlayer().OnDeath, 100, false);
		}
 }
	
	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
			
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);
		KROnEntityHit( source, this );
	}
	
		//Entity-Entity hit
	void KROnEntityHit( EntityAI source, Man target )
	{
		Man survivor = source.GetHierarchyRootPlayer();
		if ( survivor && source.IsWeapon() )
		{
			KROnPlayerToPlayerHit( survivor, target );
		}
	}
	
	protected void KROnPlayerToPlayerHit( Man shooter, Man target )
	{
		KillRewardPlayer p =  GetKillReward().GetPlayer(shooter.GetIdentity().GetPlainId());
		string sourcePlayerID = shooter.GetIdentity().GetPlainId();
		//calculate distance
		float longest_hit_dist = p.getStat("longest_survivor_hit");
		float current_dist = vector.Distance( shooter.GetPosition(), target.GetPosition() );
		int dist_update;
		
		if ( longest_hit_dist < current_dist )
		{
			dist_update = current_dist - longest_hit_dist;
			
		}
		
		GetGame().GetCallQueue( CALL_CATEGORY_SYSTEM ).CallLaterByName(GetKillReward(), "NewPlayerAction", 1, false, new Param3<string, string, int>(sourcePlayerID, "longest_survivor_hit", dist_update));
	}
	




		
	KillRewardPlayer GetKRPlayer()
	{
		if (GetGame().IsServer()){
			if (GetIdentity()){
				return GetKillReward().GetPlayer(GetIdentity().GetPlainId());
			} 
		} else {
			if (g_KillRewardPlayer){
				return g_KillRewardPlayer;
			} else {
				//Print("Player not defined on client");
			}
		}
		return null;
	}
	
}

