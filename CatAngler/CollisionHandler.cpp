//#include "CollisionHandler.h"
//#include "Engine.h"
//
//CollisionHandler* CollisionHandler::s_Instance = nullptr;
//
//CollisionHandler::CollisionHandler() {
//    tson::Layer* layer = Tile::GetInstance()->getLayer(2);
//    if (layer != nullptr && layer->getType() == tson::LayerType::TileLayer) {
//        m_CollisionLayer = layer;
//    }
//}
//
//bool CollisionHandler::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
//    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
//    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
//    return x_overlaps && y_overlaps;
//}
//
//bool CollisionHandler::mapCollision(const SDL_Rect& a) {
//    const int tileSize = 4; // Size of each tile in pixels
//    const int ColCount = 30; // Width of the map in tiles
//    const int RowCount = 20; // Height of the map in tiles
//
//    // Calculate the range of tiles that intersect with rectangle 'a'
//    int left_tile = a.x / tileSize;
//    int right_tile = (a.x + a.w) / tileSize;
//    int top_tile = a.y / tileSize;
//    int bottom_tile = (a.y + a.h) / tileSize;
//
//    // Clamp tile coordinates to map boundaries
//    left_tile = std::max(0, left_tile);
//    right_tile = std::min(right_tile, ColCount - 1);
//    top_tile = std::max(0, top_tile);
//    bottom_tile = std::min(bottom_tile, RowCount - 1);
//
//    // Access the collision layer and check each tile within the intersection range
//    for (int y = top_tile; y <= bottom_tile; ++y) {
//        for (int x = left_tile; x <= right_tile; ++x) {
//            tson::Tile* tile = m_CollisionLayer->getTileData(x, y);
//            if (tile != nullptr && tile->getId() > 0) { // If tile exists and has a non-zero GID
//                return true; // Collision detected
//            }
//        }
//    }
//    return false; // No collision detected
//}


#include "CollisionHandler.h"
#include "Engine.h"

CollisionHandler* CollisionHandler::s_Instance = nullptr;

CollisionHandler::CollisionHandler() {

    m_CollisionMap = Tile::GetInstance()->getLayerTilesetIDsByName("Collision");

}

bool CollisionHandler::checkCollision(const SDL_Rect& a, const SDL_Rect& b) {
    bool x_overlaps = (a.x < b.x + b.w) && (a.x + a.w > b.x);
    bool y_overlaps = (a.y < b.y + b.h) && (a.y + a.h > b.y);
    return x_overlaps && y_overlaps;
}

bool CollisionHandler::mapCollision(const SDL_Rect& a) {
    const int tileSize = 32;
    const int ColCount = 30;
    const int RowCount = 20;

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