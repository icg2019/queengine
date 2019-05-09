#include <glad/glad.h>
#include <string>


class TextureLoader
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	TextureLoader(const std::string& path);
	~TextureLoader();

	void Bind(unsigned int slot = 0) const;
	void Ubind() const;

	inline int GetWidth() const { return m_Width; }
	inline int GetHeight() const { return m_Height; }


};