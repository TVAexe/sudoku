#include "Nut_bam.h"

Button::Button()
	: mCurrentState(ButtonState::BUTTON_MOUSE_OUT),
	  mTexture(nullptr),
	  mButtonRect({ 0, 0, 0, 0 }),
	  mTextureRect({0, 0, 0, 0}),
	  mMouseOutColour({ 219, 184, 215, SDL_ALPHA_OPAQUE }), 
	  mMouseOverMotionColour({ 95, 89, 191, SDL_ALPHA_OPAQUE }),
	  mMouseDownColour({ 91, 191, 116, SDL_ALPHA_OPAQUE }), 
	  mMouseUpColour({ 95, 89, 191, SDL_ALPHA_OPAQUE }), 
	  mSelected(false)
{

}

void Button::setTexture(SDL_Texture* texture)
{
	mTexture = texture;
}

void Button::setButtonRect(const SDL_Rect& rect)
{
	mButtonRect = rect;
}

void Button::setTextureRect(const SDL_Rect& rect)
{
	mTextureRect = rect;
}

void Button::centerTextureRect()
{
	int textureWidth;
	int textureHeight;
	SDL_QueryTexture(mTexture, NULL, NULL, &textureWidth, &textureHeight);

	const int textureStartRow = mButtonRect.y + 0.5 * (mButtonRect.h - textureHeight);
	const int textureStartCol = mButtonRect.x + 0.5 * (mButtonRect.w - textureWidth);

	mTextureRect = { textureStartCol, textureStartRow, textureWidth, textureHeight };
}

void Button::setSelected(const bool selected)
{
	mSelected = selected;
}

bool Button::isMouseInside(const int x, const int y)
{

	bool inside = true;


	if (x < mButtonRect.x)
	{
		inside = false;
	}

	else if (x > mButtonRect.x + mButtonRect.w)
	{
		inside = false;
	}

	else if (y < mButtonRect.y)
	{
		inside = false;
	}
	
	else if (y > mButtonRect.y + mButtonRect.h)
	{
		inside = false;
	}

	return inside;
}

ButtonState Button::getMouseEvent(const SDL_Event* event)
{

	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);


		if (!isMouseInside(x, y))
		{
			mCurrentState = ButtonState::BUTTON_MOUSE_OUT;
		}
	
		else
		{
			switch (event->type)
			{
			case SDL_MOUSEMOTION:
				mCurrentState = ButtonState::BUTTON_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mCurrentState = ButtonState::BUTTON_MOUSE_DOWN;
				break;

			case SDL_MOUSEBUTTONUP:
				mCurrentState = ButtonState::BUTTON_MOUSE_UP;
				break;

			}
		}
	}
	return mCurrentState;
}

void Button::setMouseDownColour(const SDL_Color& colour)
{
	mMouseDownColour = colour;
}

void Button::renderButton(SDL_Renderer* renderer)
{
	if (mSelected)
	{
		SDL_SetRenderDrawColor(renderer, mMouseDownColour.r, mMouseDownColour.g, mMouseDownColour.b, mMouseDownColour.a);
	}
	else
	{
		switch (mCurrentState)
		{
		case ButtonState::BUTTON_MOUSE_OUT:
			SDL_SetRenderDrawColor(renderer, mMouseOutColour.r, mMouseOutColour.g, mMouseOutColour.b, mMouseOutColour.a);
			break;
		case ButtonState::BUTTON_MOUSE_OVER_MOTION:
			SDL_SetRenderDrawColor(renderer, mMouseOverMotionColour.r, mMouseOverMotionColour.g, mMouseOverMotionColour.b, mMouseOverMotionColour.a);
			break;
		case ButtonState::BUTTON_MOUSE_DOWN:
			SDL_SetRenderDrawColor(renderer, mMouseDownColour.r, mMouseDownColour.g, mMouseDownColour.b, mMouseDownColour.a);
			break;
		case ButtonState::BUTTON_MOUSE_UP:
			SDL_SetRenderDrawColor(renderer, mMouseUpColour.r, mMouseUpColour.g, mMouseUpColour.b, mMouseUpColour.a);
			break;

		}
	}

	SDL_RenderFillRect(renderer, &mButtonRect);
}

void Button::renderTexture(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, mTexture, nullptr, &mTextureRect);
}

