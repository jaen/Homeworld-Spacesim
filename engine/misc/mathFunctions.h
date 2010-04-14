#ifndef MATHFUNCTIONS_H_INCLUDED
#define MATHFUNCTIONS_H_INCLUDED

//--- includes

    #include "includes.h"
    #include <math.h>
    #include <xmmintrin.h>

//--- defines

    #ifdef __GNUC__
        #define ALIGNED_16	__attribute__ ((__aligned__ (16)))
    #else
        #define ALIGNED_16 	__declspec(align(16))
    #endif

    #define INITMATRIX(mat)

    #define INITVECTOR4(vec)

    #define INITVECTOR3(vec)

    #define INITVECTOR2(vec)

//--- typedfes

    typedef struct {
        GLint   hasSSE;
        GLint   hasSSE2;
        GLint   has3DNOW;
        GLint   hasMMX;
        GLchar  name[48]; //CPU name string
        GLint   hasEXT; //extended features available
        GLint   hasMMXEX; //
        GLint   has3DNOWEX;
        GLchar  vendor[13];
    } _CPUINFO;

    typedef union {
        ALIGNED_16 GLfloat f[16];
        __m128  sse[4];
    } _MAT4;
    //typedef GLfloat _MATRIX3[9];

    typedef union {
        ALIGNED_16 GLfloat f[4];
        __m128  sse;
    } _VEC4;
    //typedef GLfloat _VEC3[3];
    //typedef GLfloat _VEC2[2];

//--- declarations

    _CPUINFO mathGetProcessorInfo();

    #undef min
    extern GLint min(GLint a, GLint b);
    #undef max
    extern GLint max(GLint a, GLint b);

    GLvoid mat4Print(_MAT4 mat);
    extern GLvoid   mat4Identity(_MAT4 mat);
    extern _MAT4    mat4Set(GLfloat a1, GLfloat a2, GLfloat a3, GLfloat a4,
                            GLfloat b1, GLfloat b2, GLfloat b3, GLfloat b4,
                            GLfloat c1, GLfloat c2, GLfloat c3, GLfloat c4,
                            GLfloat d1, GLfloat d2, GLfloat d3, GLfloat d4);
    extern GLvoid   mat4Cpy(_MAT4 from, _MAT4 to);
    extern _MAT4    mat4Add(_MAT4 a, _MAT4 b);
    extern _MAT4    mat4Trans(_MAT4 a);
    extern _MAT4    mat4Mul(_MAT4 a, _MAT4 b);


    GLvoid vec4Print(_VEC4 vec);
    //GLvoid vec3PrintDebug(_VEC3 aVector);
    extern _VEC4    vec4Set(GLfloat x, GLfloat y, GLfloat z, GLfloat w); //creates vector [x, y, z, w]
    extern _VEC4    vec4SetAll(GLfloat a);
    extern _VEC4    vec4Add(_VEC4 a, _VEC4 b);
    extern _VEC4    vec4Subs(_VEC4 a, _VEC4 b);
    extern _VEC4    vec4Mul(_VEC4 a, _VEC4 b);
    extern _VEC4    vec4MulConst(_VEC4 a, GLfloat b);
    extern GLfloat  vec4Dot(_VEC4 a, _VEC4 b);
    extern _VEC4    vec4Cross(_VEC4 a, _VEC4 b);
    extern GLfloat  vec4Len(_VEC4 a);
    extern _VEC4    vec4Norm(_VEC4 a);
    /*_VEC4
    add
    sub
    mul
    mulconst
    dot
    len
    norm*/


#endif // MATHFUNCTIONS_H_INCLUDED
