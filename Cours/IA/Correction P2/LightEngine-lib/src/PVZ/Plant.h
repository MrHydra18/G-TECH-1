#include "Entity.h"
#include "StateMachine.h"

class Plant : public Entity
{
	enum class State
	{
		Idle,
		Shooting,
		Reloading,

		Count
	};

	StateMachine<Plant> m_stateMachine;
	int m_bullet;
	int m_capacity;

	
public:
	void Shoot();
	void Reload();

protected:
	void OnInitialize() override;
	void OnUpdate() override;

private:
	const char* StateToStr() const;

	friend class IdlePLantState;
	friend class ShootingPLantState;
	friend class ReloadingPLantState;
};

class IdlePLantState : public StateBase<Plant>
{
public:
	void Start(Plant* type) override;
	void Update(Plant* type, float dt) override;
	void End(Plant* type) override;
};

class ShootingPLantState : public StateBase<Plant>
{
private:

	float m_timer;

public:
	void Start(Plant* type) override;
	void Update(Plant* type, float dt) override;
	void End(Plant* type) override;
};

class ReloadingPLantState : public StateBase<Plant>
{
private:
	
	float m_timer;

public:
	void Start(Plant* type) override;
	void Update(Plant* type, float dt) override;
	void End(Plant* type) override;
};