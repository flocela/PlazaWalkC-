#include "BroadcastAgent.h"

using namespace std;

BroadcastAgent::BroadcastAgent(BoardProxy&& boardProxy): _boardProxy{std::move(boardProxy)}
{}

void BroadcastAgent::requestBroadcast()
{
    _boardProxy.sendChanges();
}

