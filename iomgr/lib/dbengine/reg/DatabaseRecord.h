// Copyright (C) 2019-2020 Siodb GmbH. All rights reserved.
// Use of this source code is governed by a license that can be found
// in the LICENSE file.

#pragma once

// Common project headers
#include <siodb/common/utils/BinaryValue.h>
#include <siodb/common/utils/Uuid.h>

// STL headers
#include <string>

namespace siodb::iomgr::dbengine {

class Database;

/** In-memory database registry record */
struct DatabaseRecord {
    /** Initializes object of class DatabaseRecord */
    DatabaseRecord() noexcept
        : m_id(0)
    {
    }

    /**
     * Initializes object of class DatabaseRecord.
     * @param id Database ID.
     * @param uuid Database UUID.
     * @param name Database name.
     * @param cipherId Cipher identifier.
     * @param cipherKey Cipher key.
     */
    DatabaseRecord(std::uint32_t id, const Uuid& uuid, std::string&& name, std::string&& cipherId,
            BinaryValue&& cipherKey)
        : m_id(id)
        , m_uuid(uuid)
        , m_name(std::move(name))
        , m_cipherId(std::move(cipherId))
        , m_cipherKey(std::move(cipherKey))
    {
    }

    /**
     * Initializes object of class DatabaseRecord.
     * @param database Database object.
     */
    DatabaseRecord(const Database& database);

    /**
     * Returns buffer size required to serialize this object.
     * @return Number of bytes.
     */
    std::size_t getSerializedSize() const noexcept;

    /**
     * Serializes object into buffer. Assumes buffer is big enough.
     * @param buffer Output buffer.
     * @return Address of byte after last written byte.
     */
    std::uint8_t* serializeUnchecked(std::uint8_t* buffer) const noexcept;

    /**
     * Deserializes object from buffer.
     * @param buffer Input buffer.
     * @param length Length of data in the buffer.
     * @return Number of bytes consumed.
     */
    std::size_t deserialize(const std::uint8_t* buffer, std::size_t length);

    /** Database ID */
    std::uint32_t m_id;

    /** Database UUID */
    Uuid m_uuid;

    /** Database name */
    std::string m_name;

    /** Cipher ID */
    std::string m_cipherId;

    /** Cipher key */
    BinaryValue m_cipherKey;

    /** Structure name */
    static constexpr const char* kClassName = "DatabaseRecord";
};

}  // namespace siodb::iomgr::dbengine
