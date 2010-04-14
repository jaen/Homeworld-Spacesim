/*
    RETURN CONVENTION:
        return value > 0 means successful execution;
        return value =< 0 means error and is the error code;
        in case of returning pointers NULL is error value;

*/

//--- includes

    #include "hashArrayClass.h"

//--- definitions

    GLuint harrayBasicHash(GLchar *key, GLuint len) {
        GLchar *p = key;
        GLuint h = 0;
        GLint i;

        for (i = 0; i < len; i++) {
            h += p[i];
            h += (h << 10);
            h ^= (h >> 6);
        }

        h += (h << 3);
        h ^= (h >> 11);
        h += (h << 15);

        return h;
    }

    GLvoid *harrayFind(_HASHARRAY *inArray, GLchar *key) {
        if (inArray == NULL)
            return NULL;

        GLuint len = strlen(key);
        GLuint id = (*inArray->hashFunc)(key, len) % inArray->size;
        const _HASHNODE *const node = &(inArray->array[id]);

        if (node->next == NULL || !strcmp(node->key, key))
            return node->data;

        const _HASHNODE *tmp = node->next;

        while (strcmp(tmp->key,key) && (tmp = tmp->next)); //genius while!
        if(tmp != NULL)
            return tmp->data;
        return NULL;
    }

    GLint harrayInsert(_HASHARRAY *toArray, GLchar *key, GLvoid *data) {
        if (toArray == NULL)
            return -1;

        GLuint len = strlen(key);
        GLuint id = (*toArray->hashFunc)(key, len) % toArray->size;
        _HASHNODE *const node = &(toArray->array[id]);


        if (node->data == NULL) {
            if (!(node->key = malloc(len * sizeof(GLchar))))
                return -2;
            strcpy(node->key, key);
            node->data = data;
            return 1;
        }

        if (/*!strcmp(node->key,key) &&*/ node->next == NULL) { //somehow allows duplicates for now
            if (!(node->next = malloc(sizeof(_HASHNODE))))
                return -3;
            if (!(node->next->key = malloc(len * sizeof(GLchar))))
                return -4;
            strcpy(node->next->key, key);
            node->next->data = data;
            node->next->next = NULL;
            return 1;
        } //else
          //  return -3; //wtf? duplicate key!

        _HASHNODE *tmp = node->next;
        if (!(node->next = malloc(sizeof(_HASHNODE)))) {
            node->next = tmp;
            return -5;
        }
        if (!(node->next->key = malloc(len * sizeof(GLchar))))
            return -6;
        strcpy(node->next->key, key);
        node->next->data = data;
        node->next->next = tmp;
        return 1;
    }

    _HASHARRAY *harrayNew(GLuint size, GLuint (*hashFunc)(GLchar *, GLuint)) {
        _HASHARRAY *newArray;

        if (size < 1)
            return NULL;

        if (!(newArray = malloc(sizeof(_HASHARRAY))))
            return NULL;
        if (!(newArray->array = malloc(size * sizeof(_HASHNODE)))) {
            free(newArray);
            return NULL;
        }
        memset(newArray->array,0,size * sizeof(_HASHNODE));
        if (hashFunc == 0 || *hashFunc == 0)
            newArray->hashFunc = harrayBasicHash;
        else
            newArray->hashFunc = hashFunc;
        newArray->size = size;
        return newArray;
    }

    //free the hash arrray
    GLvoid harrayFree(_HASHARRAY *what) {
        if (what != NULL) {
            if (what->array != NULL){
                for(int i = 0; i < what->size; i++) {
                    _HASHNODE *tmp = what->array[i].next, *tmp2;
                    while (tmp != NULL) {
                      tmp2 = tmp;
                      tmp = tmp->next;
                      free(tmp2->key);
                      free(tmp2);
                    }
                    what->array[i].next = NULL;
                    if (what->array[i].key != NULL)
                        free(what->array[i].key);
                }
                free(what->array);
            }
            free(what);
            what = NULL;
        }

        return;
    }
