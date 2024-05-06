#include "menu.h"

Button::Button(const std::string& text, SDL_Rect rect) {
  this->text = text;
  this->rect = rect;
  this->clicked = false;
}

void Button::draw(Graphics graphics ) {
    TTF_Font* font = graphics.loadFont("assets/Purisa-BoldOblique.ttf", 100);
    SDL_Color color = {255, 255, 0, 0};
    SDL_Surface* textSurface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(graphics.renderer, textSurface);
    SDL_Rect textRect{rect.x + 5, rect.y + 5, rect.w - 10, rect.h - 10};
    SDL_RenderCopy(graphics.renderer, textTexture, nullptr, &textRect);
}

void Button::update(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONDOWN) {
    if (event->button.button == SDL_BUTTON_LEFT && event->button.x >= rect.x && event->button.x <= rect.x + rect.w &&
        event->button.y >= rect.y && event->button.y <= rect.y + rect.h) {
      clicked = true;
    }
  }
}

bool Button::isClicked() {

  return clicked;

}

