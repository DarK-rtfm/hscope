#include "lib/scope.h"
//#include <libnotify/notification.h>
#include <libnotify/notify.h>
int main(int argc, char** argv) {
    char* type = NULL;
    int notif = 0;
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-n")) {
            notif=1;}
        else type=argv[i];
    }
    if (type == NULL) {fprintf(stderr, "Usage: %s [-n] csillagjegy\n", *argv); return 2;}
    char* scope = getscope(type);

    if (notif) {
        NotifyNotification *n;
        notify_init("CSCOPE");
        n = notify_notification_new (scope, NULL, NULL);
        if (!notify_notification_show (n, NULL)) {
			fprintf(stderr, "Failed to send notification.");
			return 1;
		}
    } else {
        printf("%s\n", scope);
    }

    free(scope);
}
