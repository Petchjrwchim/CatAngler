#pragma once
#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <vector>
#include "Layer.h"

class GameMap
{
	public:
		void render() {
			for (unsigned int i = 0; i < m_MapLayers.size(); i++)
				m_MapLayers[i]->render();
		}

		void update() {
			for (unsigned int i = 0; i < m_MapLayers.size(); i++) {
				if (m_MapLayers[i]) {  // Check if the pointer is not null before using it
					m_MapLayers[i]->update();
				}
			}
		}

		std::vector<Layer*> getMapLater() { return m_MapLayers; }

	private:
		friend class MapParser;
		std::vector<Layer*> m_MapLayers;
};


#endif GAMEMAP_H