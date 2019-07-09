#ifndef __SHADER_HPP__
#define __SHADER_HPP__

#include <string>
#include <unordered_map>
#include <functional>


class Shader {
public:
    Shader(const std::string & vertex_file, const std::string & fragment_file);

    void use();

    void set(const std::string & name, bool value);
    void set(const std::string & name, int value);
    void set(const std::string & name, unsigned int value);
    void set(const std::string & name, float v1);
    void set(const std::string & name, float v1, float v2);
    void set(const std::string & name, float v1, float v2, float v3);
    void set(const std::string & name, float v1, float v2, float v3, float v4);


    void setTime(const std::string & name, std::function<float()> time, float frequency=1.0f);

private:
    unsigned int program_id;
    std::unordered_map<std::string, unsigned int> locations;

    unsigned int location(const std::string & name);
};

#endif
