#include "Slider.h"

Slider::Slider(int x, int y, SDL_Renderer* renderer) : m_x(x), m_y(y), m_MaxValue(128), m_renderer(renderer), m_isDragging(false) {
    m_value = m_MaxValue / 2;
}

void Slider::draw() const {
    SDL_Rect sliderRect = { m_x, m_y, SLIDER_WIDTH, SLIDER_HEIGHT };
    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(m_renderer, &sliderRect);

    SDL_SetRenderDrawColor(m_renderer, 0x80, 0x80, 0x80, 0xFF);
    SDL_RenderDrawRect(m_renderer, &sliderRect);

    int knobWidth = 10;
    int knobPosition = (SLIDER_WIDTH - knobWidth) * m_value / m_MaxValue;
    SDL_Rect sliderIndicator = { m_x + knobPosition, m_y, knobWidth, SLIDER_HEIGHT };
    SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0x00, 0xFF);
    SDL_RenderFillRect(m_renderer, &sliderIndicator);
}


void Slider::handleEvent(const SDL_Event& e) {
    switch (e.type) {
    case SDL_MOUSEBUTTONDOWN:
        if (e.button.button == SDL_BUTTON_LEFT && isMouseInside(e.button.x, e.button.y)) {
            m_isDragging = true;
            updateValue(e.button.x);
        }
        break;
    case SDL_MOUSEBUTTONUP:
        m_isDragging = false;
        break;
    case SDL_MOUSEMOTION:
        if (m_isDragging) {
            updateValue(e.motion.x);
        }
        break;
    default:
        break;
    }
}

bool Slider::isMouseInside(int mouseX, int mouseY) const {
    return mouseX >= m_x && mouseX <= m_x + SLIDER_WIDTH && mouseY >= m_y && mouseY <= m_y + SLIDER_HEIGHT;
}

void Slider::updateValue(int mouseX) {
    int relativePosition = mouseX - m_x;

    if (relativePosition < 0) {
        relativePosition = 0;
    }
    else if (relativePosition > SLIDER_WIDTH) {
        relativePosition = SLIDER_WIDTH;
    }

    int value = static_cast<int>((static_cast<double>(relativePosition) / SLIDER_WIDTH) * m_MaxValue);

    // Assign the integer value to m_value
    m_value = value;
}
