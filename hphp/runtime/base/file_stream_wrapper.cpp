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

#include "hphp/runtime/base/file_stream_wrapper.h"
#include "hphp/runtime/base/runtime_error.h"
#include "hphp/runtime/base/plain_file.h"
#include "hphp/runtime/server/static_content_cache.h"
#include <memory>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

MemFile* FileStreamWrapper::openFromCache(CStrRef filename, CStrRef mode) {
  if (!StaticContentCache::TheFileCache) {
    return nullptr;
  }

  String relative =
    FileCache::GetRelativePath(File::TranslatePath(filename).c_str());
  std::unique_ptr<MemFile> file(NEWOBJ(MemFile)());
  bool ret = file->open(relative, mode);
  if (ret) {
    return file.release();
  }
  return nullptr;
}

File* FileStreamWrapper::open(CStrRef filename, CStrRef mode,
                              int options, CVarRef context) {
  String fname =
    !strncmp(filename.data(), "file://", sizeof("file://") - 1)
    ? filename.substr(sizeof("file://") - 1) : filename;

  if (MemFile *file = openFromCache(fname, mode)) {
    return file;
  }

  std::unique_ptr<PlainFile> file(NEWOBJ(PlainFile)());
  bool ret = file->open(File::TranslatePath(fname), mode);
  if (!ret) {
    raise_warning("%s", file->getLastError().c_str());
    return nullptr;
  }
  return file.release();
}

///////////////////////////////////////////////////////////////////////////////
}
