#include <exception>
#include <stdio.h>
#include <logging.h>

DataFlowException::DataFlowException(const char *type, const char *error)
{
  sprintf(msg, "%s: %s", type, error);
  char logmsg[1024];
  sprintf(logmsg, "Throwing exception: (%s): %s", type, msg);
  Logger::LogEvent(logmsg);
};


void Logger::LogEvent(const char *event)
{
  if (logger == NULL)
  {
    logger = fopen("mylog", "w");
  }
    fprintf(logger, "%s\n", event);
};


void Logger::Finalize()
{
  if (logger != NULL) {
    fclose(logger);
  }
};


FILE * Logger::logger = NULL;