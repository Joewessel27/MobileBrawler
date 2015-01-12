
#pragma once

#include "../Graphics/TextureImage.h"
#include "../Utilities/Font/Font.h"

#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"

namespace GameLibrary
{
	class Window;

	class AssetManager
	{
	private:
		Window*window;

		ArrayList<Pair<String,TextureImage*> > textures;
		ArrayList<Pair<String,Font*> > fonts;

	public:
		AssetManager(Window&window);
		virtual ~AssetManager();

		virtual bool loadTexture(const String&path, String&error=String());
		virtual void unloadTexture(const String&path);
		virtual void unloadTextures();
		virtual TextureImage* getTexture(const String&path);

		virtual bool loadFont(const String&path, String&error=String());
		virtual void unloadFont(const String&path);
		virtual void unloadFonts();
		virtual Font* getFont(const String&path);
	};
}