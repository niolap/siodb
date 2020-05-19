// Copyright (C) 2019-2020 Siodb GmbH. All rights reserved.
// Use of this source code is governed by a license that can be found
// in the LICENSE file.

#include "UInt8UniqueLinearIndex.h"

// Project headers
#include "../ikt/UInt8IndexKeyTraits.h"

namespace siodb::iomgr::dbengine {

UInt8UniqueLinearIndex::UInt8UniqueLinearIndex(Table& table, const std::string& name,
        std::size_t valueSize, const IndexColumnSpecification& columnSpec,
        std::uint32_t dataFileSize)
    : UniqueLinearIndex(table, IndexType::kLinearIndexU8, name, UInt8IndexKeyTraits(), valueSize,
            &UInt8IndexKeyTraits::compareKeys, columnSpec, dataFileSize)
{
}

UInt8UniqueLinearIndex::UInt8UniqueLinearIndex(
        Table& table, const IndexRecord& indexRecord, std::size_t valueSize)
    : UniqueLinearIndex(
            table, indexRecord, UInt8IndexKeyTraits(), valueSize, &UInt8IndexKeyTraits::compareKeys)
{
}

}  // namespace siodb::iomgr::dbengine
