class Model  
{  
public:  
Model(const std::string& path) 
{  
	loadModel(path);  
}  

void Draw(Shader& shader)  
{  
	for (unsigned int i = 0; i < meshes.size(); i++)  
		meshes[i].Draw(shader);  
}  

private:  
std::vector<Texture> texturesLoaded;  
std::vector<Mesh> meshes;  
std::string directory;  

void loadModel(std::string const& path)  
{  
	Assimp::Importer importer;  
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);  

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)  
	{  
		std::cout << "ERROR : ASSIMP:: " << importer.GetErrorString() << "\n";  
		return;  
	}  
	directory = path.substr(0, path.find_last_of('/'));  

	processNode(scene->mRootNode, scene);  
}  

void processNode(aiNode* node, const aiScene* scene)  
{  
	for (unsigned int i = 0; i < node->mNumMeshes; i++)  
	{  
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];  
		meshes.push_back(processMesh(mesh, scene));  
	}  

	for (unsigned int i = 0; i < node->mNumChildren; i++)  
	{  
		processNode(node->mChildren[i], scene);  
	}  
}  

Mesh processMesh(aiMesh* mesh, const aiScene* scene)  
{  
	std::vector<Vertex> vertices;  
	std::vector<unsigned int> indices;  
	std::vector<Texture> textures;  

	//vertex  
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)  
	{  
		//position  
		Vertex vertex;  
		vertex.pos = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);  

		//normals  
		if (mesh->HasNormals())  
		{  
			vertex.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);  
		}  

		//texture coords  
		if (mesh->mTextureCoords[0])  
		{  
			vertex.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);  
		}  
		else  
		{  
			vertex.texCoord = glm::vec2(0.0f, 0.0f);  
		}  
		vertices.push_back(vertex);  
	}  

	//indices  
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)  
	{  
		aiFace face = mesh->mFaces[i];  
		for (unsigned int j = 0; j < face.mNumIndices; j++)  
		{  
			indices.push_back(face.mIndices[j]);  
		} 
	}  

	//materials  
	aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];  
		//diffuse map  
	std::vector<Texture> diffuseMaps = loadMaterialTextures(mat, aiTextureType_DIFFUSE, "texture_diffuse");  
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());  

		//specular map  
	std::vector<Texture> specularMaps = loadMaterialTextures(mat, aiTextureType_SPECULAR, "texture_specular");  
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());  

	return Mesh(vertices, indices, textures);  
}  

unsigned int TextureFromFile(const char* path, const std::string& directory)  
{  
	std::string filename = std::string(path);  
	filename = directory + '/' + filename;  

	unsigned int textureID;  
	glGenTextures(1, &textureID);  

	int width, height, nrComponents;  
	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);  
	if (data)  
	{  
		GLenum format;  
		if (nrComponents == 1)  
			format = GL_RED;  
		else if (nrComponents == 3)  
			format = GL_RGB;  
		else if (nrComponents == 4)  
			format = GL_RGBA;  

		glBindTexture(GL_TEXTURE_2D, textureID);  
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);  
		glGenerateMipmap(GL_TEXTURE_2D);  

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  

		stbi_image_free(data);  
	}  
	else  
	{  
		std::cout << "Texture failed to load at path: " << path << "\n";  
		stbi_image_free(data);  
	}  

	return textureID;  
}  

std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)  
{  
	std::vector<Texture> textures;  

	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)  
	{  
		aiString str;  
		mat->GetTexture(type, i, &str);  
		bool skip = false;  

		for (unsigned int j = 0; j < texturesLoaded.size(); j++)  
		{  
			if (std::strcmp(texturesLoaded[j].path.data(),str.C_Str()) == 0)  
			{  
				textures.push_back(texturesLoaded[j]);  
				skip = true;  
				break;  
			}  
		}  
		if(!skip)  
		{  
			Texture texture;  
			texture.ID = TextureFromFile(str.C_Str(), this->directory);  
			texture.type = typeName;  
			texture.path = str.C_Str();  
			textures.push_back(texture);  
			texturesLoaded.push_back(texture);  
		}  

	}  

	return textures;  
}  
};
