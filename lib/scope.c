int asprintf(char** a, char*b, ...);
#include <stdio.h>
#include <stdlib.h>
#include "response.h"
#include "parse.h"
#include <time.h>
const char* months[] = {"januar", "februar"  , "marcius"   , 
                       "aprilis", "majus"    , "junius"    ,
                       "julius" , "augusztus", "szeptember",
                       "oktober", "november" , "december"  };

char* getscope(char* type) {
     
    // get current time
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    char* timestr;
    asprintf(&timestr, "%d-%s-%d", timeinfo->tm_year + 1900, months[timeinfo->tm_mon], timeinfo->tm_mday);

    // get website response for type and time
    Response* response = getsite(type, timestr);
    char* parsed;
    if (response->code < 400) {
        parsed = parse(response->data->data);
    } else {
        fprintf(stderr, "Code %ld received from site\n", response->code);
    }
    free(timestr);
    cleanup(response);

    return parsed;
}
