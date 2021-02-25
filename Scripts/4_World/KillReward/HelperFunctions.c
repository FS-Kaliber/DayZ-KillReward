PlayerBase KRGetPlayerBaseByID( string pID )
{
	PlayerBase p;
	ref array<Man> players = new array<Man>;
	GetGame().GetPlayers(players);
	for ( int i = 0; i < players.Count(); i++ )
	{
		p = PlayerBase.Cast(players.Get(i));
		if ( p.GetIdentity().GetPlainId() ==  pID )
		{
			//Print("Found Player " + p.GetIdentity().GetName() + " with id " + pID);	
			return p;
		}
	}
	//Print("Failed to GetPlayerBaseByID for Player " + pID );
	return null;
};

PlayerBase KRGetPlayerBaseByName( string pName )
{
	PlayerBase p;
	ref array<Man> players = new array<Man>;
	GetGame().GetPlayers(players);
	for ( int i = 0; i < players.Count(); i++ )
	{
		p = PlayerBase.Cast(players.Get(i));
		//Print("Looking for Player " + pName + " Checking against Name " + p.GetIdentity().GetName() + " Full Name: " + p.GetIdentity().GetFullName());	
		if ( p.GetIdentity().GetName() ==  pName)
		{
			//Print("Found Player " + p.GetIdentity().GetName() + " with Name " + pName);	
			return p;
		}
	}
	//Print("Failed to GetPlayerBaseByName for Player " + pName);
	return null;
};