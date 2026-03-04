#pragma once
#include <vector>
#include "Lib2D/Drawable.h"
#include "Entity.h"

class Scene : public Drawable
{
protected:
	std::vector<Entity*> EntityStock;
	const char* m_Name;

public:
	Scene(const char*name) : m_Name(name) {}

	const char* GetName() { return m_Name; }

	void UpdateAll();
	void Draw(Window* win) override;
	void ChangeColor(Window* win) override;
	void DeletAll();

	template <typename T>
	T* NewEntity();

	template <typename T>
	T* GetEntity();

	template <typename T>
	std::vector<T*> GetAllEntity();

};

template<typename T>
inline T* Scene::NewEntity()
{	
	T* NewEntity = new T();
	EntityStock.push_back(NewEntity);
	return NewEntity;
}

template<typename T>
inline T* Scene::GetEntity()
{
	for (Entity* e: EntityStock)
	{
		if (T* search = dynamic_cast<T*>(e))
			return search;
	}
	return nullptr;
}

template<typename T>
inline std::vector<T*> Scene::GetAllEntity()
{
	std::vector<T*> StockTemp;
	for (Entity* e : EntityStock)
	{
		if (T* search = dynamic_cast<T*>(e))
			StockTemp.push_back(search);
	}
	if (StockTemp.empty())
		return nullptr;

	return StockTemp;
}
