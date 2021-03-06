/*
 * version.h
 *
 *  Created on: Sep 17, 2018
 *      Author: meir
 */

#ifndef SRC_VERSION_H_
#define SRC_VERSION_H_

#define REDISGEARS_VERSION_MAJOR 99
#define REDISGEARS_VERSION_MINOR 99
#define REDISGEARS_VERSION_PATCH 99

#define REDISEARCH_MODULE_VERSION \
  (REDISGEARS_VERSION_MAJOR * 10000 + REDISGEARS_VERSION_MINOR * 100 + REDISGEARS_VERSION_PATCH)

/* API versions. */
#define REDISMODULE_APIVER_1 1

#endif /* SRC_VERSION_H_ */
