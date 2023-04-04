
#include <SDL.h>

enum class ButtonState
{
	BUTTON_MOUSE_OUT = 0,
	BUTTON_MOUSE_OVER_MOTION = 1,
	BUTTON_MOUSE_DOWN = 2,
	BUTTON_MOUSE_UP = 3,
};
class Button
{
private:
	ButtonState mCurrentState;
	SDL_Texture* mTexture;
	SDL_Rect mButtonRect;
	SDL_Rect mTextureRect;
	bool mSelected;
protected:
	SDL_Color mMouseOutColour;
	SDL_Color mMouseOverMotionColour;
	SDL_Color mMouseDownColour;
	SDL_Color mMouseUpColour;
public:
	Button();
	void setTexture(SDL_Texture* texture);
	void setButtonRect(const SDL_Rect& rect);
	void setTextureRect(const SDL_Rect& rect);
	void centerTextureRect();
	void setSelected(const bool selected);
	bool isMouseInside(const int x, const int y);
	ButtonState getMouseEvent(const SDL_Event* event);
	void setMouseDownColour(const SDL_Color& colour);
	void renderButton(SDL_Renderer* renderer);
	void renderTexture(SDL_Renderer* renderer);

};