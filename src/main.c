#include <stdio.h>
#include "../headers/command_parser.h"
#include "../headers/http_server.h"

int main(int argc, char *argv[])
{
    if (parse_commands(argc, argv) == 0)
    {
        printf("argc: %d\n", argc);
        printf("argv:\n");

        for (int i = 0; i < argc; i++)
        {
            printf("  %s\n", argv[i]);
        }

        start_HTTP_server();
    }

    return 0;
}
