#ifndef GENERICS_ENABLED
    #error Can't use generic classes without the Generic.h
#endif
#ifndef LINKEDTABLE_H_INCLUDED
#define LINKEDTABLE_H_INCLUDED

//--- includes

    #include <stdio.h>
    #include <string.h>
    #include <malloc.h>
    #ifdef HAS_OGL
        #include <GL\glew.h>
        #include <GL\gl.h>
    #endif
    #ifndef HAS_OGL
        #ifndef OGL_TYPEDEFS
            #define OGL_TYPEDEFS
            typedef int           GLint;
            typedef unsigned int  GLuint;
            typedef unsigned char GLubyte;
            typedef void          GLvoid;
        #endif
    #endif

//--- linked table implementation

    #define _ltablePrototype(type) \
        enum growthType {EXPLICIT, IMPLICIT}; \
        \
        typedef union { \
            type   cell; \
            GLvoid *next; \
        } _LTABLE_CELL_##type; \
        \
        typedef struct { \
            _LTABLE_CELL_##type *tables; \
            GLuint               step, size, maxindex; \
            GLubyte              growthStyle; \
        } _LINKED_TABLE_##type;\
        \
        _LINKED_TABLE_##type *ltableNew_##type(GLuint step, GLubyte growthStyle); \
        GLvoid ltableFree_##type(_LINKED_TABLE_##type *what); \
        GLvoid ltableSet_##type(_LINKED_TABLE_##type *inTable, GLuint index, type value); \
        type *ltableGet_##type(_LINKED_TABLE_##type *fromTable, GLuint index); \
        GLint  ltableGrow_##type(_LINKED_TABLE_##type *table, GLuint maxindex); \
        \
        _ltableNew(type) \
        _ltableFree(type) \
        _ltableSet(type) \
        _ltableGet(type) \
        _ltableGrow(type)

        //mallocs a new linked table; invoked by ltableNew macro
        #define _ltableNew(type) \
            _LINKED_TABLE_##type *ltableNew_##type(GLuint step, GLubyte growthStyle) { \
                _LINKED_TABLE_##type *newTable; \
                \
                if(!(newTable = malloc(sizeof(*newTable)))) \
                    return NULL; \
                \
                newTable->tables = malloc((1 + step) * sizeof(_LTABLE_CELL_##type)); \
                memset(newTable->tables, 0, (1 + step) * sizeof(_LTABLE_CELL_##type)); \
                newTable->size = 1; \
                newTable->step = step; \
                newTable->maxindex = step; \
                newTable->growthStyle = growthStyle; \
                return newTable; \
            }

        //frees the table
        #define _ltableFree(type) \
            GLvoid ltableFree_##type(_LINKED_TABLE_##type *what) { \
                _LTABLE_CELL_##type *ptr = what->tables, *tmp = NULL; \
                \
                for(int i = 0; i < what->size; i++) { \
                    tmp = ptr; \
                    ptr = ptr[what->step + 1].next; \
                    free(tmp); \
                } \
                free(what); \
            }

        //table[index] = rvalue;
        #define _ltableSet(type) \
            GLvoid ltableSet_##type(_LINKED_TABLE_##type *inTable, GLuint index, type value) { \
                if (inTable == NULL) \
                    return; \
                \
                if (inTable->growthStyle == IMPLICIT) \
                    if (index > inTable->maxindex) \
                        ltableGrow_##type(inTable, index); \
                \
                if (index < inTable->step) \
                    inTable->tables[index].cell = value; \
                else { \
                    GLuint tableno = index/inTable->step; \
                    index %= inTable->step; \
                    _LTABLE_CELL_##type *ptr = inTable->tables; \
                    \
                    for(int i = 0; i < tableno; i++) \
                        ptr = ptr[inTable->step + 1].next; \
                    \
                    ptr[index].cell = value; \
                } \
            }

        //lvalue = table[index]; returns pointer to the value as to avoid copying
        #define _ltableGet(type) \
            type *ltableGet_##type(_LINKED_TABLE_##type *fromTable, GLuint index) { \
                if (fromTable == NULL) \
                    return NULL; \
                \
                if (index < fromTable->step) \
                    return &fromTable->tables[index].cell; \
                else { \
                    GLuint tableno = index/fromTable->step; \
                    index %= fromTable->step; \
                    _LTABLE_CELL_##type *ptr = fromTable->tables; \
                    \
                    for(int i = 0; i < tableno; i++) \
                        ptr = ptr[fromTable->step + 1].next; \
                    \
                    return &ptr[index].cell; \
                } \
            }

        //grows table to accomodate at least maxindex
        #define _ltableGrow(type) \
            GLint  ltableGrow_##type(_LINKED_TABLE_##type *table, GLuint maxindex) { \
                if(table == NULL) \
                    return -1; \
                \
                GLuint              dsize;\
                _LTABLE_CELL_##type *ptr = table->tables, *tmp = NULL;\
                \
                if (maxindex < table->size*table->step || !((dsize = maxindex / table->step - table->size) > 0)) \
                    return -2; \
                \
                for(int i = 0; i < dsize; i++) { \
                    tmp = &ptr[table->step + 1]; \
                    if (!(tmp->next = malloc((1 + table->step) * sizeof(_LTABLE_CELL_##type)))) \
                        return -3; \
                    memset(tmp->next, 0, (1 + table->step) * sizeof(_LTABLE_CELL_##type)); \
                    ptr = tmp->next; \
                } \
                table->size += dsize; \
                table->maxindex = table->size * table->step; \
                return 1; \
            }

#endif // LINKEDTABLE_H_INCLUDED
