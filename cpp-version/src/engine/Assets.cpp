#include "Assets.h"
#include "Log.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>

// Instantiate static variables
std::map<std::string, Texture2D> Assets::textures;
std::map<std::string, Shader> Assets::shaders;

Shader Assets::loadShader(const std::string &vShaderFile, const std::string &fShaderFile,
                                   const std::string &tcShaderFile, const std::string &teShaderFile,
                                   const std::string &gShaderFile, const std::string &name) {
    shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, tcShaderFile, teShaderFile, gShaderFile);
    return shaders[name];
}

Shader& Assets::getShader(const std::string &name) {
    return shaders[name];
}

Texture2D Assets::loadTexture(const std::string &file, const std::string &name) {
    textures[name] = loadTextureFromFile(file.c_str());
    return textures[name];
}

Texture2D& Assets::getTexture(const std::string &name) {
    return textures[name];
}

void Assets::clear() {
    // (Properly) delete all shaders
    for (auto iter : shaders)
        glDeleteProgram(iter.second.id);
    // (Properly) delete all textures
    for (auto iter : textures)
        glDeleteTextures(1, &iter.second.id);
}

Shader Assets::loadShaderFromFile(const std::string &vShaderFile, const std::string &fShaderFile,
                                           const std::string &tcShaderFile, const std::string &teShaderFile,
                                           const std::string &gShaderFile) {
    // 1. Retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string tcCode;
    std::string teCode;
    std::string geometryCode;
    try {
        // Open files
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // Convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // If tess control shader path is present, also load a tess control shader
        if (tcShaderFile != "") {
            std::ifstream tessControlShaderFile(tcShaderFile);
            std::stringstream tcShaderStream;
            tcShaderStream << tessControlShaderFile.rdbuf();
            tessControlShaderFile.close();
            tcCode = tcShaderStream.str();
        }
        // If tess evaluation shader path is present, also load a tess evaluation shader
        if (teShaderFile != "") {
            std::ifstream tessEvalShaderFile(teShaderFile);
            std::stringstream teShaderStream;
            teShaderStream << tessEvalShaderFile.rdbuf();
            tessEvalShaderFile.close();
            teCode = teShaderStream.str();
        }
        // If geometry shader path is present, also load a geometry shader
        if (gShaderFile != "") {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::exception e) {
        std::ostringstream loadError;
        std::string geomShaderFile = "";
        if (gShaderFile != "")
            geomShaderFile = gShaderFile;

        loadError << "ERROR::SHADER: Failed to read shader files " << vShaderFile << " " << fShaderFile << " "
                  << geomShaderFile << "\n"
                  << "\n -- --------------------------------------------------- -- "
                  << std::endl;
        LOG(Error) << loadError.str();
    }
    const GLchar *vShaderCode = vertexCode.c_str();
    const GLchar *fShaderCode = fragmentCode.c_str();
    const GLchar *tcShaderCode = tcCode.c_str();
    const GLchar *teShaderCode = teCode.c_str();
    const GLchar *gShaderCode = geometryCode.c_str();
    // 2. Now create shader object from source code
    Shader shader;
    shader.compile(vShaderCode, fShaderCode,
                   tcShaderFile != "" ? tcShaderCode : nullptr,
                   teShaderFile != "" ? teShaderCode : nullptr,
                   gShaderFile != "" ? gShaderCode : nullptr);
    return shader;
}

Texture2D Assets::loadTextureFromFile(const std::string &file) {
    // Create Texture object
    Texture2D texture;
    texture.load(file);

    // Now generate texture
    texture.generate();
    // And finally return texture
    return texture;
}