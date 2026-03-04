#pragma once
#include "RmStates.h"


//classe abstraite
class RmConditions : public Condition<RugbyMan>
{
protected:
	bool m_assert = true;
public:
	RmConditions(bool _assert) { m_assert = _assert; }
	virtual bool Test(RugbyMan* player) = 0;
};


class TeamHasBall : public RmConditions {

public:
	TeamHasBall(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* mate) override;
};

class OtherTeamHasBall : public RmConditions {

public:
	OtherTeamHasBall(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* mate) override;
};


class EnemyInFrontOfMe : public RmConditions {

public:
	EnemyInFrontOfMe(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* player) override;
};

class TeamateBehind : public RmConditions {

public:
	TeamateBehind(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* player) override;
};


class HaveBall : public RmConditions {

public:
	HaveBall(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* mate) override;
};

class IsStun : public RmConditions {

public:
	IsStun(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* mate) override;
};

class IsManuel : public RmConditions {

public:
	IsManuel(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* mate) override;
};

class BallIsLoseSince : public RmConditions {
private:
	float m_time;
public:
	BallIsLoseSince(bool _assert, float _time) : RmConditions(_assert), m_time(_time) {}
	bool Test(RugbyMan* mate) override;
};

class TeamWillHaveBall : public RmConditions {

public:
	TeamWillHaveBall(bool _assert) : RmConditions(_assert){}
	bool Test(RugbyMan* mate) override;
};

class IWillHaveBall : public RmConditions {

public:
	IWillHaveBall(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* mate) override;
};

class OtherTeamWillHaveBall : public RmConditions {

public:
	OtherTeamWillHaveBall(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* mate) override;
};

class IsBorderField : public RmConditions {

public:
	IsBorderField(bool _assert) : RmConditions(_assert) {}
	bool Test(RugbyMan* mate) override;
};