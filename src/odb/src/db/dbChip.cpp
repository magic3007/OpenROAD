///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (c) 2019, Nefelus Inc
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

#include "dbChip.h"

#include "dbBlock.h"
#include "dbBlockItr.h"
#include "dbDatabase.h"
#include "dbNameCache.h"
#include "dbProperty.h"
#include "dbPropertyItr.h"
#include "dbTable.h"
#include "dbTable.hpp"
#include "dbTech.h"
#include "odb/db.h"

namespace odb {

template class dbTable<_dbChip>;

bool _dbChip::operator==(const _dbChip& rhs) const
{
  if (_top != rhs._top) {
    return false;
  }

  if (*_block_tbl != *rhs._block_tbl) {
    return false;
  }

  if (*_prop_tbl != *rhs._prop_tbl) {
    return false;
  }

  if (*_name_cache != *rhs._name_cache) {
    return false;
  }

  return true;
}

////////////////////////////////////////////////////////////////////
//
// _dbChip - Methods
//
////////////////////////////////////////////////////////////////////

_dbChip::_dbChip(_dbDatabase* db)
{
  _block_tbl = new dbTable<_dbBlock>(
      db, this, (GetObjTbl_t) &_dbChip::getObjectTable, dbBlockObj);

  _prop_tbl = new dbTable<_dbProperty>(
      db, this, (GetObjTbl_t) &_dbChip::getObjectTable, dbPropertyObj);

  _name_cache
      = new _dbNameCache(db, this, (GetObjTbl_t) &_dbChip::getObjectTable);

  _block_itr = new dbBlockItr(_block_tbl);

  _prop_itr = new dbPropertyItr(_prop_tbl);
}

_dbChip::~_dbChip()
{
  delete _block_tbl;
  delete _prop_tbl;
  delete _name_cache;
  delete _block_itr;
  delete _prop_itr;
}

dbOStream& operator<<(dbOStream& stream, const _dbChip& chip)
{
  dbOStreamScope scope(stream, "dbChip");
  stream << chip._top;
  stream << *chip._block_tbl;
  stream << NamedTable("prop_tbl", chip._prop_tbl);
  stream << *chip._name_cache;
  return stream;
}

dbIStream& operator>>(dbIStream& stream, _dbChip& chip)
{
  stream >> chip._top;
  stream >> *chip._block_tbl;
  stream >> *chip._prop_tbl;
  stream >> *chip._name_cache;

  return stream;
}

dbObjectTable* _dbChip::getObjectTable(dbObjectType type)
{
  if (type == dbBlockObj) {
    return _block_tbl;
  }
  if (type == dbPropertyObj) {
    return _prop_tbl;
  }

  return getTable()->getObjectTable(type);
}

////////////////////////////////////////////////////////////////////
//
// dbChip - Methods
//
////////////////////////////////////////////////////////////////////

dbBlock* dbChip::getBlock()
{
  _dbChip* chip = (_dbChip*) this;

  if (chip->_top == 0) {
    return nullptr;
  }

  return (dbBlock*) chip->_block_tbl->getPtr(chip->_top);
}

dbChip* dbChip::create(dbDatabase* db_)
{
  _dbDatabase* db = (_dbDatabase*) db_;

  if (db->_chip != 0) {
    return nullptr;
  }

  _dbChip* chip = db->_chip_tbl->create();
  db->_chip = chip->getOID();
  return (dbChip*) chip;
}

dbChip* dbChip::getChip(dbDatabase* db_, uint dbid_)
{
  _dbDatabase* db = (_dbDatabase*) db_;
  return (dbChip*) db->_chip_tbl->getPtr(dbid_);
}

void dbChip::destroy(dbChip* chip_)
{
  _dbChip* chip = (_dbChip*) chip_;
  _dbDatabase* db = chip->getDatabase();
  dbProperty::destroyProperties(chip);
  db->_chip_tbl->destroy(chip);
  db->_chip = 0;
}

void _dbChip::collectMemInfo(MemInfo& info)
{
  info.cnt++;
  info.size += sizeof(*this);

  _block_tbl->collectMemInfo(info.children_["block"]);
  _prop_tbl->collectMemInfo(info.children_["prop"]);
  _name_cache->collectMemInfo(info.children_["name_cache"]);
}

}  // namespace odb
