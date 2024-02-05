#pragma once
#ifndef TILE_H
#define TILE_H

#include <vector>
#include <string>
#include <iostream>
#include "tileson.hpp"
#include "TextureManager.h"
#include <filesystem>

namespace fs = std::filesystem;

class Tile {
    public:
        static Tile* GetInstance() {
            static Tile* instance = new Tile();
            return instance;
        }

        bool load(const std::string& id, const std::string& path) {
            tson::Tileson parser;
            map = parser.parse(fs::path(path));
            if (map->getStatus() != tson::ParseStatus::OK) {
                std::cerr << "Failed to load map from path: " << path << ", with ID: " << id << std::endl;
                return false;
            }
            this->id = id;

            for (auto& tileset : map->getTilesets()) {
                std::string imagePath = tileset.getImage().string();
                fs::path p = imagePath;
                std::string baseName = p.filename().string();
                if (!TextureManager::GetInstance()->load(baseName, imagePath)) {
                    std::cerr << "Failed to load tileset: " << imagePath << std::endl;
                    return false;
                }
            }

            return true;
        }

        tson::Layer* getLayerByName(const std::string& name) {
            if (map) {
                for (auto& layer : map->getLayers()) {
                    if (layer.getName() == name) {
                        return &layer;
                    }
                }
            }
            return nullptr;
        }


        void render(const std::string& layerName, float scale = 2.0f) {
            if (!map) {
                std::cerr << "Map is not loaded, cannot render!" << std::endl;
                return;
            }

            // Find the specified layer by name
            tson::Layer* layer = getLayerByName(layerName);
            if (layer == nullptr) {
                std::cerr << "Layer named: " << layerName << " not found. Cannot render this layer." << std::endl;
                return;
            }

            if (layer->getType() == tson::LayerType::TileLayer) {
                // Render only if it's a tile layer
                for (auto& [pos, tile] : layer->getTileData()) {
                        tson::Tileset* tileset = tile->getTileset();
                        if (!tileset) continue;

                        tson::Rect drawingRect = tile->getDrawingRect();
                        tson::Vector2f tilePosition = tile->getPosition(pos);

                        int scaledX = static_cast<int>(tilePosition.x * scale);
                        int scaledY = static_cast<int>(tilePosition.y * scale);
                        int scaledWidth = static_cast<int>(tile->getTileSize().x * scale);
                        int scaledHeight = static_cast<int>(tile->getTileSize().y * scale);

                        std::string tilesetID = tileset->getImagePath().filename().string();

                        TextureManager::GetInstance()->drawTile(tilesetID, tile->getTileSize().x, scaledX, scaledY, drawingRect.y / tile->getTileSize().y + 1, drawingRect.x / tile->getTileSize().x, scaledWidth, scaledHeight, SDL_FLIP_NONE);
                }
            }
            else {
                std::cerr << "Layer named: " << layerName << " is not a tile layer. Cannot render this layer." << std::endl;
            }
        }

        std::vector<std::vector<uint32_t>> getLayerTilesetIDsByName(const std::string& name) {
            std::vector<std::vector<uint32_t>> tilesetIDs;

            tson::Layer* layer = getLayerByName(name);
            if (layer && layer->getType() == tson::LayerType::TileLayer) {
                const std::vector<uint32_t>& data = layer->getData(); 
                int width = map->getSize().x;
                int height = map->getSize().y;

                tilesetIDs.resize(height, std::vector<uint32_t>(width, 0));

                for (int y = 0; y < height; ++y) {
                    for (int x = 0; x < width; ++x) {
                        int tileIndex = y * width + x;
                        uint32_t tileID = data[tileIndex];
                        tilesetIDs[y][x] = tileID;
                    }
                }
            }
            else {
                std::cerr << "Layer '" << name << "' not found or is not a tile layer." << std::endl;
            }

            return tilesetIDs;
        }

        void update() {
        }

        void clean() {
        }

    private:
    
        Tile() {} 
        std::string id; 
        static Tile* s_Instance;
        std::unique_ptr<tson::Map> map;
};

#endif // TILE_H
