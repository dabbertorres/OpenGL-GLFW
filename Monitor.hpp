#ifndef SWIFT_MONITOR_HPP
#define SWIFT_MONITOR_HPP

#include <GL/glew.h>	// GLEW include MUST go before GLFW include

#include <GLFW/glfw3.h>

#include <string>
#include <array>
#include <vector>

#include "Color.hpp"
#include "Vector.hpp"

namespace swift
{
	class Monitor
	{
		public:
			struct GammaRamp
			{
				std::array<unsigned short, 256> red;
				std::array<unsigned short, 256> green;
				std::array<unsigned short, 256> blue;
			};
			
			struct VideoMode
			{
				Vector<unsigned int, 2> resolution;
				unsigned int refreshRate;
				
				struct
				{
					unsigned int blue;
					unsigned int green;
					unsigned int red;
				} bitdepth;
			};
			
			static Monitor& getPrimary();
			static std::vector<Monitor&> getAll();
			
			Vector<unsigned int, 2> getPosition() const;
			Vector<unsigned int, 2> getPhysicalSize() const;
			std::string getName() const;
			std::vector<VideoMode> getVideoModes() const;
			VideoMode getCurrentVideoMode() const;
			
			void setGamma(float g);
			void setGammaRamp(const GammaRamp& gr);
			const GammaRamp& getGammaRamp() const;
			
		private:
			static std::vector<Monitor> monitors;
			
			GLFWmonitor* monitor;
			GammaRamp gammaRamp;
	};
}

#endif