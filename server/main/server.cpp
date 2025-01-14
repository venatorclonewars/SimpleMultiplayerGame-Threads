#include <enet/enet.h>
#include <iostream>

#include <string>
#include <map>

class ClientData
{
private:
    int m_id;
    std::string m_username;

public:
    ClientData(int id, ENetEvent* event) : m_id(id) {}
    int getID() { return m_id; }
};

std::map<int, ClientData*> clientMap;

//void sendPacket(ENetPeer* server, const char* data)
//{
//    ENetPacket* packet = enet_packet_create(data, strlen(data) + 1, ENET_PACKET_FLAG_RELIABLE);
//    enet_peer_send(server, 0, packet);
//}

void sendPacket(ENetPeer* server, const char* data)
{
    size_t dataSize = 0;
    memcpy(&dataSize, data, sizeof(size_t));
    
    printf("data size on server %zu \n", dataSize);
    if (dataSize == 0 || dataSize > 300)
        return;
    ENetPacket* packet = enet_packet_create(data, dataSize + sizeof(size_t), ENET_PACKET_FLAG_RELIABLE);
    enet_peer_send(server, 0, packet);
}

void broadcastPacket(ENetHost* server, int senderID, const char* data)
{
    int id = 0;

    for (int i = 0; i < server->peerCount; i++) 
    {
        ENetPeer* peer = &server->peers[i];

        if (static_cast<ClientData*>(peer->data) != nullptr)
            id = static_cast<ClientData*>(peer->data)->getID();

        /*if (id == senderID)
            continue;*/
        //printf("\n sent packet");
        sendPacket(peer, data);
    }
}


int main()
{
    if (enet_initialize() != 0)
    {
        std::cerr << "An error occurred while initializing ENet!" << std::endl;
        exit(1);
    }
    std::cout << "ENet initialized successfully!" << std::endl;

    ENetAddress address;
    ENetEvent event;
    ENetHost* server;

    address.host = ENET_HOST_ANY;
    address.port = 7777;

    server = enet_host_create(&address, 32, 1, 0, 0);

    if (server == NULL)
    {
        fprintf(stderr, "An error occured while trying to create ENET server \n");
    }

    enet_address_set_host(&address, "127.0.0.1");
    address.port = 7777;


    int newPlayerID = 0;
    int id = 0;

    while (true)
    {
        while (enet_host_service(server, &event, 1000) > 0)
        {
            switch (event.type)
            {
            case ENET_EVENT_TYPE_CONNECT:
                printf("A new client connected from %x:%u. \n",
                    event.peer->address.host,
                    event.peer->address.port
                );

                newPlayerID++;
                clientMap[newPlayerID] = new ClientData(newPlayerID, &event);
                event.peer->data = clientMap[newPlayerID];

                sendPacket(event.peer, (const char*)"Hi new player");

                // Set the no-response timeout limit to 50 seconds
                enet_peer_timeout(event.peer, 50000, 10000, 50000);
                break;

            case ENET_EVENT_TYPE_RECEIVE:
                printf("\n");
                printf("A packet of length %u was received from port:%u on channel %u.\n",
                    event.packet->dataLength,
                    event.peer->address.port,
                    event.channelID);

                id = static_cast<ClientData*>(event.peer->data)->getID();
                printf("Player ID: %u", id);
                printf("\n");

               /* printf("Packet contents: ");
                fwrite(event.packet->data, 1, event.packet->dataLength, stdout);
                printf("\n"); */      
               
                broadcastPacket(server, id, reinterpret_cast<const char*>(event.packet->data));

                break;

            case ENET_EVENT_TYPE_DISCONNECT:
                printf("%x%u disconnected. \n",
                    event.peer->address.host,
                    event.peer->address.port);

                delete static_cast<ClientData*>(event.peer->data);
                clientMap.erase(static_cast<ClientData*>(event.peer->data)->getID());
                event.peer->data = nullptr;
 
                break;
            }
        }

        //broadcastPacket(server, id, (const char*)"Random data from the server");

    }
    

    enet_host_destroy(server);
    enet_deinitialize();

	return 0;
}
