#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <set>
#include <string>
#include <swiftly/configuration.h>

std::set<std::string> blockedMessages;

Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Configuration *config = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);

    server = new Server();
    g_playerManager = new PlayerManager();
    config = new Configuration();
}

void OnPluginStart()
{
    uint32_t msgCount = config->FetchArraySize("removemessages.blocked_messages");
    for (uint32_t i = 0; i < msgCount; i++)
    {
        const char *msg = config->Fetch<const char *>("removemessages.blocked_messages[%d]", i);
        if (msg == nullptr)
            continue;
        
        blockedMessages.insert(std::string(msg));
    }
}

bool OnClientGameMessage(Player *player, int destionation, const char *message)
{
    std::string msg = message;
    if (blockedMessages.find(msg) != blockedMessages.end())
        return false;

    return true;
}

void OnPluginStop()
{
    
}

const char *GetPluginAuthor()
{
    return "moongetsu";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "Remove Messages";
}

const char *GetPluginWebsite()
{
    return "https://github.com/moongetsu/swiftly_removemessages";
}