// Copyright (C) 2019-2020 Siodb GmbH. All rights reserved.
// Use of this source code is governed by a license that can be found
// in the LICENSE file.

#pragma once

// Project headers
#include "../io/OutputStream.h"
#include "../utils/ErrorCodeChecker.h"

// STL headers
#include <memory>

// Protobuf headers
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

namespace siodb::protobuf {

/** Siodb version of the protobuf output stream which operates over an OutputStream. */
class StreamOutputStream : public google::protobuf::io::ZeroCopyOutputStream,
                           public io::OutputStream {
public:
    /**
     * Creates a stream that reads from the given OutputStream.
     * If a block_size is given, it specifies the number of bytes that
     * should be read and returned with each call to Next().  Otherwise,
     * a reasonable default is used.
     * @param stream Output stream.
     * @param errorChecker Error checker.
     * @param blockSize Block size.
     */
    explicit StreamOutputStream(io::OutputStream& stream,
            const utils::ErrorCodeChecker& errorCodeChecker, int blockSize = -1);

    /**
     * If an I/O error has occurred on this OutputStream, this is the
     * errno from that error. Otherwise, this is zero. Once an error
     * occurs, the stream is broken and all subsequent operations will fail.
     * @return Error code.
     */
    int GetErrno() const noexcept
    {
        return m_copyingOutput.GetErrno();
    }

    /**
     * Flushes IO.
     * @return true if operation succeded.
     */
    bool Flush()
    {
        if (m_isOpen) return m_impl.Flush();
        return false;
    }

    // implements ZeroCopyOutputStream
    bool Next(void** data, int* size) override;
    void BackUp(int count) override;
    google::protobuf::int64 ByteCount() const override;

    /** 
     * Checks for error.
     * @throw std::system_error if error found.
     */
    void CheckNoError() const;

    ////////////// siodb::io::OutputStream implementation /////////////////////

    /**
     * Returns indication that stream is valid.
     * @return true stream if stream is valid, false otherwise.
     */
    bool isValid() const noexcept override;

    /**
     * Closes stream.
     * @return Zero on success, nonzero otherwise.
     */
    int close() noexcept override;

    /**
     * Writes data to stream.
     * @param buffer Data buffer.
     * @param size Data size in bytes.
     * @return Number of written bytes. Negative value indicates error.
     */
    std::ptrdiff_t write(const void* buffer, std::size_t size) noexcept override;

private:
    class CopyingOutputStream : public google::protobuf::io::CopyingOutputStream {
    public:
        CopyingOutputStream(
                io::OutputStream& stream, const utils::ErrorCodeChecker& errorCodeChecker);

        int GetErrno() const noexcept
        {
            return m_errno;
        }

        // implements CopyingOutputStream
        bool Write(const void* buffer, int size);

    private:
        /** Error checker */
        const utils::ErrorCodeChecker& m_errorCodeChecker;

        /** Output stream*/
        io::OutputStream& m_stream;

        /** The errno of the I/O error, if one has occurred. Otherwise, zero */
        int m_errno;

        GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(CopyingOutputStream);
    };

    CopyingOutputStream m_copyingOutput;
    google::protobuf::io::CopyingOutputStreamAdaptor m_impl;
    bool m_isOpen;

    GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(StreamOutputStream);
};

}  // namespace siodb::protobuf
