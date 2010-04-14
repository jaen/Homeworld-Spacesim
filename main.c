    #include "engine\includes.h"
    #include <stdio.h>
    #include <stdlib.h>

    #include "engine\misc\mathFunctions.h"


    GLint main(GLint argc, GLchar *argv[]) {
        int a=2,b=4;
        printf("Hello world! %d\n", min(a++, b));
        printf("%d",a);
        return 0;
    }
