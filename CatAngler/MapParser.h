#pragma once
//#ifndef MAPPARSER_H
//#define MAPPARSER_H
//
//#include <map>
//#include <string>
//#include "GameMap.h"
//#include "TileLayer.h"
//#include "tinyxml.h"
//
//class MapParser
//{
//	public:
//		bool load();
//		void clean();
//
//		inline GameMap* getMaps(std::string id) { return m_MapDict[id];  }
//		inline static MapParser* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new MapParser(); }
//
//	private:
//		MapParser(){}
//		static MapParser* s_Instance;
//		std::map<std::string, GameMap*> m_MapDict;
//
//		bool Parse(std::string id, std::string source);
//		Tileset parseTileset(TiXmlElement* xmlTileset);
//		TileLayer* parseTileLayer(TiXmlElement* xmlLayer,TilesetList tilesets, int tilesize, int rowcount, int colcount);
//};
//
//#endif
// MapParser.h
#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include "tinyxml.h"
#include <string>
#include <map>
#include <vector>
#include <SDL.h>

struct Tileset {
    int firstGid;
    int tileWidth;
    int tileHeight;
    int spacing;
    int margin;
    int count;
    int columns;
    std::string name;
    std::string imagePath;
    SDL_Texture* texture;
};

struct Layerm {
    int width;
    int height;
    std::vector<int> tiles;
};

class MapParser {
public:
    static MapParser* GetInstance();
    bool LoadMap(std::string mapFile);
    void Clean();

    // Rendering function for demonstration
    void Render();

private:
    MapParser() {}
    static MapParser* s_Instance;
    std::map<std::string, Tileset> tilesets;
    std::vector<Layerm> layers;

    // Helper methods
    void ParseTilesets(TiXmlElement* pTilesetRoot);
    void ParseLayer(TiXmlElement* pLayerRoot);
    SDL_Texture* LoadTexture(std::string path);
};

#endif