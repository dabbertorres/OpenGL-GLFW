#include "Monitor.hpp"

namespace swift
{
	Monitor::GammaRamp::GammaRamp()
	{
		blue.fill(0);
		green.fill(0);
		red.fill(0);
	}

	Monitor::VideoMode::VideoMode()
	:	resolution{0, 0},
		refreshRate(0),
		blueBits(0),
		greenBits(0),
		redBits(0)
	{}

	Monitor::VideoMode::VideoMode(const GLFWvidmode& vm)
	:	resolution{static_cast<uint>(vm.width), static_cast<uint>(vm.height)},
		refreshRate(vm.refreshRate),
		blueBits(vm.blueBits),
		greenBits(vm.greenBits),
		redBits(vm.redBits)
	{}

	Monitor& Monitor::getPrimary()
	{
		getMonitorsList();
		return monitors[0];
	}

	const Monitor::MonitorList& Monitor::getAll()
	{
		getMonitorsList();
		return monitors;
	}

	Vector<uint, 2> Monitor::getPosition() const
	{
		int x;
		int y;

		glfwGetMonitorPos(monitor, &x, &y);

		return {static_cast<uint>(x), static_cast<uint>(y)};
	}

	Vector<uint, 2> Monitor::getPhysicalSize() const
	{
		int x;
		int y;

		glfwGetMonitorPhysicalSize(monitor, &x, & y);

		return {static_cast<uint>(x), static_cast<uint>(y)};
	}
	
	std::string Monitor::getName() const
	{
		return glfwGetMonitorName(monitor);
	}

	std::vector<Monitor::VideoMode> Monitor::getVideoModes() const
	{
		std::vector<VideoMode> videoModes;

		int total = 0;
		const GLFWvidmode* vms = glfwGetVideoModes(monitor, &total);

		for(int i = 0; i < total; ++i)
			videoModes.emplace_back(vms[i]);

		return videoModes;
	}

	Monitor::VideoMode Monitor::getCurrentVideoMode() const
	{
		return {*glfwGetVideoMode(monitor)};
	}

	void Monitor::setGamma(float g)
	{
		glfwSetGamma(monitor, g);
		getNewGammaRamp();
	}

	void Monitor::setGammaRamp(const GammaRamp& gr)
	{
		gammaRamp = gr;

		GLFWgammaramp glgr;
		glgr.size = 256;
		
		std::copy(gr.blue.begin(), gr.blue.end(), glgr.blue);
		std::copy(gr.green.begin(), gr.green.end(), glgr.green);
		std::copy(gr.red.begin(), gr.red.end(), glgr.red);

		glfwSetGammaRamp(monitor, &glgr);
	}
	
	const Monitor::GammaRamp& Monitor::getGammaRamp() const
	{
		return gammaRamp;
	}
	
	void Monitor::getMonitorsList()
	{
		if(monitors.empty())
		{
			int total = 0;
			GLFWmonitor** mons = glfwGetMonitors(&total);

			for(int i = 0; i < total; ++i)
				monitors.emplace_back(mons[i]);
		}
	}
	
	Monitor::Monitor(GLFWmonitor* m)
	:	monitor(m)
	{
		getNewGammaRamp();
	}
	
	void Monitor::getNewGammaRamp()
	{
		const GLFWgammaramp* gr = glfwGetGammaRamp(monitor);
		
		std::copy(gr->blue, gr->blue + gr->size, gammaRamp.blue.begin());
		std::copy(gr->green, gr->green + gr->size, gammaRamp.green.begin());
		std::copy(gr->red, gr->red + gr->size, gammaRamp.red.begin());
	}
	
	std::vector<Monitor, Monitor::Allocator> Monitor::monitors;
}
