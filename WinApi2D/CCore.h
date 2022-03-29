#pragma once

class CTexture;

class CCore
{
	SINGLETON(CCore);

private:
	bool		M_bDebug;

public:
	void update();
	void render();
	void init();

	bool		GetDebugMode() { return M_bDebug; }

};

