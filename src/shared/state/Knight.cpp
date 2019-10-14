#include "../state.h"

using namespace state;
using namespace std;

Knight::Knight(){
    entityId=KNIGHT;
}

EntityId const Knight::getEntityId (){
    return this->entityId;
}
