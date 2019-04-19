/*
 * redisdemo.h
 *
 *  Created on: Apr 18, 2019
 *      Author: SMING
 */


#ifndef REDISDEMO_H_
#define REDISDEMO_H_
#include <string>
#include "hiredis.h"
	class RedisDemo{
	public:
		RedisDemo();
		void write(redisContext *c, std::string const &key, std::string const &value);
		std::string read(redisContext *c, std::string const &key);
		redisContext *context;


	};




#endif /* REDISDEMO_H_ */
