#ifndef SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH
#define SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH

#include "byte_stream.hh"

#include <map>
#include <list>
#include <tuple>
#include <deque>
#include <queue>
#include <unordered_map>

#include <cstdint>
#include <string>

//! \brief A class that assembles a series of excerpts from a byte stream (possibly out of order,
//! possibly overlapping) into an in-order byte stream.
//  一个将字节流中的一系列节选（可能不按顺序）集合成一个有序的字节流的类。
//  可能是重叠的）组装成一个有序的字节流。
class StreamReassembler {
  private:
    // Your code here -- add private members as necessary.
    //std::map<char,bool> _stream;
    //std::deque<char> _stream;
    //std::deque<bool> _state;
    std::deque<std::pair<char,bool>> _stream;

    //std::list<std::pair<char,bool>> _stream;

    bool _is_eof;

    std::size_t _is_end_index;
    std::size_t _unassembled_bytes;

    ByteStream _output;  //!< The reassembled in-order byte stream
    size_t _capacity;    //!< The maximum number of bytes

  public:
    //! \brief Construct a `StreamReassembler` that will store up to `capacity` bytes.
    //! \note This capacity limits both the bytes that have been reassembled,
    //! and those that have not yet been reassembled.
    //   构建一个 "StreamReassembler"，它最多可以存储`capacity'字节
    StreamReassembler(const size_t capacity);

    //! \brief Receive a substring and write any newly contiguous bytes into the stream.
    //!
    //! The StreamReassembler will stay within the memory limits of the `capacity`.
    //! Bytes that would exceed the capacity are silently discarded.
    //!
    //! \param data the substring
    //! \param index indicates the index (place in sequence) of the first byte in `data`
    //! \param eof the last byte of `data` will be the last byte in the entire stream
    //  接收一个子串并将任何新的连续的字节写入流中。
    //  同时保持在 "容量 "的内存限制之内。如果字节数
    //  超过容量的字节会被默默地丢弃。
    //  `data`: 子串
    //  `index`表示`data`中第一个字节的索引（序列中的位置）。
    //  `eof`: 这个子串的最后一个字节将是整个流中的最后一个字节。
    void push_substring(const std::string &data, const uint64_t index, const bool eof);

    //! \name Access the reassembled byte stream
    //!@{
    const ByteStream &stream_out() const { return _output; }
    ByteStream &stream_out() { return _output; }
    //!@}

    //! The number of bytes in the substrings stored but not yet reassembled
    //!
    //! \note If the byte at a particular index has been pushed more than once, it
    //! should only be counted once for the purpose of this function.
    //  已存储但尚未重新组合的子串中的字节数
    //  如果某个特定索引的字节被推送了不止一次，那么它
    //  就本函数而言，应该只计算一次。
    size_t unassembled_bytes() const;

    //! \brief Is the internal state empty (other than the output stream)?
    //! \returns `true` if no substrings are waiting to be assembled
    //  内部状态是否为空（除输出流外）？
    bool empty() const;
};

#endif  // SPONGE_LIBSPONGE_STREAM_REASSEMBLER_HH
