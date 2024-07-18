#pragma once
#include"PreRequisites.h"

class Device;
class DeviceContext;

class
	Texture {
public:
	Texture() = default;
	~Texture() = default;

	HRESULT init(Device device, std::string textureName, ExtensionType extensionType);

	void
		init(Device device,
			unsigned int width,
			unsigned int height,
			DXGI_FORMAT format,
			unsigned int BindFlags);
	/// <summary>
	/// Brief:This method is change of updating the logic of the texture
	/// </summary>
	void
	update();

	void
		render(DeviceContext & deviceContext, unsigned int StartSlot, 
			unsigned int NumViews);
	///Brief :This method is in charge of releasing the resources stored in the class's memory

	void
		destroy();
public:
	ID3D11Texture2D* m_texture = nullptr;
	//This variable in in charge on handle a atexture resource as data 
	ID3D11ShaderResourceView* m_textureFromImg;
	



};
