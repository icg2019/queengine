#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <unordered_map>
#include <functional>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

class Shader {
    private:
        unordered_map<string, unsigned int> locations;

        unsigned int Location(const string & name);

    public:
        unsigned int program_id;
        int option_command; 


        Shader(const string & vertex_file, const string & fragment_file);

        void Use();
        bool active;

        void Set(const string & name, float v1);
        void Set(const string & name, float v1, float v2);
        void Set(const string & name, float v1, float v2, float v3);
        void Set(const string & name, float v1, float v2, float v3, float v4);
        void Set(const string & name, bool value);
        void Set(const string & name, int value);
        void Set(const string & name, int v1, int v2);
        void Set(const string & name, int v1, int v2, int v3);
        void Set(const string & name, int v1, int v2, int v3, int v4);
        void Set(const string & name, unsigned int value);
        void Set(const string & name, unsigned int v1, unsigned int v2);
        void Set(const string & name, unsigned int v1, unsigned int v2, unsigned int v3);
        void Set(const string & name, unsigned int v1, unsigned int v2, unsigned int v3, unsigned int v4);
        void Set(const string & name, int res, float *value);
        void Set(const string & name, int res, int * value);
        void Set(const string & name, int res, unsigned int * value);
        void Set(const string & name, const glm::mat4 & value);

        void SetTime(const string & name, std::function<float()> time, float frequency=1.0f);
};

#endif
