//
// Created by asant on 05/10/2019.
//

#include <algorithm>
#include "NetworkServer.h"

static int id = 0;

int NetworkServer::connect(SharedEditor *sharedEditor) {
    editors.push_back(sharedEditor);
    return id++;
}

void NetworkServer::disconnect(SharedEditor *sharedEditor) {
    auto it = std::find_if(editors.begin(), editors.end(), [&](SharedEditor* it){ return (it->getSiteId()==sharedEditor->getSiteId());});
    editors.erase(it);
}

void NetworkServer::send(const Message &m) {
    messages.push_back(m);
}

void NetworkServer::dispatchMessages() {
    for (auto m = messages.begin(); m != messages.end(); m++) {
        for (auto e : editors) {
            if (e->getSiteId() != m->getSiteId()) {
                e->process(*m);
            }
        }
    }
    messages.clear();
}
