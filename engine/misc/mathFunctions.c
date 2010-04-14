/*
    RETURN CONVENTION:
        return value > 0 means successful execution;
        return value =< 0 means error and is the error code;
        in case of returning pointers NULL is error value;

*/

//--- includes

    #include "mathFunctions.h"

//--- some variables

     GLfloat idMat[16] = {1,0,0,0,
                          0,1,0,0,
                          0,0,1,0,
                          0,0,0,1};

    _VEC4 tmpVec;
    _MAT4 tmpMat, tmpMat2;

//--- definitions

        _CPUINFO mathGetProcessorInfo() {
            _CPUINFO info;
            GLchar  *vendorstr = info.vendor;
            GLint n = 1, *ptrn = &n;

            memset(&info, 0, sizeof(info));

            /*asm (
                "MOV EAX, 0 ;get vendor str\n\t"
                "CPUID\n\t"
            );*/


            return info;
        }

        inline int min(GLint a, GLint b) {
            return (a<b ? a : b);
        }

        inline GLint max(GLint a, GLint b) {
            return (a>b ? a : b);
        }

    //--- matrix functions

        GLvoid mat4Print(_MAT4 mat) {
           printf("|%.3f %.3f %.3f %.3f|\n",   mat.f[ 0], mat.f[ 4], mat.f[ 8], mat.f[12]);
           printf("|%.3f %.3f %.3f %.3f|\n",   mat.f[ 1], mat.f[ 5], mat.f[ 9], mat.f[13]);
           printf("|%.3f %.3f %.3f %.3f|\n",   mat.f[ 2], mat.f[ 6], mat.f[10], mat.f[14]);
           printf("|%.3f %.3f %.3f %.3f|\n\n", mat.f[ 3], mat.f[ 7], mat.f[11], mat.f[15]);
        }

        inline GLvoid mat4Identity(_MAT4 mat) {
            memcpy(mat.f, idMat, sizeof(_MAT4));
        }

        inline _MAT4 mat4Set(GLfloat a1, GLfloat a2, GLfloat a3, GLfloat a4,GLfloat b1, GLfloat b2, GLfloat b3, GLfloat b4, GLfloat c1, GLfloat c2, GLfloat c3, GLfloat c4, GLfloat d1, GLfloat d2, GLfloat d3, GLfloat d4) {
            /*tmpMat.sse[0] = _mm_setr_ps(a1, a2, a3, a4);
            tmpMat.sse[1] = _mm_setr_ps(b1, b2, b3, b4);
            tmpMat.sse[2] = _mm_setr_ps(c1, c2, c3, c4);
            tmpMat.sse[3] = _mm_setr_ps(d1, d2, d3, d4);*/
            tmpMat.sse[0] = _mm_setr_ps(a1, b1, c1, d1);
            tmpMat.sse[1] = _mm_setr_ps(a2, b2, c2, d2);
            tmpMat.sse[2] = _mm_setr_ps(a3, b3, c3, d3);
            tmpMat.sse[3] = _mm_setr_ps(a4, b4, c4, d4);
            return tmpMat;
        }

        inline GLvoid mat4Cpy(_MAT4 from, _MAT4 to) {
            memcpy(to.f, from.f, sizeof(_MAT4));
        }

        inline _MAT4 mat4Add(_MAT4 a, _MAT4 b) {
            tmpMat.sse[0] = _mm_add_ps(a.sse[0], b.sse[0]);
            tmpMat.sse[1] = _mm_add_ps(a.sse[1], b.sse[1]);
            tmpMat.sse[2] = _mm_add_ps(a.sse[2], b.sse[2]);
            tmpMat.sse[3] = _mm_add_ps(a.sse[3], b.sse[3]);
            return tmpMat;
        }

        inline _MAT4 mat4Trans(_MAT4 a) {
            tmpMat.sse[0] = _mm_setr_ps(a.f[ 0], a.f[ 4], a.f[ 8], a.f[12]);
            tmpMat.sse[1] = _mm_setr_ps(a.f[ 1], a.f[ 5], a.f[ 9], a.f[13]);
            tmpMat.sse[2] = _mm_setr_ps(a.f[ 2], a.f[ 6], a.f[10], a.f[14]);
            tmpMat.sse[3] = _mm_setr_ps(a.f[ 3], a.f[ 7], a.f[11], a.f[15]);
            return tmpMat;
        }

        inline _MAT4 mat4Mul(_MAT4 a, _MAT4 b) { //CRUDE! REALLY CRUDE! NEEDS SOME SHUFFPS LOVE
            tmpMat2.sse[0] = _mm_mul_ps(a.sse[0], b.sse[0]);
            tmpMat2.sse[1] = _mm_mul_ps(a.sse[0], b.sse[1]);
            tmpMat2.sse[2] = _mm_mul_ps(a.sse[0], b.sse[2]);
            tmpMat2.sse[3] = _mm_mul_ps(a.sse[0], b.sse[3]);
            tmpMat.f[ 0] = tmpMat2.f[ 0] + tmpMat2.f[ 1] + tmpMat2.f[ 2] + tmpMat2.f[ 3];
            tmpMat.f[ 1] = tmpMat2.f[ 4] + tmpMat2.f[ 5] + tmpMat2.f[ 6] + tmpMat2.f [7];
            tmpMat.f[ 2] = tmpMat2.f[ 8] + tmpMat2.f[ 9] + tmpMat2.f[10] + tmpMat2.f[11];
            tmpMat.f[ 3] = tmpMat2.f[12] + tmpMat2.f[13] + tmpMat2.f[14] + tmpMat2.f[15];
            tmpMat2.sse[0] = _mm_mul_ps(a.sse[1], b.sse[0]);
            tmpMat2.sse[1] = _mm_mul_ps(a.sse[1], b.sse[1]);
            tmpMat2.sse[2] = _mm_mul_ps(a.sse[1], b.sse[2]);
            tmpMat2.sse[3] = _mm_mul_ps(a.sse[1], b.sse[3]);
            tmpMat.f[ 4] = tmpMat2.f[ 0] + tmpMat2.f[ 1] + tmpMat2.f[ 2] + tmpMat2.f[ 3];
            tmpMat.f[ 5] = tmpMat2.f[ 4] + tmpMat2.f[ 5] + tmpMat2.f[ 6] + tmpMat2.f [7];
            tmpMat.f[ 6] = tmpMat2.f[ 8] + tmpMat2.f[ 9] + tmpMat2.f[10] + tmpMat2.f[11];
            tmpMat.f[ 7] = tmpMat2.f[12] + tmpMat2.f[13] + tmpMat2.f[14] + tmpMat2.f[15];
            tmpMat2.sse[0] = _mm_mul_ps(a.sse[2], b.sse[0]);
            tmpMat2.sse[1] = _mm_mul_ps(a.sse[2], b.sse[1]);
            tmpMat2.sse[2] = _mm_mul_ps(a.sse[2], b.sse[2]);
            tmpMat2.sse[3] = _mm_mul_ps(a.sse[2], b.sse[3]);
            tmpMat.f[ 8] = tmpMat2.f[ 0] + tmpMat2.f[ 1] + tmpMat2.f[ 2] + tmpMat2.f[ 3];
            tmpMat.f[ 9] = tmpMat2.f[ 4] + tmpMat2.f[ 5] + tmpMat2.f[ 6] + tmpMat2.f [7];
            tmpMat.f[10] = tmpMat2.f[ 8] + tmpMat2.f[ 9] + tmpMat2.f[10] + tmpMat2.f[11];
            tmpMat.f[11] = tmpMat2.f[12] + tmpMat2.f[13] + tmpMat2.f[14] + tmpMat2.f[15];
            tmpMat2.sse[0] = _mm_mul_ps(a.sse[3], b.sse[0]);
            tmpMat2.sse[1] = _mm_mul_ps(a.sse[3], b.sse[1]);
            tmpMat2.sse[2] = _mm_mul_ps(a.sse[3], b.sse[2]);
            tmpMat2.sse[3] = _mm_mul_ps(a.sse[3], b.sse[3]);
            tmpMat.f[12] = tmpMat2.f[ 0] + tmpMat2.f[ 1] + tmpMat2.f[ 2] + tmpMat2.f[ 3];
            tmpMat.f[13] = tmpMat2.f[ 4] + tmpMat2.f[ 5] + tmpMat2.f[ 6] + tmpMat2.f [7];
            tmpMat.f[14] = tmpMat2.f[ 8] + tmpMat2.f[ 9] + tmpMat2.f[10] + tmpMat2.f[11];
            tmpMat.f[15] = tmpMat2.f[12] + tmpMat2.f[13] + tmpMat2.f[14] + tmpMat2.f[15];
            return mat4Trans(tmpMat);
        }

    //-- vector functions

        GLvoid vec4Print(_VEC4 vec) {
           printf("<%.3f, %.3f, %.3f, %.3f>\n", vec.f[0], vec.f[1], vec.f[2], vec.f[3]);
        }

        /*GLvoid vectorPrintDebug3(_VEC3 aVector) {
           printf("<%.3f, %.3f, %.3f>\n", aVector[0], aVector[1], aVector[2]);
        }*/

        inline _VEC4 vec4Set(GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
            return (_VEC4) _mm_setr_ps(x, y, z, w); //could be changed to load if we had different indexes
        }

        inline _VEC4 vec4SetAll(GLfloat a) {
            return (_VEC4) _mm_set1_ps(a);
        }

        inline _VEC4 vec4Add(_VEC4 a, _VEC4 b) {
            return (_VEC4) _mm_add_ps(a.sse, b.sse);
            /*tmpVec = (_VEC4)_mm_add_ps(a.sse, b.sse);
            tmpVec.f[3] = 1.0f;
            return tmpVec;*/
        }

        inline _VEC4 vec4Subs(_VEC4 a, _VEC4 b) {
            return (_VEC4) _mm_sub_ps(a.sse, b.sse);
        }

        inline _VEC4 vec4Mul(_VEC4 a, _VEC4 b) {
            return (_VEC4) _mm_mul_ps(a.sse, b.sse);
        }

        inline _VEC4 vec4MulConst(_VEC4 a, GLfloat b) {
            tmpVec = vec4SetAll(b);
            return (_VEC4) _mm_mul_ps(a.sse, tmpVec.sse);
        }

        //to be shuffps'd (prolly)
        inline GLfloat vec4Dot(_VEC4 a, _VEC4 b) {
            tmpVec = vec4Mul(a, b);
            return tmpVec.f[0] + tmpVec.f[1] + tmpVec.f[2]/* + tmpVec.f[3]*/;
        }

        //to be shuffps'd (prolly)
        inline _VEC4 vec4Cross(_VEC4 a, _VEC4 b) {
            return vec4Set(a.f[1] * b.f[2] - a.f[2] * b.f[1],
                            a.f[2] * b.f[0] - a.f[0] * b.f[2],
                            a.f[0] * b.f[1] - a.f[1] * b.f[0],
                            0.f);
        }

        inline GLfloat vec4Len(_VEC4 a) {
            tmpVec = vec4SetAll(vec4Dot(a, a));
            return ((_VEC4) _mm_sqrt_ps(tmpVec.sse)).f[0];
        }

        inline _VEC4 vec4Norm(_VEC4 a) { //can be  beter with rcp_sqrt, but later
            GLfloat len;
            if (((len = vec4Len(a)) > -0.0000001) && (len < 0.0000001)) //it's kinda zero-ish
                return (_VEC4) _mm_set1_ps(0);
            tmpVec.f[0] = 1 / len;
            return vec4MulConst(a, tmpVec.f[0]);
        }

