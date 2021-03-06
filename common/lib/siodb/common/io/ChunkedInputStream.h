// Copyright (C) 2019-2020 Siodb GmbH. All rights reserved.
// Use of this source code is governed by a license that can be found
// in the LICENSE file.

#pragma once

// Project headers
#include "InputStreamWrapperStream.h"

// CRT headers
#include <cstdint>

namespace siodb::io {

/** Chunked input wrapper over another input stream. */
class ChunkedInputStream : public InputStreamWrapperStream {
public:
    /**
     * Initializes object of class ChunkedInputStream.
     * @param in Underlying input stream.
     */
    explicit ChunkedInputStream(InputStream& in) noexcept
        : InputStreamWrapperStream(in)
        , m_chunkSize(0)
        , m_pos(0)
        , m_hasChunkSize(false)
        , m_eof(false)
        , m_stopReadingAfterCurrentChunkFinished(false)
    {
    }

    DECLARE_NONCOPYABLE(ChunkedInputStream);

    /**
     * Return end of chunk stream flag.
     * @return true if end of chunk stream reached, false otherwise.
     */
    bool isEof() const noexcept
    {
        return m_eof;
    }

    /**
     * Returns number of bytes remaining in the current chunk.
     * @return Number of bytes remaining in the current chunk.
     */
    std::size_t getRemainingBytesInChunk() const noexcept
    {
        return m_hasChunkSize ? m_chunkSize - m_pos : 0;
    }

    /** Sets indication that stream should stop reading after current chunk finishes. */
    void setStopReadingAfterCurrentChunkFinished() noexcept
    {
        m_stopReadingAfterCurrentChunkFinished = true;
    }

    /**
     * Reads data from stream.
     * @param buffer Data buffer.
     * @param size Size of data in bytes.
     * @return Number of read bytes. Negative value indicates error.
     */
    std::ptrdiff_t read(void* buffer, std::size_t size) noexcept override;

    /**
     * Skips data.
     * @param size Number of bytes to skip.
     * @return Number of bytes skipped. Negative value indicates error.
     */
    std::ptrdiff_t skip(std::size_t size) noexcept override;

private:
    /**
     * Reads chunk size.
     * @return 1 on success, 0 on the end of file, -1 on error.
     */
    int readChunkSize() noexcept;

private:
    /** Current chunk size */
    std::uint32_t m_chunkSize;

    /** Current position in the chunk */
    std::uint32_t m_pos;

    /** Chunk size presence flag */
    bool m_hasChunkSize;

    /** End of chunk stream flag */
    bool m_eof;

    /** Indicates that reading should be stopped as if end of stream received */
    bool m_stopReadingAfterCurrentChunkFinished;
};

}  // namespace siodb::io
