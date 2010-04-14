#ifndef HASHARRAYCLASS_H_INCLUDED
#define HASHARRAYCLASS_H_INCLUDED

//--- includes

    #include <malloc.h>
    #include <string.h>
    #include <GL\glew.h>
    #include <GL\gl.h>

//--- typedefs

    typedef struct hnode {
        GLchar *key;
        GLvoid *data;
        struct hnode  *next;
    } _HASHNODE;

    /*typedef struct {
        GLvoid *data;
        _HASHSUBNODE  *next;
    } _HASHNODE; */

    typedef struct {
        _HASHNODE *array;
        GLuint size;
        GLuint (*hashFunc)(GLchar*, GLuint);
    } _HASHARRAY;

//--- declarations

    //just a basic hash
    GLuint harrayBasicHash(GLchar *key, GLuint len);

    //returns the contents of the data field if found, otherwise NULL
    GLvoid *harrayFind(_HASHARRAY *inArray, GLchar *key);

    //inserts into hash array
    GLint harrayInsert(_HASHARRAY *toArray, GLchar *key, GLvoid *data);

    //mallocs a new hash array
    _HASHARRAY *harrayNew(GLuint size, GLuint (*hashFunc)(GLchar *, GLuint));

    //free the hash arrray
    GLvoid harrayFree(_HASHARRAY *what);

#endif // HASHARRAYCLASS_H_INCLUDED
