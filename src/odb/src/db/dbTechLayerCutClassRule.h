///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2020, The Regents of the University of California
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
//
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// Generator Code Begin Header
#pragma once

#include "dbCore.h"
#include "odb/odb.h"

namespace odb {
class dbIStream;
class dbOStream;
class _dbDatabase;

struct dbTechLayerCutClassRuleFlags
{
  bool length_valid_ : 1;
  bool cuts_valid_ : 1;
  uint spare_bits_ : 30;
};

class _dbTechLayerCutClassRule : public _dbObject
{
 public:
  _dbTechLayerCutClassRule(_dbDatabase*);

  ~_dbTechLayerCutClassRule();

  bool operator==(const _dbTechLayerCutClassRule& rhs) const;
  bool operator!=(const _dbTechLayerCutClassRule& rhs) const
  {
    return !operator==(rhs);
  }
  bool operator<(const _dbTechLayerCutClassRule& rhs) const;
  void collectMemInfo(MemInfo& info);

  dbTechLayerCutClassRuleFlags flags_;
  char* _name;
  int width_;
  int length_;
  int num_cuts_;
  dbId<_dbTechLayerCutClassRule> _next_entry;
};
dbIStream& operator>>(dbIStream& stream, _dbTechLayerCutClassRule& obj);
dbOStream& operator<<(dbOStream& stream, const _dbTechLayerCutClassRule& obj);
}  // namespace odb
   // Generator Code End Header
