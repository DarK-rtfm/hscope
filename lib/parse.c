// Originally supposed to be a parser function with libxml2, but the site is HTML5 and broken as fuck.
#include <string.h>
#include <stdlib.h>
char* parse(char* r) {
    const char* anchor = "<div class=\"details-content\">";
    const char* anchor2 = "</div>";
    char* begin = strstr(r, anchor) + strlen(anchor);
    char* end = strstr(begin, anchor2);
    char* parsed = malloc ((size_t)(end-begin) + 1);
    strncpy(parsed, begin, (size_t)(end-begin));
    parsed[end-begin]=0;
    return parsed;
}
