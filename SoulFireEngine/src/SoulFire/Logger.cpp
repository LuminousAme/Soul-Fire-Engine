//Soul Fire Engine By Ame Gilham, inspired by The Cherno's Hazel 
//Logger.cpp - source file for the class that handles the logging system by wrapping around spdlog

//precompile header
#include "SF_PCH.h"

#include "Logger.h"

//include required spdlog features
#include "spdlog/common.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/ansicolor_sink.h"

namespace SoulFire {
	//declare the two different logger static pointers
	std::shared_ptr<spdlog::logger> Logger::s_ApplicationLog;
	std::shared_ptr<spdlog::logger> Logger::s_EngineLog;


	void Logger::Init()
	{
		//set the logging pattern
		//start color, timestamp, type, from logger name, message, end color
		spdlog::set_pattern("%^[%T] %l from %n: %v%$"); 

		//create the loggers
		s_ApplicationLog = spdlog::stdout_color_mt("Application", spdlog::color_mode::automatic);
		s_ApplicationLog->set_level(spdlog::level::trace);
		s_EngineLog = spdlog::stdout_color_mt("Engine", spdlog::color_mode::automatic);
		s_EngineLog->set_level(spdlog::level::trace);

		// get the output color for the trace logging
		auto console_sink = dynamic_cast<spdlog::sinks::stdout_color_sink_mt*>(s_ApplicationLog->sinks().back().get());
		// and change it to white
		console_sink->set_color(spdlog::level::trace, console_sink->WHITE);
		//and repeat for the engine log
		console_sink = dynamic_cast<spdlog::sinks::stdout_color_sink_mt*>(s_EngineLog->sinks().back().get());
		console_sink->set_color(spdlog::level::trace, console_sink->WHITE);
	}
}