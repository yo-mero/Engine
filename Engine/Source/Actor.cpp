#include "Actor.h"
#include "MeshComponent.h"
#include "Device.h"
#include "Transform.h"

Actor::Actor(Device device)
{
	std::shared_ptr<Transform> transform = std::make_shared<Transform>();
	addComponent(transform);
	std::shared_ptr<MeshComponent> Mesh = std::make_shared<MeshComponent>();
	addComponent(Mesh);

	m_ModelBuffer.init(device, sizeof(CBChangesEveryFrame));
	m_sampler.init(device);
}

void Actor::update(float deltaTime, DeviceContext deviceContext)
{
	getComponent<Transform>()->update(deltaTime);

	model.mWorld = XMMatrixTranspose(getComponent<Transform>()->matrix);
	model.vMeshColor = XMFLOAT4(0.7f, 0.7f, 0.7f, 1.0f);
	m_ModelBuffer.update(deviceContext, 0, nullptr, &model, 0, 0);
}


void Actor::render(DeviceContext deviceContext)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_vertexBuffers[i].render(deviceContext, 0, 1);
		m_indexBuffers[i].render(deviceContext, DXGI_FORMAT_R32_UINT);
		if (m_textures.size() - 1)
		{
			if (i <= m_textures.size() - 1)
			{
				m_textures[i].render(deviceContext, 0, 1);
			}
			else
			{
				//m_default.render(deviceContext, 0, 1);
			}

		}
		m_sampler.render(deviceContext, 0, 1);
		m_ModelBuffer.renderModel(deviceContext, 2, 1);

		deviceContext.m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		deviceContext.m_deviceContext->DrawIndexed(m_meshes[i].m_numIndex, 0, 0); //referencia para los indices
	}
}

void Actor::destroy()
{
	for (auto& vertexBuffer : m_vertexBuffers)
	{
		vertexBuffer.destroy();
	}
	for (auto& indexBuffer : m_indexBuffers)
	{
		indexBuffer.destroy();
	}
	for (auto& tex : m_textures)
	{
		tex.destroy();
	}
	m_ModelBuffer.destroy();
	m_sampler.destroy();
}
void Actor::SetMesh(Device device, std::vector<MeshComponent> meshes)
{
	m_meshes = meshes;

	for (auto& mesh : m_meshes)
	{
		Buffer vertexBuffer;
		vertexBuffer.init(device, mesh, D3D11_BIND_VERTEX_BUFFER);
		m_vertexBuffers.push_back(vertexBuffer);


		Buffer indexBuffer;
		indexBuffer.init(device, mesh, D3D11_BIND_INDEX_BUFFER);
		m_indexBuffers.push_back(indexBuffer);
	}
}

void Actor::SetTextures(std::vector<Texture> textures)
{
	m_textures = textures;
}


