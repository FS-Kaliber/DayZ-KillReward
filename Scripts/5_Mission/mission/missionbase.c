modded class MissionBase extends MissionBaseWorld
{

	
    override UIScriptedMenu CreateScriptedMenu (int id) {
        UIScriptedMenu menu = NULL;
        menu = super.CreateScriptedMenu (id);
        if (!menu) {
            switch (id) {
                case KILLREWARD_PANEL_MENU:
                    menu = new KillRewardPanelUI;
                    break;
            }
            if (menu) {
                menu.SetID (id);
            }
        }
        return menu;
    }
}