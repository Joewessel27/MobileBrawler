
#include "AssetManager.h"
#include "../Utilities/Geometry/Transform.h"
#include "../Utilities/Time/TimeInterval.h"
#include "../Window/Window.h"

#pragma once

namespace GameLibrary
{
	class Application;
	class Window;

	class ApplicationData
	{
	private:
		Application* application;
		Window* window;
		AssetManager* assetManager;
		TimeInterval timeInterval;
		Transform transform;

	public:
		ApplicationData(Application*application, Window*window, AssetManager*assetManager, const TimeInterval&timeInterval, const Transform&transform);
		ApplicationData(const ApplicationData&);

		ApplicationData& operator=(const ApplicationData&);

		Application* getApplication() const;
		Window* getWindow() const;
		AssetManager* getAssetManager() const;
		TimeInterval& getTime();
		const TimeInterval& getTime() const;
		Transform& getTransform();
		const Transform& getTransform() const;

		void setApplication(Application*application);
		void setWindow(Window*window);
		void getAssetManager(AssetManager*assetManager);
		void setTime(const TimeInterval&time);
		void setTransform(const Transform&transform);
	};

	typedef ApplicationData AppData;
}