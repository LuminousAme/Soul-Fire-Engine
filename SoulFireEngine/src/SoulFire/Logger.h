//Soul Fire Engine By Ame Gilham 
//Logger.h - header file for the class that handles the logging system by wrapping around spdlog
#pragma once

#include "EngineCore.h"
#include "spdlog/spdlog.h"
#include <memory>


namespace SoulFire {
	class SF_API Logger
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetApplicationLog() { return s_ApplicationLog; }
		inline static std::shared_ptr<spdlog::logger>& GetEngineLog() { return s_EngineLog; }

	private:
		static std::shared_ptr<spdlog::logger> s_ApplicationLog;
		static std::shared_ptr<spdlog::logger> s_EngineLog;
	};
}

//Application logging
#define SF_LOG_TRACE(...)          ::SoulFire::Logger::GetApplicationLog()->trace(__VA_ARGS__);
#define SF_LOG_INFO(...)           ::SoulFire::Logger::GetApplicationLog()->info(__VA_ARGS__);
#define SF_LOG_WARNING(...)        ::SoulFire::Logger::GetApplicationLog()->warn(__VA_ARGS__);
#define SF_LOG_ERROR(...)          ::SoulFire::Logger::GetApplicationLog()->error(__VA_ARGS__);
#define SF_LOG_FATAL(...)          ::SoulFire::Logger::GetApplicationLog()->fatal(__VA_ARGS__);
//application assert
#define SF_LOG_ASSERT(x, ...){if(!(x)){ ::SoulFire::Logger::GetApplicationLog()->error(__VA_ARGS__); __debugbreak();}}

//engine logging
#define SF_ENGINE_LOG_TRACE(...)   ::SoulFire::Logger::GetEngineLog()->trace(__VA_ARGS__);
#define SF_ENGINE_LOG_INFO(...)    ::SoulFire::Logger::GetEngineLog()->info(__VA_ARGS__);
#define SF_ENGINE_LOG_WARNING(...) ::SoulFire::Logger::GetEngineLog()->warn(__VA_ARGS__);
#define SF_ENGINE_LOG_ERROR(...)   ::SoulFire::Logger::GetEngineLog()->error(__VA_ARGS__);
#define SF_ENGINE_LOG_FATAL(...)   ::SoulFire::Logger::GetEngineLog()->fatal(__VA_ARGS__);
//engine assert
#define SF_ENGINE_LOG_ASSERT(x, ...){if(!(x)){ ::SoulFire::Logger::GetEngineLog()->error(__VA_ARGS__); __debugbreak();}}