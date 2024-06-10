#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "wsServer/include/ws.h"

/* variable to store the unity socket connection */
ws_cli_conn_t * unity_client;

/* when a connection is made */
void onopen(ws_cli_conn_t *client)
{
    /* display address of client */
    char *cli;
    cli = ws_getaddress(client);
    printf("Connection opened, addr: %s\n", cli);
}

/* when a connection is closed */
void onclose(ws_cli_conn_t *client)
{
    /* display address of client */
    char *cli;
    cli = ws_getaddress(client);
    printf("Connection closed, addr: %s\n", cli);
}

/* each time a message is recieved */
void onmessage(ws_cli_conn_t *client, const unsigned char *msg, uint64_t size, int type)
{

    /* the Unity client upon connecting sends the message "TREG",
       so to determine whether a new client is the correct client we
       check we have received that message
    */
    int cmp;
    cmp = strcmp("TREG", (char*)msg);
    printf("was the message TREG? %d \n", cmp);
    /* if so, we fill in the socket data to our variable */
    if (cmp==0) {
	printf("we got a T-REG client\n");
	unity_client = client;
    }

    /* display the message to the server log */
    char *cli;
    cli = ws_getaddress(client);
    printf("I receive a message %s (size: %" PRId64", type: %d), from %s\n", msg, size, type, cli);

    /* forward all messages to the T-REG client */
    //ws_sendframe(starling_client, (char*)msg, size, type);
    ws_sendframe_txt(unity_client, (char*)msg);

}

int main(void)
{
 /*
     * Main loop, this function never* returns.
     *
     * *If the .thread_loop is != 0, a new thread is created
     * to handle new connections and ws_socket() becomes
     * non-blocking.
     */
    ws_socket(&(struct ws_server){
        /*
         * Bind host, such as:
         * localhost -> localhost/127.0.0.1
         * 0.0.0.0   -> global IPv4
         * ::        -> global IPv4+IPv6 (Dual stack)
         */
        .host = "localhost",
        .port = 9010,
        .thread_loop   = 0,
        .timeout_ms    = 1000,
        .evs.onopen    = &onopen,
        .evs.onclose   = &onclose,
        .evs.onmessage = &onmessage
    });


    /* main never returns */
    return (0);
}
