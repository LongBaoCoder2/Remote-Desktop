// #include <iostream>
// #include <unordered_map>

// #include "MMO_Common.h"

// class GameServer : public olc::net::server_interface<GameMsg>
// {
// public:
//     GameServer(uint16_t nPort) : olc::net::server_interface<GameMsg>(nPort)
//     {
//     }

//     /*
//     The m_vGarbageIDs variable is used to keep track of client IDs that need to be removed from the game server. When a client disconnects unexpectedly, it is not always possible to remove it immediately from the game server's data structures. This is because the client may still have pending messages in the network queue, or it may be in the middle of processing a message.

// The m_vGarbageIDs variable allows the game server to keep track of these clients and remove them from the game server's data structures at a later time. This is done by checking the m_vGarbageIDs variable at the beginning of each game loop. If any client IDs are found in the m_vGarbageIDs variable, the game server will remove them from the game server's data structures.

// The m_vGarbageIDs variable is necessary because it allows the game server to clean up its data structures and prevent memory leaks. Without the m_vGarbageIDs variable, the game server would eventually run out of memory as it held onto data for clients that are no longer connected.
//     */
//     std::unordered_map<uint32_t, sPlayerDescription> m_mapPlayerRoster;
//     std::vector<uint32_t> m_vGarbageIDs;

// protected:
//     bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMsg>> client) override
//     {
//         // For now we will allow all
//         return true;
//     }

//     void OnClientValidated(std::shared_ptr<olc::net::connection<GameMsg>> client) override
//     {
//         // Client passed validation check, so send them a message informing
//         // them they can continue to communicate
//         olc::net::message<GameMsg> msg;
//         msg.header.id = GameMsg::Client_Accepted;
//         client->Send(msg);
//     }

//     void OnClientDisconnect(std::shared_ptr<olc::net::connection<GameMsg>> client) override
//     {
//         if (client)
//         {
//             if (m_mapPlayerRoster.find(client->GetID()) == m_mapPlayerRoster.end())
//             {
//                 // client never added to roster, so just let it disappear
//             }
//             else
//             {
//                 auto &pd = m_mapPlayerRoster[client->GetID()];
//                 std::cout << "[UNGRACEFUL REMOVAL]:" + std::to_string(pd.nUniqueID) + "\n";
//                 m_mapPlayerRoster.erase(client->GetID());
//                 m_vGarbageIDs.push_back(client->GetID());
//             }
//         }
//     }

//     void OnMessage(std::shared_ptr<olc::net::connection<GameMsg>> client, olc::net::message<GameMsg> &msg) override
//     {
//         if (!m_vGarbageIDs.empty())
//         {
//             for (auto pid : m_vGarbageIDs)
//             {
//                 olc::net::message<GameMsg> m;
//                 m.header.id = GameMsg::Game_RemovePlayer;
//                 m << pid;
//                 std::cout << "Removing " << pid << "\n";
//                 MessageAllClients(m);
//             }
//             m_vGarbageIDs.clear();
//         }

//         switch (msg.header.id)
//         {
//         case GameMsg::Client_RegisterWithServer:
//         {
//             sPlayerDescription desc;
//             msg >> desc;
//             desc.nUniqueID = client->GetID();
//             m_mapPlayerRoster.insert_or_assign(desc.nUniqueID, desc);

//             olc::net::message<GameMsg> msgSendID;
//             msgSendID.header.id = GameMsg::Client_AssignID;
//             msgSendID << desc.nUniqueID;
//             MessageClient(client, msgSendID);

//             olc::net::message<GameMsg> msgAddPlayer;
//             msgAddPlayer.header.id = GameMsg::Game_AddPlayer;
//             msgAddPlayer << desc;
//             MessageAllClients(msgAddPlayer);

//             for (const auto &player : m_mapPlayerRoster)
//             {
//                 olc::net::message<GameMsg> msgAddOtherPlayers;
//                 msgAddOtherPlayers.header.id = GameMsg::Game_AddPlayer;
//                 msgAddOtherPlayers << player.second;
//                 MessageClient(client, msgAddOtherPlayers);
//             }

//             break;
//         }

//         case GameMsg::Client_UnregisterWithServer:
//         {
//             break;
//         }

//         case GameMsg::Game_UpdatePlayer:
//         {
//             // Simply bounce update to everyone except incoming client
//             MessageAllClients(msg, client);
//             break;
//         }
//         }
//     }
// };

// int main()
// {
//     GameServer server(60000);
//     server.Start();

//     while (1)
//     {
//         server.Update(-1, true);
//     }
//     return 0;
// }