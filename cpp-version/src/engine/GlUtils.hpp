#ifndef GL_UTILS_H
#define GL_UTILS_H

// Check if extension is supported
int isExtensionSupported(const char* extname)
{
    GLint numExtensions;
    GLint i;

    glGetIntegerv(GL_NUM_EXTENSIONS, &numExtensions);

    for (i = 0; i < numExtensions; i++)
    {
        const GLubyte * e = glGetStringi(GL_EXTENSIONS, i);
        if (!strcmp((const char *)e, extname))
        {
            return 1;
        }
    }

    return 0;
}

// Query the adress of extensions fonctions
GL3WglProc getProcAddress(const char * funcname)
{
    return gl3wGetProcAddress(funcname);
}

#endif