
#ifndef _COMMON_H_
#define _COMMOH_H_

#define foreach(i,d) for(i = d.begin(); i != d.end(); i++)
#define foreach_ptr(i,d) for(i = d->begin(); i != d->end(); i++)

#define LOG_LEVEL_ERROR 1
#define LOG_LEVEL_INFO  2
#define LOG_LEVEL_DEBUG 3

#define LOG(level, format, ...)  \
  if (level > m_log_level) ; \
  else { \
    printf("[ collectd-fs ]: "); \
    printf(format, __VA_ARGS__); \
  }

#define DEBUG(format, ...)  LOG(LOG_LEVEL_DEBUG, format, __VA_ARGS__)
#define ERROR(format, ...)  LOG(LOG_LEVEL_ERROR, format, __VA_ARGS__)
#define INFO(format, ...)   LOG(LOG_LEVEL_INFO, format, __VA_ARGS__)

#endif /* _COMMON_H_ */
