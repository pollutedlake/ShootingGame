#pragma once

class SceneManager;

class Scene
{
	friend SceneManager;
private:

	virtual void init() = 0;
	virtual void release() = 0;
	virtual void update(HDC hdc) = 0;
	virtual void exit() = 0;

protected:


public:

	Scene();
	virtual ~Scene();
};

