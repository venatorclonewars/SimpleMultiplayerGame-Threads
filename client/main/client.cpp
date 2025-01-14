#include <enet/enet.h>
#include <iostream>

int main()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "An error occurred while initializing ENet!  \n" << std::endl;
        exit(1);
    }
    std::cout << "ENet initialized successfully!  \n" << std::endl;

    /*ENetHost* client;
    client = enet_host_create(NULL, 1, 1, 0, 1);

    if (client == NULL)
    {
        fprintf(stderr, "An error occured while trying to create ENET client");
    }

    ENetAddress address;
    ENetEvent event;
    ENetPeer* peer;

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 7777;

    peer = enet_host_connect(client, &address, 1, 0);


    if (peer == NULL)
    {
        fprintf(stderr, "No availabel peers for initalization");
        exit(1);
    }

    if (enet_host_service(client, &event, 5000) > 0 &&
        event.type == ENET_EVENT_TYPE_CONNECT)
    {
        puts("Connection to 127.0.0.1:7777 succeeded");
    }
    else
    {
        enet_peer_reset(peer);
    }

    while (enet_host_service(client, &event, 1000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            printf("A packet of length %u containing %s was received from %s on channel %u.\n",
                event.packet->dataLength,
                event.packet->data,
                event.peer->address.host,
                event.peer->address.port,
                event.channelID);
            break;
        }
    }

    enet_peer_disconnect(peer, 0);

    while (enet_host_service(client, &event, 3000) > 0)
    {
        switch (event.type)
        {
        case ENET_EVENT_TYPE_RECEIVE:
            enet_packet_destroy(event.packet);
            break;

        case ENET_EVENT_TYPE_DISCONNECT:
            puts("Disconnection succeede \n");
            break;
        }
    }*/

    enet_deinitialize();

	return 0;
}