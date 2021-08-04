#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity)
    : capacity_(capacity), bytes_read_(0), bytes_write_(0), eof_(false), _error(false) {
    // DUMMY_CODE(capacity);
}

size_t ByteStream::write(const string &data) {
    // DUMMY_CODE(data);

    auto len = data.size();

    /*if (capacity_ - stream_.size() < len) {
        len = capacity_ - stream_.size();
        stream_.insert(stream_.end(),data.begin(),data.begin()+len);
    }*/
    if (len > remaining_capacity()) {
        len = remaining_capacity();
    }
    // size_t len = min(capacity_, data.size());
    for (size_t i = 0; i < len; ++i) {
        stream_.append(1, data[i]);
    }
    // stream_ += data.substr(0, len);
    // stream_.insert(stream_.begin(),data.begin(),data.end());
    // stream_.insert(stream_.end(),data.begin(),data.end());
    // availCapacity_ -= len;
    bytes_write_ += len;
    // buffer_size_+=len;

    return len;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    // DUMMY_CODE(len);
    auto length = len;
    if (length > buffer_size()) {
        length = buffer_size();
    }

    // string output;
    /*while(!buffer_empty()) {
        //stream_.pop_front();
        output.insert(0,1,stream_.pop_front());
        //stream_.pop_front();
    }*/
    /*output.assign(stream_.begin(), stream_.begin() + length);

    return output;*/
    // return stream_.substr(0,len);
    return string(stream_.begin(), stream_.begin() + length);
    // return string().assign(stream_.begin(),stream_.end()+length);
    // return stream_.substr(0,len);
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    // DUMMY_CODE(len);
    /*auto length = len;
    if (length > buffer_size()) {
        length = buffer_size();
    }*/
    // availCapacity_ += len;

    auto size = len;
    if (size > buffer_size()) {
        size = buffer_size();
    }

    /*while (length--) {
        stream_.pop_front();
    }*/
    stream_.erase(stream_.begin(), stream_.begin() + size);
    bytes_read_ += size;
    // stream_.erase(0,len);
    // return;
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    // DUMMY_CODE(len);

    auto const res = peek_output(len);
    pop_output(len);

    return res;
}

void ByteStream::end_input() { eof_ = true; }

bool ByteStream::input_ended() const { return eof_; }

size_t ByteStream::buffer_size() const { return stream_.size(); }

bool ByteStream::buffer_empty() const { return buffer_size() == 0; }

bool ByteStream::eof() const { return (input_ended() && buffer_empty()); }

size_t ByteStream::bytes_written() const { return bytes_write_; }

size_t ByteStream::bytes_read() const { return bytes_read_; }

size_t ByteStream::remaining_capacity() const { return capacity_ - buffer_size(); }
