#pragma once
namespace miit::algebra
{
	/**
	* @brief
	*/
	class Generator
	{
	public:
		/**
		* @brief
		*/
		virtual ~Generator() {};
		/**
		* @brief
		*/
		virtual int generate() = 0;
	};
}
