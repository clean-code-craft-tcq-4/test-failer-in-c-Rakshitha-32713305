#include <stdio.h>
#include <assert.h>
#include <string.h>

char line[1000];
char reference_line[1000];

const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
 
int printColorMap(char *line)
{
    int pairno =0;
    int i = 0, j = 0;
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            pairno += sprintf(&line[pairno],"%d | %s | %s\n", ((i * 5 + j)+1), (majorColor[i]), (minorColor[j]));           
        }
    }
    return i * j;
}

void colorcode_ReferenceManual_Display(char *reference_line)
{
    int i = 0;
    int j = 0;
    int pairno =0; 
 
    for(i = 0; i < 5; i++)
    {
        for(j = 0; j < 5; j++)
        {
            pairno += sprintf(&reference_line[pairno],"%d\t|\t%s\t\t|\t%s\n",((i * 5 + j)+1), (majorColor[i]), (minorColor[j]));
        }
    }
}

void colormap_test()
{   
    assert(strcmp(&reference_line[0],&line[0])== 0);   
}


int main()
{    
    int result = printColorMap(line);
    printf("%s",line);
    colorcode_ReferenceManual_Display(reference_line);
    assert(result == 25);
    colormap_test();
    printf("All is well (maybe!)\n");
    return 0;
}
