#ifndef TEXTURE_H
#define TEXTURE_H
#include <glad/glad.h>
#include <string>


class TextureLoader
{
public:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char * m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
	int wrapping, filtering;
public:
	TextureLoader(const std::string& path, int wrapping = 0, int filtering = 0);

	void Bind(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }


};
#endif
