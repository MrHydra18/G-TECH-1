#pragma once
#include "Vector2D.h"
#include "AssetsManager.h"



class Entity {

protected:

	SDL_Texture* texture = nullptr;

public:

	std::string tag;
	std::string layer;
	SDL_Point rotationCenter = { 16, 16 };
	SDL_Rect m_rect = { 0, 0, 32, 32 };
	Vector2D direction;
	float rotation = 0;
	bool markedForDeletion = false;

	Entity(std::string t) : tag(t) {}

	//Getteur
	std::string getTag() const { return tag; }
	std::string getLayer()const { return layer; }
	Vector2D getPosition() const { return Vector2D((float)m_rect.x, (float)m_rect.y); }


	//Setteur
	void setLayer(std::string l) { layer = l; }
	void setVelocity(Vector2D vel) { direction = vel; }
	void setRotationCenter(SDL_Point point) { rotationCenter = point; }
	void setPosition(float x, float y, float anchorX = 0.5f, float anchorY = 0.5f) {
		m_rect.x = (int)(x - m_rect.w * anchorX);
		m_rect.y = (int)(y - m_rect.h * anchorY);
	}

	bool isOutOfBounds(int windowWidth, int windowHeight) const {
		return (m_rect.x + m_rect.w < 0 ||           
			m_rect.x > windowWidth * 2 ||             
			m_rect.y + m_rect.h < 0 ||                
			m_rect.y > windowHeight * 2);           
	}

	bool collision(SDL_Rect other) const {
		return (other.x < m_rect.x + m_rect.w &&
			other.x + other.w > m_rect.x &&
			other.y < m_rect.y + m_rect.h &&
			other.y + other.h > m_rect.y);
	}

	static bool checkCollision(SDL_Rect a, SDL_Rect b) {
		return (a.x < b.x + b.w &&
			a.x + a.w > b.x &&
			a.y < b.y + b.h &&
			a.y + a.h > b.y);
	}

	virtual void replaceEntityAfterWindowResize(int oldWidth, int oldHeight, int newWidth, int newHeight) {

		float ratioX = (float)newWidth / oldWidth;
		float ratioY = (float)newHeight / oldHeight;

		// Scaler la position
		m_rect.x = (int)(m_rect.x * ratioX);
		m_rect.y = (int)(m_rect.y * ratioY);

		// Scaler la taille (sera recalculée dans update() pour Enemy/Vaisseau)
		m_rect.w = (int)(m_rect.w * ratioX);
		m_rect.h = (int)(m_rect.h * ratioY);

		// NE PAS toucher à direction - c'est juste une direction normalisée (-1, 0, 1)
	}

	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void update(float deltaTime) = 0;


};