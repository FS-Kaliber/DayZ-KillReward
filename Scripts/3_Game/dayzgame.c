ref NotificationSystem m_KillRewardNotificationSystem = new NotificationSystem();


modded class DayZGame extends CGame {
	
    autoptr ref KillReward_Config KRconfig;
	
	override void OnAfterCreate() {
        super.OnAfterCreate();
		if (IsServer()) {
		KRconfig = new KillReward_Config;
		}
		
	}

}