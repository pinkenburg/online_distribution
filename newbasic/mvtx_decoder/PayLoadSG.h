// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

// @file PayLoadSG.h
// @brief Declaration of class for scatter-gather buffer
// @author ruben.shahoyan@cern.ch
// @sa <O2/Detectors/ITSMFT/common/reconstruction/include/ITSMFTReconstruction/PayLoadSG.h>
//     <1c31a8d52>

#ifndef MVTXDECODER_PAYLOADSG_H
#define MVTXDECODER_PAYLOADSG_H

#include <cstdint>
#include <vector>

namespace mvtx
{

class PayLoadSG
{
  // scatter-gather buffer for the payload: base pointer + vector of references for pieces to collect
 public:
//  using DataType = unsigned char;

  PayLoadSG() = default;
  ~PayLoadSG() = default;

  ///< add n bytes to the buffer
  void add( size_t start, size_t n)
  {
    if (n)
    {
      mBuffer.emplace_back(start, n);
    }
  }
/*
  ///< read current character value from buffer w/o stepping forward
  bool current(char& v)
  {
    if (mCurrentPieceID < mBuffer.size()) {
      const auto& piece = mBuffer[mCurrentPieceID];
      if (mCurrentEntryInPiece < piece.size) {
        v = piece.data[mCurrentEntryInPiece];
        return true;
      } else {
        nextPiece();
        return current(v);
      }
    }
    return false;
  }

  ///< read character value from buffer
  bool next(char& v)
  {
    if (mCurrentPieceID < mBuffer.size()) {
      const auto& piece = mBuffer[mCurrentPieceID];
      if (mCurrentEntryInPiece < piece.size) {
        v = piece.data[mCurrentEntryInPiece++];
        return true;
      } else {
        nextPiece();
        return next(v);
      }
    }
    return false;
  }

  ///< read short value from buffer
  bool next(uint16_t& v)
  {
    char b0, b1;
    if (next(b0) && next(b1)) {
      v = (b0 << 8) | b1;
      return true;
    }
    return false;
  }
*/
  ///< move current pointer to the head
  void rewind()
  {
    mCurrentPieceID = 0;
  }

  ///< make buffer empty
  void clear()
  {
    mBuffer.clear();
    mCurrentPieceID = 0;
  }

  struct SGPiece {
    uint32_t data = 0;   // data of the piece
    uint32_t size = 0;   // size of the piece
    SGPiece() = default;
    SGPiece(int st, int n) : data(st), size(n) {}
  };

  void setDone() { mCurrentPieceID = mBuffer.size(); }

  size_t& currentPieceID() { return mCurrentPieceID; }
  size_t currentPieceID() const { return mCurrentPieceID; }

  const SGPiece* currentPiece() const { return mCurrentPieceID < mBuffer.size() ? &mBuffer[mCurrentPieceID] : nullptr; }

  const SGPiece* nextPiece()
  {
    // move to the next piece
    mCurrentPieceID++;
    return currentPiece();
  }

  const SGPiece* getPiece(int i) const { return &mBuffer[i]; }

  size_t getNPieces() const { return mBuffer.size(); }

 private:
  std::vector<SGPiece> mBuffer;   // list of pieces to fetch
  size_t mCurrentPieceID = 0;     // current piece

  //ClassDefNV(PayLoadSG, 1);
};

} // namespace mvtx

#endif
