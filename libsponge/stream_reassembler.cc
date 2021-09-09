#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity)
                                    ://_stream(capacity,'\0')
                                    //,_state(capacity,false)
                                    _stream(capacity)
                                    ,_is_eof(false)
                                    ,_is_end_index(0)
                                    ,_unassembled_bytes(0)
                                    ,_output(capacity)
                                    ,_capacity(capacity)
{
    for(std::size_t i=0;i<_capacity;++i) {
        /*_stream.insert(i).first='\0';
        _stream.at(i).second= false;*/
        _stream.insert(std::begin(_stream),1,std::make_pair('\0',false));
    }

}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
//  这个函数接受一个字节的子串（又称段）。
//  可能是无序的，来自逻辑流，并组装任何新的
//  连续的子串，并按顺序将它们写入输出流。
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    //DUMMY_CODE(data, index, eof);

    auto first_unassembled=_output.bytes_written();
    auto first_unacceptable=first_unassembled+_capacity;

    auto begin_index=index;
    auto end_index=index+data.size();

    if(begin_index>=first_unacceptable || end_index<first_unassembled) {
        return;
    }

    if(begin_index<first_unassembled) {
        begin_index=first_unassembled;
    }
    if(end_index>=first_unacceptable) {
        end_index=first_unacceptable;
    }

    for(auto i=begin_index;i<end_index;++i) {
        //if(_stream.count(data.at(i-index))==1)
        /*auto it=_stream.find(data.at(i-index));
        if(it==_stream.end()) {
            _stream.emplace(std::make_pair(data.at(i-index),true));
            _unassembled_bytes++;
        }*/
        /*if(!_state[i-first_unassembled]) {
            _stream[i-first_unassembled]=data[i-index];
            _state[i-first_unassembled]=true;
            _unassembled_bytes++;
        }*/
        if(_stream.at(i-first_unassembled).second==false) {
            _stream.at(i-first_unassembled).first=data[i-index];
            _stream.at(i-first_unassembled).second=true;
            ++_unassembled_bytes;
        }
        /*list<std::pair<char,bool>>::iterator it;

        for(auto it=_stream.begin();it!=_stream.end();it++) {
            if(it->second==false) {
                it->first=data[i-index];
                it->second=true;
                ++_unassembled_bytes;
            }
        }*/
    }

    std::string str;
    /*while(_state.front()) {
        str+=_stream.front();
        _stream.pop_front();
        _state.pop_front();

        _stream.emplace_back('\0');
        _state.emplace_back(false);
    }*/
    while(_stream.front().second) {
        str+=_stream.front().first;

        _stream.pop_front();

        _stream.emplace_back(std::make_pair('\0', false));
    }

    if(str.size()>0) {
        stream_out().write(str);
        _unassembled_bytes-=str.size();
    }

    if(eof) {
        _is_eof=true;
        _is_end_index=end_index;
    }

    if(_is_eof && _is_end_index==_output.bytes_written()) {
        _output.end_input();
    }

}

size_t StreamReassembler::unassembled_bytes() const {
    return _unassembled_bytes;
}

bool StreamReassembler::empty() const {
    return unassembled_bytes()==0;
}
