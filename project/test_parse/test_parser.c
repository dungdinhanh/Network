#include <libparse/parser.h>

int main() {
    char * str = "{ \"method\": 1, \"message\": \"Hello\", \"user\": \"anhanq\", \"password\": \"anhanqq\", \"sender\": 1, \"group\": 1, \"receiver\": 2, }";
    MessageClient msg = clientJsonToStruct(str);
    printf("Message: %s\n", msg.message);
    printf("User: %s\n", msg.user);
    printf("Password: %s\n", msg.password);

    return 0;
} 
