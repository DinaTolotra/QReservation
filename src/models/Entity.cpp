#include "Entity.hpp"

Entity::Entity()
{
    _db = new Database();
    _db->setupConnection();
    _db->setupQuery();
}

Entity::~Entity()
{
    if (_db != nullptr) {
        _db->disconnect();
        delete _db;
    }
}
