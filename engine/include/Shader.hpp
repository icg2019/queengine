#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Shader {
    private:
        unsigned int program_id;
        unordered_map<string, unsigned int> locations;

        unsigned int location(const string & name);

    public:
        Shader(const string & vertex_file, const string & fragment_file);

        void use();

        void set(const string & name, bool value);
        void set(const string & name, int value);
        void set(const string & name, unsigned int value);
        void set(const string & name, float v1);
        void set(const string & name, float v1, float v2);
        void set(const string & name, float v1, float v2, float v3);
        void set(const string & name, float v1, float v2, float v3, float v4);
        void set(const string & name, const glm::mat4 & value);

        void setTime(const string & name, function<float()> time, float frequency=1.0f);

};

#endif
