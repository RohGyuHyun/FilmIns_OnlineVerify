#include <stdio.h>

#include <time.h>


 

int main()

{

    FILE* version = NULL;

    fopen_s(&version, "VersionInfo.h", "r");

 

    if(version == NULL)

    {

        printf("File is not found. : VersionInfo.h\n");

        return -1;

    }

 

    char bufFileVer[1024];

    char bufProductVer[1024];

    char bufStrFileVer[1024];

    char bufStrProductVer[1024];

 

    fgets(bufFileVer, 1024, version);

    fgets(bufProductVer, 1024, version);

    fclose(version);

    

    int fileVer[4] = {0, };

    int productVer[4] = {0, };

 

    sscanf_s(bufFileVer, "#define FILE_VERSION\t%d,%d,%d,%d", 

      &fileVer[0], &fileVer[1], &fileVer[2], &fileVer[3]);

       sscanf_s(bufProductVer, "#define PRODUCT_VERSION\t%d,%d,%d,%d",

         &productVer[0], &productVer[1], &productVer[2], &productVer[3]);

 

    fileVer[0] = productVer[0];

    fileVer[1] = productVer[1];

    productVer[2] = 0;

    productVer[3] = 0;

 

    tm today;

    time_t now;

    time(&now);

    _localtime64_s(&today, &now);

 

    int day = (today.tm_mon + 1) * 100 + today.tm_mday;

 

    if(day != fileVer[2])

    {

        fileVer[2] = day;

        fileVer[3] = 1;

    }

    else

    {

        fileVer[3]++;

    }

    printf(" \n \n");

    printf("= MMLayer Version. =====================\n");

    printf("   File    Ver.%5d,%5d,%5d,%5d\n", 

      fileVer[0], fileVer[1], fileVer[2], fileVer[3]);

    printf("   Product Ver.%5d,%5d,%5d,%5d\n", 

      productVer[0], productVer[1], productVer[2], productVer[3]);

    printf("========================================\n");

    printf(" \n \n");

 

    

    fopen_s(&version, "VersionInfo.h", "w+");

 

    if(version == NULL)

    {

        printf("File is not found. : VersionInfo.h\n");

        return -1;

    }

 

    sprintf_s(bufFileVer, "#define FILE_VERSION\t%d,%d,%d,%d\n", 

      fileVer[0], fileVer[1], fileVer[2], fileVer[3]);

    sprintf_s(bufStrFileVer, "#define STR_FILE_VERSION\t\"%d,%d,%d,%d\\0\"\n", 

      fileVer[0], fileVer[1], fileVer[2], fileVer[3]);

 

    sprintf_s(bufProductVer, "#define PRODUCT_VERSION\t%d,%d,%d,%d\n", 

      productVer[0], productVer[1], productVer[2], productVer[3]);

    sprintf_s(bufStrProductVer, "#define STR_PRODUCT_VERSION\t\"%d, %d,%d,%d\\0\"\n",

      productVer[0], productVer[1], productVer[2], productVer[3]);

 

    fprintf_s(version, "%s", bufFileVer);

    fprintf_s(version, "%s", bufProductVer);

    fprintf_s(version, "%s", bufStrFileVer);

    fprintf_s(version, "%s", bufStrProductVer);

 

    fclose(version);

    

    return 0;

}
