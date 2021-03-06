/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-2013 Facebook, Inc. (http://www.facebook.com)     |
   | Copyright (c) 1998-2010 Zend Technologies Ltd. (http://www.zend.com) |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.00 of the Zend license,     |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.zend.com/license/2_00.txt.                                |
   | If you did not receive a copy of the Zend license and are unable to  |
   | obtain it through the world-wide-web, please send a note to          |
   | license@zend.com so we can mail you a copy immediately.              |
   +----------------------------------------------------------------------+
*/

#include "hphp/runtime/base/php_stream_wrapper.h"
#include "hphp/runtime/base/runtime_error.h"
#include "hphp/runtime/base/plain_file.h"
#include "hphp/runtime/base/temp_file.h"
#include "hphp/runtime/base/mem_file.h"
#include "hphp/runtime/base/output_file.h"
#include <memory>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

File *PhpStreamWrapper::openFD(const char *sFD) {
  if (!RuntimeOption::ClientExecutionMode()) {
    raise_warning("Direct access to file descriptors "
                  "is only available from command-line");
    return nullptr;
  }

  char *end = nullptr;
  long nFD = strtol(sFD, &end, 10);
  if ((sFD == end) || (*end != '\0')) {
    raise_warning("php://fd/ stream must be specified in the form "
                  "php://fd/<orig fd>");
    return nullptr;
  }
  long dtablesize = getdtablesize();
  if ((nFD < 0) || (nFD >= dtablesize)) {
    raise_warning("The file descriptors must be non-negative numbers "
                  "smaller than %ld", dtablesize);
    return nullptr;
  }

  return NEWOBJ(PlainFile)(dup(nFD), true);
}


File* PhpStreamWrapper::open(CStrRef filename, CStrRef mode,
                             int options, CVarRef context) {
  if (strncasecmp(filename.c_str(), "php://", 6)) {
    return nullptr;
  }

  const char *req = filename.c_str() + sizeof("php://") - 1;

  if (!strcasecmp(req, "stdin")) {
    return NEWOBJ(PlainFile)(dup(STDIN_FILENO), true);
  }
  if (!strcasecmp(req, "stdout")) {
    return NEWOBJ(PlainFile)(dup(STDOUT_FILENO), true);
  }
  if (!strcasecmp(req, "stderr")) {
    return NEWOBJ(PlainFile)(dup(STDERR_FILENO), true);
  }
  if (!strncasecmp(req, "fd/", sizeof("fd/") - 1)) {
    return openFD(req + sizeof("fd/") - 1);
  }

  if (!strncasecmp(req, "temp", sizeof("temp") - 1) ||
      !strcasecmp(req, "memory")) {
    std::unique_ptr<TempFile> file(NEWOBJ(TempFile)());
    if (!file->valid()) {
      raise_warning("Unable to create temporary file");
      return nullptr;
    }
    return file.release();
  }

  if (!strcasecmp(req, "input")) {
    Transport *transport = g_context->getTransport();
    if (transport) {
      int size = 0;
      const void *data = transport->getPostData(size);
      if (data && size) {
        return NEWOBJ(MemFile)((const char *)data, size);
      }
    }
    return NEWOBJ(MemFile)(nullptr, 0);
  }

  if (!strcasecmp(req, "output")) {
    return NEWOBJ(OutputFile)(filename);
  }

  return nullptr;
}

///////////////////////////////////////////////////////////////////////////////
}
