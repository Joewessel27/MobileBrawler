
#pragma once

#include "View.h"
#include "../Application/AssetManager.h"
#include "../Graphics/Image.h"
#include "../Graphics/Graphics.h"
#include "../Utilities/String.h"
#include "../Utilities/Geometry/Vector2.h"
#include <mutex>

namespace GameLibrary
{
//WindowSettings

	class WindowSettings
	{
		friend class Window;
	private:
		Vector2i position;
		Vector2u size;
		String title;
		Image*icon;
		Color backgroundColor;
		int style;

		void* createIconData() const;
		
	public:
		WindowSettings();
		WindowSettings(const WindowSettings&);
		WindowSettings(const Vector2i& position, const Vector2u& size, const String&title="", Image*icon=nullptr, const Color&backgroundColor=Color::WHITE, int style=0);
		~WindowSettings();

		WindowSettings& operator=(const WindowSettings&);
		
		void setPosition(const Vector2i&);
		const Vector2i& getPosition() const;
		
		void setSize(const Vector2u&);
		const Vector2u& getSize() const;
		
		void setTitle(const String&);
		const String& getTitle() const;
		
		void setIcon(Image*);
		const Image* getIcon() const;

		void setBackgroundColor(const Color&);
		const Color& getBackgroundColor() const;
		
		void setStyle(int);
		int getStyle() const;
	};

//Window

	class WindowEventListener;

	class Window
	{
		friend class EventManager;
		friend class Graphics;
	public:
		enum WindowStyle
		{
			STYLE_DEFAULT = 0x00000000,
			STYLE_BORDERLESS = 0x00000001,
			STYLE_FULLSCREEN = 0x00000002,
			STYLE_HIDDEN = 0x00000004,
			STYLE_RESIZABLE = 0x00000008,
			STYLE_MINIMIZED = 0x00000010,
			STYLE_MAXIMIZED = 0x00000020
		};

		enum WindowPosition
		{
			POSITION_UNDEFINED = 0x0fffffff,
			POSITION_CENTERED = 0x0ffffffe
		};
		
		static WindowSettings getDefaultSettings();
		
		Window();
		Window(const Window&) = delete;
		virtual ~Window();

		Window& operator=(const Window&) = delete;
		
		void create(const WindowSettings&settings = Window::getDefaultSettings());
		
		void refresh();
		void clear(const Color&clearColor=Color::WHITE);
		void destroy();
		
		Image*capture();
		virtual Graphics* getGraphics();
		AssetManager* getAssetManager();

		static RectangleI getDisplayBounds(unsigned int displayIndex);
		
		const Vector2i& getPosition();
		void setPosition(const Vector2i&);
		
		const Vector2u& getSize();
		void setSize(const Vector2u&);

		const String& getTitle();
		void setTitle(const String&);

		const Color& getBackgroundColor();
		void setBackgroundColor(const Color&color);

		Image* getIcon();
		void setIcon(Image*);

		View* getView();
		
		bool isOpen();
		bool isFocused();
		bool isVisible();
		void setVisible(bool);
		bool isFullscreen();
		void setFullscreen(bool);
		void setFullscreen(bool toggle, unsigned int width, unsigned int height);

		void addEventListener(WindowEventListener*);
		void removeEventListener(WindowEventListener*);

		TransformD getViewTransform();

		void getHandlePtr(void*ptr) const;
		void*getWindowData() const;
		
	private:
		void*windowdata;
		unsigned int windowID;
		void*icondata;
		View*view;
		Graphics*graphics;
		AssetManager*assetManager;
		WindowSettings settings;
		Vector2u windowed_size;
		
		ArrayList<WindowEventListener*> eventListeners;
		std::mutex listenermutex;
		
		void callListenerEvent(byte eventType, int x, int y, bool external, bool* returnVal = nullptr);
	};

//WindowEventListener

	class WindowEventListener
	{
	public:
		/*Destructor*/
		virtual ~WindowEventListener();
		/*Event called when the window has been shown
			\param window the window that was shown*/
		virtual void onWindowShown(Window*window);
		/*Event called when the window has been hidden
			\param window the window that was hidden*/
		virtual void onWindowHidden(Window*window);
		/*Event called when the window is exposed and should be redrawn
			\param window the window that was exposed*/
		virtual void onWindowExposed(Window*window);
		/*Event called when the window has been moved
			\param window the window that was moved
			\param position the new position of the window, relative to the entire screen*/
		virtual void onWindowMoved(Window*window, const Vector2d&position);
		/*Event called when the window has been resized
			\param window the window that was resized
			\param size the new size of the window
			\param external stores true if the event was externally driven (resized by the user), and false if the window was resized programmatically*/
		virtual void onWindowResized(Window*window, const Vector2u&size, bool external);
		/*Event called when the window has been minimized
			\param window the window that was minimized*/
		virtual void onWindowMinimize(Window*window);
		/*Event called when the window has been maximized
			\param window the window that was maximized*/
		virtual void onWindowMaximize(Window*window);
		/*Event called when the window has been restored down to normal size and position
			\param window the window that was restored*/
		virtual void onWindowRestore(Window*window);
		/*Event called when the mouse pointer enters the window
			\param window the window that has mouse focus*/
		virtual void onWindowMouseEnter(Window*window);
		/*Event called when the mouse pointer leaves the window
			\param window the window that lost mouse focus*/
		virtual void onWindowMouseLeave(Window*window);
		/*Event called when the window gains input focus
			\param window the window that gained input focus*/
		virtual void onWindowFocusGained(Window*window);
		/*Event called when the window loses input focus
			\param window the window that lost input focus*/
		virtual void onWindowFocusLost(Window*window);
		/*Event called when the window requests to close
			\param window the window that is closing
			\returns true to allow the window to close, false to prevent it from closing. In the case of multiple listeners, the one returning false takes priority. Returns true by default*/
		virtual bool onWindowClose(Window*window);
	};
}
