#include "../state.h"

using namespace state;
using namespace std;

Troll::Troll(){
    entityId=TROLL;
}

EntityId const Troll::getEntityId (){
    return entityId;
}
