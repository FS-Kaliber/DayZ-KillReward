class KRStat
{
    string Name;
	int Stat;

    void KRStat(string statName, int stat) 
	{
        Name = statName;
		Stat = stat;
		
    }
	
	void updateStat(){
		Stat++;
	}
	
	void KRshoot( int shoot){
		Stat = shoot;
	}
};

