

#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {
}

bool CollisionHandler::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    //std::cout << a.x << ", " << b.x + b.w << ", " << a.x + a.w << ", " << b.x << std::endl;
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);

    //std::cout << x_overlaps << ", " << y_overlaps << std::endl;
    return x_overlaps && y_overlaps;
}

bool CollisionHandler::checkCollisionVec(Collider* a, std::vector<Collider*> b)
{
    bool after = false;
    for (Collider* i : b) {
        if (i == a) {
            after = true;
        }
	    if (a != i && checkCollision(a->get(), i->get()) && after) {
            return true;
	    }
    }
    return false;

}

bool CollisionHandler::mapCollision(const SDL_Rect& a, std::string layerName) {

    m_CollisionMap = Tile::GetInstance()->getLayerTilesetIDsByName(layerName);

    const int tileSize = 32;
    const int ColCount = 40;
    const int RowCount = 30;

    int left_tile = a.x / tileSize;
    int right_tile = (a.x + a.w) / tileSize;
    int top_tile = a.y / tileSize;
    int bottom_tile = (a.y + a.h) / tileSize;
    
    left_tile = std::max(0, left_tile);
    right_tile = std::min(right_tile, ColCount - 1);
    top_tile = std::max(0, top_tile);
    bottom_tile = std::min(bottom_tile, RowCount);

    for (int j = top_tile; j <= bottom_tile; ++j) {
        for (int i = left_tile; i <= right_tile; ++i) {
            if (m_CollisionMap[j][i] > 0) {
                return true;
            }
        }
    }
    return false;
}