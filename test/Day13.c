#include <stdio.h>
#include <String.h>
#include <Day13.c>
#include "test.h"



int main()
{
    TEST_INIT();
    char in[] = 
"[1,1,3,1,1]\n"
"[1,1,5,1,1]\n"
"\n"
"[[1],[2,3,4]]\n"
"[[1],4]\n"
"\n"
"[9]\n"
"[[8,7,6]]\n"
"\n"
"[[4,4],4,4]\n"
"[[4,4],4,4,4]\n"
"\n"
"[7,7,7,7]\n"
"[7,7,7]\n"
"\n"
"[]\n"
"[3]\n"
"\n"
"[[[]]]\n"
"[[]]\n"
"\n"
"[1,[2,[3,[4,[5,6,7]]]],8,9]\n"
"[1,[2,[3,[4,[5,6,0]]]],8,9]\n";


/*
L5 (E1 E1 E3 E1 E1)

[5, [6, 7], 8]

L3 (E5 L2 (E6 E7) E8)
*/

    char input[] = "[50, [[]], [60,70], 91]\n";

    Node node[] = {
        { .value =
            { .head = 1
            , .type = LIST
            }
        , .next = 0
        },
        { .value =
            { .number = 44
            , .type = NUMBER
            }
        , .next = 2
        },
        { .value =
            { .head = 0
            , .type = LIST
            }
        , .next = 3
        },
        { .value =
            { .head = 5
            , .type = LIST
            }
        , .next = 4
        },
        { .value =
            { .number = 99
            , .type = NUMBER
            }
        , .next = 0
        },
        { .value =
            { .number = 55
            , .type = NUMBER
            }
        , .next = 6
        },
        { .value =
            { .number = 66
            , .type = NUMBER
            }
        , .next = 0
        }
    };

    Node nodes[32] = {0};



    /*
    List_parse((String){input, sizeof(input)}, nodes, 0);
    printf("Print list 2: ");
    List_print(nodes, 0);
    printf("\n");
    printf("List length %zu\n", List_length(nodes, 1));
    printf("List size %zu\n", List_size(nodes, 0));
    */

    RUN(Day13_solve, in, "", "");
}

