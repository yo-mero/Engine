#pragma once
# include "PreRequisites.h"

class Device
{
public:
	Device() = default;
	~Device() = default;

	void
		init();
	void
		update();
	void
		render();
	void
		destroy();
public:
	ID3D11Device* m_device = NULL;
};

