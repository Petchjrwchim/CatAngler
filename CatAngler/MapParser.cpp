//#include "MapParser.h"
//
//MapParser* MapParser::s_Instance = nullptr;
//
//bool MapParser::load()
//{
//    return Parse("map", "assets\\images\\map.tmx");
//}
//
//void MapParser::clean()
//{
//    std::map<std::string, GameMap*>::iterator it;
//    for (it = m_MapDict.begin(); it != m_MapDict.end(); it++) {
//        delete it->second; // Free the memory.
//        it->second = nullptr;
//    }
//
//    m_MapDict.clear();
//}
//
//
//bool MapParser::Parse( std::string id, std::string source)
//{
//    TiXmlDocument xml;
//    xml.LoadFile(source);
//
//    if (xml.Error()) {
//        std::cerr << "Failed to load: "<< source << std::endl;
//            return false;
//    }
//
//   
//    
//    TiXmlElement* root = xml.RootElement();
//    int rowcount, colcount, tilesize = 0;
//
//    //if (!root) {
//    //    std::cerr << "Failed to get root element." << std::endl;
//    //    return false;
//    //}
//
//    root->Attribute("width", &colcount);
//    root->Attribute("height", &rowcount);
//    root->Attribute("tilewidth", &tilesize);
//
//    TilesetList tilesets;
//    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
//        if (e->Value() == std::string("tileset")) {
//            tilesets.push_back(parseTileset(e));
//        }
//    }
//
//    GameMap* gamemap = new GameMap();
//    for (TiXmlElement* e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
//        if (e->Value() == std::string("layer")) {
//            TileLayer* tileLayer = parseTileLayer(e, tilesets, tilesize, rowcount, colcount);
//            gamemap->m_MapLayers.push_back(tileLayer);
//        }
//    }
//    m_MapDict[id] = gamemap;
//    return true;
//
//}
//
//Tileset MapParser::parseTileset(TiXmlElement* xmlTileset)
//{
//    Tileset tileset;
//    tileset.Name = xmlTileset->Attribute("name");
//    xmlTileset->Attribute("firstgid", &tileset.firstID);
//
//    
//    tileset.lastID = (tileset.firstID + tileset.TileCount) - 1;
//
//    xmlTileset->Attribute("tilecount", &tileset.ColCount);
//    tileset.RowCount = tileset.TileCount / tileset.ColCount;
//    xmlTileset->Attribute("tilewidth", &tileset.TileSize);
//
//    TiXmlElement* image = xmlTileset->FirstChildElement();
//    tileset.Source = image->Attribute("source");
//    return tileset;
//
//}
//
//TileLayer* MapParser::parseTileLayer(TiXmlElement* xmlLayer, TilesetList tilesets, int tilesize, int rowcount, int colcount)
//{
//    TiXmlElement* data = nullptr;  // Initialize to nullptr to avoid using an uninitialized pointer
//    for (TiXmlElement* e = xmlLayer->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
//        if (e->Value() == std::string("data")) {
//            data = e;
//            break;
//        }
//    }
//
//    std::string matrix(data->GetText());
//    std::istringstream iss(matrix);
//    std::string id;
//
//    TileMap tilemap(rowcount, std::vector<int>(colcount, 0));
//
//    for (int row = 0; row < rowcount; row++) {
//        for (int col = 0; col < colcount; col++) {
//            std::getline(iss, id, ',');
//            std::stringstream converter(id);
//            converter >> tilemap[row][col];
//
//            if (!iss.good())
//                break;
//        }
//    }
//    
//    return (new TileLayer(tilesize, rowcount, colcount, tilemap, tilesets));
//}
// MapParser.cpp
#include "MapParser.h"
#include "TextureManager.h"
#include <iostream>
#include "SDL_image.h" // Ensure you have SDL_image for texture loading

MapParser* MapParser::s_Instance = nullptr;

MapParser* MapParser::GetInstance() {
    if (s_Instance == nullptr) {
        s_Instance = new MapParser();
    }
    return s_Instance;
}

bool MapParser::LoadMap(std::string mapFile) {
    TiXmlDocument xmlDocument;
    if (!xmlDocument.LoadFile(mapFile.c_str())) {
        std::cerr << "Loading map failed: " << mapFile << std::endl;
        return false;
    }

    TiXmlElement* pRoot = xmlDocument.RootElement();
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        if (std::string(e->Value()) == "tileset") {
            ParseTilesets(e);
        }
        else if (std::string(e->Value()) == "layer") {
            ParseLayer(e);
        }
    }

    return true;
}

void MapParser::ParseTilesets(TiXmlElement* pTilesetRoot) {
    Tileset tileset;
    pTilesetRoot->Attribute("firstgid", &tileset.firstGid);
    pTilesetRoot->FirstChildElement("image")->Attribute("width", &tileset.tileWidth);
    pTilesetRoot->FirstChildElement("image")->Attribute("height", &tileset.tileHeight);
    tileset.name = pTilesetRoot->Attribute("name");
    tileset.imagePath = pTilesetRoot->FirstChildElement("image")->Attribute("source");
    tileset.texture = LoadTexture(tileset.imagePath);

    // Assuming a single tileset for simplicity
    tilesets[tileset.name] = tileset;
}

void MapParser::ParseLayer(TiXmlElement* pLayerRoot) {
    Layerm layer;
    pLayerRoot->Attribute("width", &layer.width);
    pLayerRoot->Attribute("height", &layer.height);

    std::string data = pLayerRoot->FirstChildElement("data")->GetText();
    // You'll need to parse the CSV data or whichever format you're using in your TMX file
    // This is just a placeholder to indicate where to parse layer tile data

    // Assuming a single layer for simplicity
    layers.push_back(layer);
}

SDL_Texture* MapParser::LoadTexture(std::string path) {
    SDL_Texture* texture = IMG_LoadTexture(SDL_GetRenderer(SDL_GetWindowFromID(1)), path.c_str()); // Simplified
    if (texture == nullptr) {
        std::cerr << "Failed to load texture: " << IMG_GetError() << std::endl;
    }
    return texture;
}

void MapParser::Render() {
}



void MapParser::Clean() {
    // Clean up loaded tilesets textures
    for (auto& ts : tilesets) {
        SDL_DestroyTexture(ts.second.texture);
    }
    tilesets.clear();
    layers.clear();
}

// Remember to call MapParser::GetInstance()->LoadMap("path/to/your/map.tmx") in your main game initialization
// And MapParser::GetInstance()->Render() in your game loop

