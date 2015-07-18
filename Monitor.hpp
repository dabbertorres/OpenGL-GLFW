#ifndef SWIFT_MONITOR_HPP
#define SWIFT_MONITOR_HPP

#include <GL/glew.h>	// GLEW include MUST go before GLFW include

#include <GLFW/glfw3.h>

#include <string>
#include <array>
#include <vector>

#include "Types.hpp"
#include "Color.hpp"
#include "Vector.hpp"

namespace swift
{
	class Monitor
	{
		public:
			struct Allocator : public std::allocator<Monitor>
			{
				template<typename T, typename... Args>
				void construct(T* p, Args&&... args)
				{
					new (static_cast<void *>(p)) T(std::forward<Args>(args)...);
				}

				template<typename T>
				struct rebind
				{
					using other = Allocator;
				};

				using value_type = Monitor;
			};

			struct GammaRamp
			{
				GammaRamp();

				std::array<unsigned short, 256> blue;
				std::array<unsigned short, 256> green;
				std::array<unsigned short, 256> red;
			};

			struct VideoMode
			{
				VideoMode();
				VideoMode(const GLFWvidmode& vm);

				Vector<uint, 2> resolution;
				uint refreshRate;

				uint blueBits;
				uint greenBits;
				uint redBits;
			};

			using MonitorList = std::vector<Monitor, Allocator>;

			static Monitor& getPrimary();
			static const MonitorList& getAll();

			Vector<uint, 2> getPosition() const;
			Vector<uint, 2> getPhysicalSize() const;
			std::string getName() const;
			std::vector<VideoMode> getVideoModes() const;
			VideoMode getCurrentVideoMode() const;

			void setGamma(float g);
			void setGammaRamp(const GammaRamp& gr);
			const GammaRamp& getGammaRamp() const;

		private:
			friend class Allocator;
			friend class Window;
			
			static void getMonitorsList();

			Monitor(GLFWmonitor* m);

			void getNewGammaRamp();

			GLFWmonitor* monitor;
			GammaRamp gammaRamp;

		private:
			static MonitorList monitors;
	};
}

#endif
