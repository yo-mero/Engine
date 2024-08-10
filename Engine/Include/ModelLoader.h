#pragma once
#include "PreRequisites.h"
#include "fbxsdk.h"
#include "MeshComponent.h"
// Clase para cargar modelos 3D usando el SDK de FBX
class ModelLoader
{
public:
	ModelLoader();
	~ModelLoader();
	// Carga un modelo desde el archivo especificado
	bool LoadModel(const std::string& filePath);
	// Devuelve los vértices del modelo cargado
	const std::vector<SimpleVertex>& GetVertices() const { return vertices; }
	// Devuelve los índices del modelo cargado
	const std::vector<uint32_t>& GetIndices() const { return indices; }


	// Devuelve los nombres de los archivos de textura utilizados por el modelo
	std::vector<std::string>GetTextureFileName() const { return textureFileName; }

	// Procesa un nodo del modelo FBX
	void ProcessNode(FbxNode* node);
	// Procesa una malla del nodo FBX
	void ProcessMesh(FbxNode* node);

	// Procesa el material de una malla FBX
	void ProcessMaterial(FbxSurfaceMaterial* material);
private:
	FbxManager* lSdkManager; // Gestor del SDK de FBX
	FbxScene* lScene;		// Escena del modelo FBX
	std::vector<SimpleVertex> vertices;	 // Vértices del modelo
	std::vector<unsigned int> indices;	 // Índices del modelo
	std::vector<std::string> textureFileName;	// Nombres de archivos de textura del modelo
public:
	std::vector<MeshComponent> meshes;	// Mallas del modelo
};
